  .set MULTIBOOT2_REQUEST_MAGIC, 0xE85250D6
  .set MULTIBOOT2_REQUEST_ARCHITECTURE_I386, 0
  .set MULTIBOOT2_RESPONSE_MAGIC, 0x36D76289

multiboot2_request:
  .long MULTIBOOT2_REQUEST_MAGIC
  .long MULTIBOOT2_REQUEST_ARCHITECTURE_I386
  .long (.Lmultiboot2_request_end - multiboot2_request)
  .long -(MULTIBOOT2_REQUEST_MAGIC + MULTIBOOT2_REQUEST_ARCHITECTURE_I386 + .Lmultiboot2_request_end - multiboot2_request)
.Lmultiboot2_request_tag_last:
  .short 0
  .short 0
  .long (.Lmultiboot2_request_end - .Lmultiboot2_request_tag_last)
.Lmultiboot2_request_end:

.globl _start
_start:
  // set stack
  mov $(stack + 0x4000), %esp
  // reset EFLAGS
  xor %ecx, %ecx
  push %ecx
  popf
  // validate multiboot2
  cmp $MULTIBOOT2_RESPONSE_MAGIC, %eax
  jne .Lfinish
  // call main
  call main
.Lfinish:
  cli
.Lhalt:
  hlt
  jmp .Lhalt

main:
  // push "PSYS" to QEMU debugcon
  mov  $0x50, %al
  outb %al, $0xE9
  mov  $0x53, %al
  outb %al, $0xE9
  mov  $0x59, %al
  outb %al, $0xE9
  mov  $0x53, %al
  outb %al, $0xE9
  ret

.comm stack, 0x4000