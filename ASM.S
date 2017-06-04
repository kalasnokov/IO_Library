ERROR = 0

EOF = 1

STDIN = 0
STDOUT = 1
READ = 0
WRITE = 1

maxLen = 64

.text
    .global inImage
    .global outImage
    .global putText
    .global clearBuf
    .global getChar
    .global getInPos
    .global setInPos
    .global getBufLen
    .global retBufLen
    .global putChar
    .global getOutPos
    .global setOutPos
    .global getText
    .global putInt
    .global getInt

inImage: #clears the inBuf, resets inPos to 0 and then takes user input (rdi,clearbuf,rax,rsi,rdx,syscall)

    leaq inBuf,%rdi
    call clearBuf

    movq $0,inPos

    mov $READ,%rax
    mov $STDIN,%rdi
    mov $inBuf,%rsi
    mov $maxLen,%rdx
    syscall

ret


outImage: #prints the content in outBuf (rax,rdi,rsi,rdx,clearBuf,syscall)

    movq $0,outPos
    mov $WRITE,%rax
    mov $STDOUT,%rdi
    mov $outBuf,%rsi
    mov $maxLen,%rdx
    syscall
    leaq outBuf,%rdi
    call clearBuf

ret


putText: #receives rdi as loaded inBuf, places content of loaded buf in outBuf from outPos and onwards (rdi,rsi,r9,rax,inImage)

    mov %rdi,%rsi
    leaq outBuf,%rdi

    PTloop:
    lodsb

    mov outPos,%r9
    mov %al,(%rdi,%r9,1)
    incq outPos

    cmp $maxLen,outPos
    jl PTcont
    pushq %rsi
    pushq %rdi

    call outImage

    popq %rdi
    popq %rsi
    PTcont:

    cmpb $0,%al
    jne PTloop


ret


clearBuf: #clears the buffert loaded in rdi (rdi,r9)

    mov $0,%r9
    CBloop:
    movq $0,(%rdi,%r9,1)
    incq %r9
    cmpq $maxLen,%r9
    jle CBloop


ret

/*Rutinen ska tolka en sträng som börjar på aktuell buffertposition i inbufferten och fortsätta
tills ett tecken som inte kan ingå i ett heltal påträffas. Den lästa substrängen översätts till
heltalsformat och returneras. Positionen i bufferten ska vara det första tecken som inte
ingick i det lästa talet när rutinen lämnas. Inledande blanktecken i talet ska vara tillåtna.
april, 2017 3
Bibliotek för in- och utmatning
(Intel x64 assembler) DV1464/DV1493
Ett plustecken eller ett minustecken ska kunna inleda talet och vara direkt följt av en eller
flera heltalssiffror. Ett tal utan inledande plus eller minus ska alltid tolkas som positivt.
Om inmatningsbufferten är tom eller om den aktuella positionen i inmatningsbufferten
är vid dess slut vid anrop av getInt ska getInt kalla på inImage, så att getInt alltid
returnerar värdet av ett inmatat tal.*/

getInt: #(rbx,rcx,r11,r10,rax,rsi)
    movq $0,%rbx //counter
    movq $0,%rcx //total
    movq $1,%r11 //tecken
    GIloop:
    call getChar
    cmp $32,%rax //om space tecken, loopa till nästa tecken
    addq $1,inPos
    je GIloop
    cmp $43,%rax //om + tecken, notera detta i tecken-variabeln och loopa vidare
    movq $1,%r11
    addq $1,inPos
    je GIloop
    cmp $45,%rax //om - tecken, notera detta i tecken-variabeln och loopa vidare
    movq $-1,%r11
    addq $1,inPos
    je GIloop
    cmp $48,%rax //om lägre än ascii 48, exit
    jl GIexit
    cmp $57,%rax //om högre än ascii 57, exit
    jg GIexit
    //kommer vi hit har vi en "siffra char" i rax
    subq $48,%rax //subbar ascii offset
    movq $1,%rsi
    cmpq $0,%rbx
    je GITenSkip
    movq %rbx,%r10
    GITenloop: //ska multiplicera rsi(1 från början) med 10, %r10 gånger
    imulq $10,%rsi
    cmpq $0,%r10
    jg GITenloop
    GITenSkip:
    imulq %rsi,%rax //multiplicerar nuvarande tal med rätt 10 mul, (om vi inte gick in tenloopen är denna 1)
    addq %rax,%rcx //adderar det till totalen
    addq $1,inPos
    jmp GIloop //går vidare till nästa position
    GIexit:
    mov %rcx,%rax //lägger över totalen i rax och returnar
ret

getChar: #returns char in inBuf[inPos], if inPos == 64 or inBuf length == 0 inImage will be called (rdi,rax,inImage,r8,r9)
    leaq inBuf,%rdi
    call getBufLen

    cmp $0,%rax
    jne GCcont1
    call inImage

    GCcont1:

    cmp $64,inPos
    jne GCcont2
    call inImage

    GCcont2:
    leaq inBuf,%r8
    mov inPos,%r9
    mov (%r8,%r9,1),%rax


    ret


    getInPos: #returns inPos value (rax)

    movq inPos,%rax

ret


setInPos: #sets inPos value, if input > bufLen then inPos == bufLen or if input < 0 then inPos == 0 (rdi,rbx,rax)

    push %rbx
    cmp $0,%edi
    jg SIPcont
    movq $0,%rdi
    jmp SIPret

    SIPcont:

    movq %rdi,%rbx
    leaq inBuf,%rdi
    call getBufLen
    movq %rbx,%rdi

    cmpq %rax,%rdi
    jl SIPret
    movq %rax,%rdi
    subq $1,%rdi
    SIPret:
    movq %rdi,inPos

    pop %rbx


ret


getBufLen: #takes loaded array position in rdi, returns length in rax (rdi,rax,rsi)

    mov %rdi,%rsi #position of array is now in rsi
    mov $0,%rdi #rdi used as counter

    GBLloop:
    lodsb
    cmpb $0,%al
    jz GBLret
    cmp $65,%rdi
    jz GBLret

    inc %rdi
    jmp GBLloop

    GBLret:

    decq %rdi
    mov %rdi, %rax
    movq %rsi,%rdi

ret


    retBufLen:

    leaq inBuf,%rdi
    call getBufLen


ret


putChar: #puts rdi at the outPos (rdi,r8,r9,outImage)

    leaq outBuf,%r8
    mov outPos,%r9
    mov %rdi,(%r8,%r9,1)
    incq outPos

    cmp $maxLen,outPos
    jne PCret
    call outImage
    PCret:

    ret


    getOutPos:

    movq outPos,%rax


ret


setOutPos:  #sets outPos value, if input > bufLen then outPos == bufLen or if input < 0 then outPos == 0 (rdi,rbx,rax)
    push %rbx
    cmp $0,%edi
    jg SOPcont
    movq $0,%rdi
    jmp SOPret

    SOPcont:

    movq %rdi,%rbx
    leaq outBuf,%rdi
    call getBufLen
    movq %rbx,%rdi

    cmpq %rax,%rdi
    jl SOPret
    movq %rax,%rdi
    subq $1,%rdi

    SOPret:

    movq %rdi,outPos
    pop %rbx

ret


getText: #receieves loaded address in rdi and lenght to read in rsi, writes the content of inBuf to the first argument (rcx,r8,r9,rdx,rdi,rax,rsi,rax)

    leaq inBuf,%rcx #inBuf loaded into rcx

    movq $0,%r8 #used as counter for parameter 1
    mov inPos,%r9

    GTloop:
    mov (%rcx,%r9,1),%rdx #char value now loaded in rdx
    incq %r9

    mov %rdx,(%rdi,%r8,1) #char value moved to parameter 1 pos r8

    incq %r8

    cmpq $maxLen,%r9
    je GTret

    cmp %rsi,%r8
    je GTret

    jmp GTloop
    GTret:

    movq %r8,%rax

ret

putInt: #places the argument rdi in the outBuf at the outPos location (rdi,rax,rdx)

    push %r12
    movq $0,%r12 #if r12 = 0, param is negative, if r12 = 1, param is positive

    bt $31,%rdi
    jc PIneg

        movq $1,%r12
        notq %rdi

        addq $1,%rdi

    PIneg:
    notq %rdi

    addq $1,%rdi

    movq %rdi,%rax
    movq $0,%r9


    PIloop1:

        movq $0,%rdx
        mov $10,%edi #delare satt till 10

        idiv %edi #dela rax med 10


        incq %r9 #räkna upp ett steg

        pushq %rdx

    cmp $0,%rax #om rax = 0 så kan vi ej dela mer
    jne PIloop1

    leaq outBuf,%rdi


    cmp $0,%r12
    jne PIpos

        mov outPos,%r10
        mov $'-',%r8
        mov %r8,(%rdi,%r10,1)
        incq outPos

    PIpos:

    PIloop2:

        popq %r8
        addq $48,%r8
        mov outPos,%r10
        mov %r8,(%rdi,%r10,1)
        incq outPos
        decq %r9

    cmp $0,%r9
    jne PIloop2

    pop %r12

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
workBuf: .space 64
inPos: .quad 0
outPos: .quad 0
workPos: .quad 0

