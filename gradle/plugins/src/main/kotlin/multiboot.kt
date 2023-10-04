import br.dev.pedrolamarao.elf.*
import br.dev.pedrolamarao.gdb.rsp.GdbRemote
import br.dev.pedrolamarao.gdb.rsp.GdbRemoteParser
import br.dev.pedrolamarao.gdb.rsp.GdbRemoteStopSignal
import org.gradle.api.DefaultTask
import org.gradle.api.GradleException
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.Property
import org.gradle.api.provider.ProviderFactory
import org.gradle.api.tasks.*
import org.gradle.kotlin.dsl.newInstance
import org.gradle.process.ExecOperations
import java.io.File
import java.lang.String.format
import java.net.InetSocketAddress
import java.nio.ByteOrder
import java.nio.channels.FileChannel
import java.nio.channels.FileChannel.MapMode
import java.nio.file.Files
import java.nio.file.Paths
import java.util.concurrent.ThreadLocalRandom
import java.util.concurrent.TimeUnit
import javax.inject.Inject
import kotlin.collections.List
import kotlin.collections.Map
import kotlin.collections.dropLastWhile
import kotlin.collections.forEach
import kotlin.collections.listOf
import kotlin.collections.mutableListOf
import kotlin.collections.mutableMapOf
import kotlin.collections.plus
import kotlin.collections.plusAssign
import kotlin.collections.set
import kotlin.collections.toTypedArray

abstract class MultibootCreateImageTask : DefaultTask()
{
    @get:InputFile
    abstract val inputFile: RegularFileProperty

    @get:Input
    abstract val command: Property<String>

    @get:OutputFile
    abstract val outputFile: RegularFileProperty

    @get:Inject
    abstract val execOperations: ExecOperations

    @get:InputFiles
    abstract val moduleFiles : ConfigurableFileCollection

    @get:Inject
    abstract val providers: ProviderFactory

    init
    {
        // TODO: expose Gradle Metal locateToolFile utility
        fun locateExecutableFile (list: String, name: String): File {
            for (item in list.split(File.pathSeparator.toRegex()).dropLastWhile { it.isEmpty() }.toTypedArray()) {
                val directory = Paths.get(item)
                if (! Files.isDirectory(directory)) continue
                val file = directory.resolve(name)
                if (Files.isExecutable(file)) return file.toFile()
                val file_exe = file.resolveSibling("$name.exe")
                if (Files.isExecutable(file_exe)) return file_exe.toFile()
            }
            throw GradleException("executable file not found: $name")
        }
        val metalPath = providers.gradleProperty("metal.path")
            .orElse(providers.environmentVariable("PATH"))

        val target = project.providers.gradleProperty("metal.target").orElse("default").get()
        val tool = metalPath.map { locateExecutableFile(it,"grub-mkstandalone").toString() }

        val layout = project.layout
        command.convention(tool)
        outputFile.convention( inputFile.flatMap { layout.buildDirectory.file("grub/standalone/${target}/${it.asFile.nameWithoutExtension}") } )
    }

    @TaskAction
    fun action ()
    {
        val configurationFile = File(temporaryDir, "grub.cfg").apply {
            createNewFile()
            writeText(
                GrubConfigurationEditor().apply {
                    options["default"] = "0"
                    options["timeout"] = "0"
                    entries += GrubConfigurationEntryEditor().apply {
                        name = "psys"
                        multiboot2("(memdisk)/program")
                        moduleFiles.forEach { module2("/modules/${it.name}") }
                    }
                }
                .toString()
            )
        }

        val builder = project.objects.newInstance<GrubMakeImageEditor>()
        builder.platform.set("i386-pc")
        builder.imageFile.set(outputFile)
        builder.installModules.addAll("configfile", "memdisk", "multiboot2", "normal")
        builder.source("/boot/grub/grub.cfg", configurationFile)
        builder.source("/program", inputFile)
        moduleFiles.forEach { builder.source("/modules/${it.name}", it) }

        execOperations.exec {
            executable = command.get()
            argumentProviders += builder
            errorOutput = File(temporaryDir, "grub-mkstandalone.err.txt").outputStream()
            standardOutput = File(temporaryDir, "grub-mkstandalone.out.txt").outputStream()
        }
    }
}

abstract class MultibootRunImageTask : DefaultTask()
{
    @get:InputFile
    abstract val imageFile : RegularFileProperty

    @get:Nested
    abstract val qemuArgs : QemuSystemEditor

    @get:Input
    abstract val qemuExecutable : Property<String>

    @get:Inject
    abstract val execOperations : ExecOperations

    @get:Inject
    abstract val providers: ProviderFactory;

    init
    {
        // TODO: expose Gradle Metal locateToolFile utility
        fun locateExecutableFile (list: String, name: String): File {
            for (item in list.split(File.pathSeparator.toRegex()).dropLastWhile { it.isEmpty() }.toTypedArray()) {
                val directory = Paths.get(item)
                if (! Files.isDirectory(directory)) continue
                val file = directory.resolve(name)
                if (Files.isExecutable(file)) return file.toFile()
                val file_exe = file.resolveSibling("$name.exe")
                if (Files.isExecutable(file_exe)) return file_exe.toFile()
            }
            throw GradleException("executable file not found: $name")
        }
        val metalPath = providers.gradleProperty("metal.path")
            .orElse(providers.environmentVariable("PATH"))

        val target = project.providers.gradleProperty("metal.target").orElse("default").get()
        val tool = metalPath.map { locateExecutableFile(it,"qemu-system-x86_64").toString() }

        qemuExecutable.convention(tool)

        qemuArgs.debug.convention("cpu_reset,int")
        qemuArgs.debugConsole.convention("vc")
        qemuArgs.kernel.convention(imageFile)
        qemuArgs.gdb.convention("tcp:localhost:12345")
        qemuArgs.machine.convention("q35")
        qemuArgs.stop.convention(true)
    }

    @TaskAction
    fun action ()
    {
        execOperations.exec {
            executable = qemuExecutable.get()
            argumentProviders += qemuArgs
            errorOutput = File(temporaryDir, "qemu.err.txt").outputStream()
            standardOutput = File(temporaryDir, "qemu.out.txt").outputStream()
        }
    }
}

private data class Symbol (val name : String, val size : Long, val address : Long) { }

private class SymbolTable (val addresses : Map<Long,Symbol>, val names : Map<String,Symbol>)
{
    fun findByAddress (address : Long) = addresses[address]

    fun findByName (name : String) = names[name]

    companion object
    {
        fun from (symbols : List<Symbol>) : SymbolTable
        {
            val addresses = mutableMapOf<Long,Symbol>()
            val names = mutableMapOf<String,Symbol>()
            for (symbol in symbols) {
                addresses[symbol.address] = symbol
                names[symbol.name] = symbol
            }
            return SymbolTable(addresses,names)
        }

        fun parse32 (file : FileChannel, byteOrder : ByteOrder) : SymbolTable
        {
            val elf = ElfFileView32(file.map(MapMode.READ_ONLY, 0, 52).order(byteOrder))
            val sectionTable = ElfSectionTableView32(
                file.map(
                    MapMode.READ_ONLY, elf.sectionTableOffset().toLong(), elf.sectionEntrySize().toLong() * elf.sectionTableSize()
                )
                .order(byteOrder),
                elf.sectionEntrySize()
            )
            var strings = null as ElfStringTable?
            val symbolTables = java.util.ArrayList<ElfSymbolTableView32>()
            for (section in sectionTable) {
                val bytes = file.map(MapMode.READ_ONLY, section.offset().toLong(), section.size().toLong()).order(byteOrder)
                when (section.type()) {
                    2 -> symbolTables.add(ElfSymbolTableView32(bytes, section.entrySize()))
                    3 -> strings = ElfStringTable(bytes)
                }
            }
            val list = mutableListOf<Symbol>()
            if (strings != null) {
                for (symbolTable in symbolTables) {
                    for (symbol in symbolTable) {
                        val name = strings[symbol.name()].toString()
                        list.add(Symbol(name, symbol.size().toLong(), symbol.value().toLong()))
                    }
                }
            }
            return from(list)
        }

        fun parse64 (file : FileChannel, byteOrder : ByteOrder) : SymbolTable
        {
            val elf = ElfFileView64(file.map(MapMode.READ_ONLY, 0, 64).order(byteOrder))
            val sectionTable = ElfSectionTableView64(
                file.map(
                    MapMode.READ_ONLY, elf.sectionTableOffset(), elf.sectionEntrySize().toLong() * elf.sectionTableSize()
                )
                .order(byteOrder),
                elf.sectionEntrySize()
            )
            var strings = null as ElfStringTable?
            val symbolTables = java.util.ArrayList<ElfSymbolTableView64>()
            for (section in sectionTable) {
                val bytes = file.map(MapMode.READ_ONLY, section.offset(), section.size()).order(byteOrder)
                when (section.type()) {
                    2 -> symbolTables.add(ElfSymbolTableView64(bytes, section.entrySize().toInt()))
                    3 -> strings = ElfStringTable(bytes)
                }
            }
            val list = mutableListOf<Symbol>()
            if (strings != null){
                for (symbolTable in symbolTables) {
                    for (symbol in symbolTable) {
                        val name = strings[symbol.name()].toString()
                        list.add(Symbol(name, symbol.size(), symbol.value()))
                    }
                }
            }
            return from(list)
        }

        fun parse (file : FileChannel) : SymbolTable
        {
            val elf = ElfFileView(file.map(MapMode.READ_ONLY, 0, 16))
            val byteOrder = when (elf.encoding().toInt()) {
                1 -> ByteOrder.LITTLE_ENDIAN
                2 -> ByteOrder.BIG_ENDIAN
                else -> throw RuntimeException("file is not an ELF")
            }
            return when (elf.format().toInt()) {
                1 -> parse32(file,byteOrder)
                2 -> parse64(file,byteOrder)
                else -> throw RuntimeException("file is neither ELF32 nor ELF64")
            }
        }
    }
}

abstract class MultibootTestImageTask : DefaultTask()
{
    @get:InputFile
    abstract val executableFile : RegularFileProperty

    @get:InputFile
    abstract val imageFile : RegularFileProperty

    @Internal
    val port = ThreadLocalRandom.current().nextInt(20000, 40000)

    @get:Nested
    abstract val qemuArgs : QemuSystemEditor

    @get:Input
    abstract val qemuExecutable : Property<String>

    @get:Inject
    abstract val providers: ProviderFactory

    init
    {
        // TODO: expose Gradle Metal locateToolFile utility
        fun locateExecutableFile (list: String, name: String): File {
            for (item in list.split(File.pathSeparator.toRegex()).dropLastWhile { it.isEmpty() }.toTypedArray()) {
                val directory = Paths.get(item)
                if (! Files.isDirectory(directory)) continue
                val file = directory.resolve(name)
                if (Files.isExecutable(file)) return file.toFile()
                val file_exe = file.resolveSibling("$name.exe")
                if (Files.isExecutable(file_exe)) return file_exe.toFile()
            }
            throw GradleException("executable file not found: $name")
        }
        val metalPath = providers.gradleProperty("metal.path")
            .orElse(providers.environmentVariable("PATH"))

        val target = project.providers.gradleProperty("metal.target").orElse("default").get()
        val tool = metalPath.map { locateExecutableFile(it,"qemu-system-x86_64").toString() }

        qemuArgs.apply {
            debug.set("cpu_reset,int")
            display.set("none")
            kernel.set(imageFile)
            this.gdb.set("tcp:localhost:${port}")
            machine.set("q35")
            rtc {
                base.set("2020-07-24T22:46:00")
            }
            characterDevice("file") {
                options.put("path", File(temporaryDir, "qemu.debugcon.txt").toString())
                options.put("id", "debugcon")
            }
            debugConsole.set("chardev:debugcon")
            stop.set(true)
        }

        qemuExecutable.convention(tool)
    }

    @TaskAction
    fun action ()
    {
        logger.info("${project.path}:${this.name}: executableFile = ${executableFile.get()}")
        logger.info("${project.path}:${this.name}: imageFile = ${imageFile.get()}")

        val symbols = FileChannel.open( executableFile.asFile.get().toPath() ).use { SymbolTable.parse(it) }
        val control = symbols.findByName("_test_control") ?: throw RuntimeException("_test_control not found")
        val debug = symbols.findByName("_test_debug") ?: throw RuntimeException("_test_debug not found")
        val finish = symbols.findByName("_test_finish") ?: throw RuntimeException("_test_finish not found")
        val start = symbols.findByName("_test_start") ?: throw RuntimeException("_test_start not found")

        val qemuProcess = ProcessBuilder()
            .command( listOf(qemuExecutable.get()) + qemuArgs.build() )
            .redirectError( File(temporaryDir, "qemu.error.txt") )
            .redirectOutput( File(temporaryDir, "qemu.out.txt") )
            .start()

        qemuProcess.waitFor(750, TimeUnit.MILLISECONDS)

        try
        {
            GdbRemote.from( InetSocketAddress("localhost",port) ).use {
                gdb ->

                // learn server features
                gdb.exchange("qSupported:hwbreak+;swbreak+;xmlRegisters+")

                // discover initial status
                gdb.exchange("?")

                // break once at _test_start
                gdb.exchange(format("Z1,%X,0",start.address))
                gdb.exchange("c")
                gdb.exchange(format("z1,%X,0",start.address))

                logger.info("! Test ${this}: START")

                // watch psys test data
                gdb.exchange(format("Z2,%X,%d",control.address,control.size))
                gdb.exchange(format("Z2,%X,%d",debug.address,debug.size))

                // continue up to _test_finish...
                gdb.exchange(format("Z1,%X,0",finish.address))

                // ...watching _test_control and _test_debug
                var previous = 0
                while (true)
                {
                    // continue until next stop
                    val response = gdb.exchange("c")
                    val stop = GdbRemoteParser.parseStop(response.content()) ?: throw RuntimeException("expected stop, got null")

                    // expect stop by TRAP
                    if (stop !is GdbRemoteStopSignal) throw RuntimeException("expected signal, got $stop")
                    if (! "05".contentEquals(stop.signal())) throw RuntimeException("expected TRAP, got ${stop.signal()}")

                    // if not watch then break, assume _test_finish
                    if (! stop.attributes().containsKey("watch")) break

                    // evaluate watch, assuming little-endian
                    val address = stop.attributes()["watch"]?.toLong(16)
                    val symbol = address?.let { it1 -> symbols.findByAddress(it1) } ?: continue
                    val memory = gdb.exchange(format("m%X,%d",address,symbol.size))
                    val value = Integer.reverseBytes( Integer.parseUnsignedInt( memory.content(),16 ) )

                    // interpret watch
                    if (symbol == control) {
                        if      (previous == 0 && value == 0) { }
                        else if (previous == 0 && value != 0) {
                            logger.info("! Test ${this.path}: stage ${previous}: ENTERING...")
                        }
                        else if (previous != 0 && value == 0) {
                            logger.error("! Test ${this.path}: stage ${previous}: FAILED")
                            throw RuntimeException("test ${this.path}: stage ${previous}: FAILED")
                        }
                        else {
                            logger.lifecycle("! Test ${this.path}: stage ${previous}: SUCCESS")
                            logger.info("! Test ${this.path}: stage ${previous}: ENTERING...")
                        }
                        previous = value
                    }
                    else if (symbol == debug) {
                        logger.info("! Test ${this.path}: stage ${previous}: DEBUG = ${value}")
                    }
                }

                // terminate
                logger.info("! Test ${this.path}: FINISH")
                gdb.exchange("k")
            }
        }
        finally
        {
            qemuProcess.destroy()
        }

        logger.info("${project.path}:${this.name}: QEMU completed with status = ${qemuProcess.exitValue()}")
    }
}