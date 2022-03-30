package grub

import GrubConfigurationEditor
import GrubConfigurationEntryEditor
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test

class GrubConfigurationTest {
    @Test
    fun configurationEntryEditorTest () {
        assertEquals(
            "menuentry  {\r\n}",
            GrubConfigurationEntryEditor().toString()
        )

        assertEquals(
            "menuentry psys {\r\n}",
            GrubConfigurationEntryEditor().apply {
                name = "psys"
            }
            .toString()
        )

        assertEquals(
            "menuentry psys {\r\nmultiboot2 /root/program\r\n}",
            GrubConfigurationEntryEditor().apply {
                name = "psys"
                multiboot2("/root/program")
            }
            .toString()
        )

        assertEquals(
            "menuentry psys {\r\nmultiboot2 /root/program arg\r\n}",
            GrubConfigurationEntryEditor().apply {
                name = "psys"
                multiboot2("/root/program arg")
            }
            .toString()
        )

        assertEquals(
            "menuentry psys {\r\nmodule2 (memdisk)/module\r\n}",
            GrubConfigurationEntryEditor().apply {
                name = "psys"
                module2("(memdisk)/module")
            }
            .toString()
        )

        assertEquals(
            "menuentry psys {\r\nmodule2 (memdisk)/module arg\r\n}",
            GrubConfigurationEntryEditor().apply {
                name = "psys"
                module2("(memdisk)/module arg")
            }
            .toString()
        )
    }
    @Test
    fun configurationEditorTest () {
        assertEquals(
            "\r\n\r\n",
            GrubConfigurationEditor().toString()
        )

        assertEquals(
            "default = 0\r\n\r\n",
            GrubConfigurationEditor().apply {
                options["default"] = "0"
            }
            .toString()
        )

        assertEquals(
            "timeout = 0\r\n\r\n",
            GrubConfigurationEditor().apply {
                options["timeout"] = "0"
            }
            .toString()
        )

        assertEquals(
            "default = 0\r\ntimeout = 0\r\n\r\n",
            GrubConfigurationEditor().apply {
                options["default"] = "0"
                options["timeout"] = "0"
            }
            .toString()
        )

        assertEquals(
            "default = 0\r\ntimeout = 0\r\nmenuentry psys {\r\nmultiboot2 (memdisk)/application\r\n}\r\n",
            GrubConfigurationEditor().apply {
                options["default"] = "0"
                options["timeout"] = "0"
                entries += GrubConfigurationEntryEditor().apply {
                    name = "psys"
                    multiboot2("(memdisk)/application")
                }
            }
            .toString()
        )

        assertEquals(
            "default = 0\r\ntimeout = 0\r\nmenuentry psys {\r\nmultiboot2 (memdisk)/bridge\r\nmodule2 (memdisk)/application\r\n}\r\n",
            GrubConfigurationEditor().apply {
                options["default"] = "0"
                options["timeout"] = "0"
                entries += GrubConfigurationEntryEditor().apply {
                    name = "psys"
                    multiboot2("(memdisk)/bridge")
                    module2("(memdisk)/application")
                }
            }
            .toString()
        )
    }
}
