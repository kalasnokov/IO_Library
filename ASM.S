EXIT = 1
ERROR = 0

EOF = 1

STDIN = 0
STDOUT = 1
READ = 0
WRITE = 1

maxLen = 64

.text
    .global foo
    .global bar
    .extern printf
    .global increment
    .global inImage
    .global outImage
    .global putText
    .global clearBuf
    .global getChar
    .global getInPos
    .global setInPos
    .global getBufLen
    .global retBufLen

foo:

mov $1,%rax
mov $1,%rdi
mov $msg,%rsi
mov $len,%rdx
syscall


ret


bar:
mov %rdi,%rsi
mov $1,%rax
mov $1,%rdi
mov $1,%rdx
syscall


ret


increment:

inc %rdi
mov %rdi,%rax


ret


inImage:

mov $inBuf,%rdi
call clearBuf

movq $0,inPos

mov $READ,%rax
mov $STDIN,%rdi
mov $inBuf,%rsi
mov $maxLen,%rdx
syscall

ret


outImage:

mov $WRITE,%rax
mov $STDOUT,%rdi
mov $outBuf,%rsi
mov $maxLen,%rdx
syscall


ret


putText:

subq $8,outBuf


ret


clearBuf:

xor %rdi,%rdi


ret


getChar:

leaq inBuf,%r8
mov inPos,%r9
mov (%r8,%r9,1),%rax


ret


getInPos:

movq inPos,%rax


ret


setInPos:

movq %rdi,inPos


ret


getBufLen:

loop:
cmp $0,%rdi
je return

return:


ret


retBufLen:

movq $inBuf,%rdi
call getBufLen


ret


exit:
mov $0,%ebx
mov $1,%eax
int $0x80

.data
msg:
    .ascii "Hello?\n"
    len = . - msg

startMsg:
    .ascii "Startup!\n"
    startMsgLen = . - startMsg

inBuf: .space 64
outBuf: .space 64
workBud: .space 64
inPos: .quad 0
outPos: .quad 0
workPos: .quad 0
