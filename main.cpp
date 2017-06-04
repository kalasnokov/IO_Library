#include <iostream>
#include "IOLib.h"


using namespace std;
int main()
{
	__asm
	{
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
		.global putChar
		.global getOutPos
		.global setOutPos
		.global getText

		foo :

		mov $1, %rax
			mov $1, %rdi
			mov $msg, %rsi
			mov $len, %rdx
			syscall


			ret


			bar :

		mov %rdi, %rsi
			mov $1, %rax
			mov $1, %rdi
			mov $1, %rdx
			syscall


			ret


			increment :

		inc %rdi
			mov %rdi, %rax


			ret


			inImage : #clears the inBuf, resets inPos to 0 and then takes user input(rdi, clearbuf, rax, rsi, rdx, syscall)

			leaq inBuf, %rdi
			call clearBuf

			movq $0, inPos

			mov $READ, %rax
			mov $STDIN, %rdi
			mov $inBuf, %rsi
			mov $maxLen, %rdx
			syscall

			ret


			outImage : #prints the content in outBuf(rax, rdi, rsi, rdx, clearBuf, syscall)

			movq $0, outPos
			mov $WRITE, %rax
			mov $STDOUT, %rdi
			mov $outBuf, %rsi
			mov $maxLen, %rdx
			syscall
			leaq outBuf, %rdi
			call clearBuf

			ret


			putText : #receives rdi as loaded inBuf, places content of loaded buf in outBuf from outPos and onwards(rdi, rsi, r9, rax, inImage)

			mov %rdi, %rsi
			leaq outBuf, %rdi

			PTloop :
		lodsb

			mov outPos, %r9
			mov %al, (%rdi, %r9, 1)
			incq outPos

			cmp $maxLen, outPos
			jl PTcont
			pushq %rsi
			pushq %rdi

			call outImage

			popq %rdi
			popq %rsi
			PTcont :

		cmpb $0, %al
			jne PTloop


			ret


			clearBuf : #clears the buffert loaded in rdi(rdi, r9)

			mov $0, %r9
			CBloop :
		movq $0, (%rdi, %r9, 1)
			incq %r9
			cmpq $maxLen, %r9
			jle CBloop


			ret


			getChar : #returns char in inBuf[inPos], if inPos == 64 or inBuf length == 0 inImage will be called(rdi, rax, inImage, r8, r9)
			leaq inBuf, %rdi
			call getBufLen

			cmp $0, %rax
			jne GCcont1
			call inImage

			GCcont1 :

		cmp $64, inPos
			jne GCcont2
			call inImage

			GCcont2 :
		leaq inBuf, %r8
			mov inPos, %r9
			mov(%r8, %r9, 1), %rax


			ret


			getInPos : #returns inPos value(rax)

			movq inPos, %rax

			ret


			setInPos : #sets inPos value, if input > bufLen then inPos == bufLen or if input < 0 then inPos == 0 (rdi, rbx, rax)

			push %rbx
			cmp $0, %edi
			jg SIPcont
			movq $0, %rdi
			jmp SIPret

			SIPcont :

		movq %rdi, %rbx
			leaq inBuf, %rdi
			call getBufLen
			movq %rbx, %rdi

			cmpq %rax, %rdi
			jl SIPret
			movq %rax, %rdi
			subq $1, %rdi
			SIPret :
		movq %rdi, inPos

			pop %rbx


			ret


			getBufLen : #takes loaded array position in rdi, returns length in rax(rdi, rax, rsi)

			mov %rdi, %rsi #position of array is now in rsi
			mov $0, %rdi #rdi used as counter

			GBLloop :
		lodsb
			cmpb $0, %al
			jz GBLret
			cmp $65, %rdi
			jz GBLret

			inc %rdi
			jmp GBLloop

			GBLret :

		decq %rdi
			mov %rdi, %rax
			movq %rsi, %rdi

			ret


			retBufLen :

		leaq inBuf, %rdi
			call getBufLen


			ret


			putChar : #puts rdi at the outPos(rdi, r8, r9, outImage)

			leaq outBuf, %r8
			mov outPos, %r9
			mov %rdi, (%r8, %r9, 1)
			incq outPos

			cmp $maxLen, outPos
			jne PCret
			call outImage
			PCret :

		ret


			getOutPos :

		movq outPos, %rax


			ret


			setOutPos : #sets outPos value, if input > bufLen then outPos == bufLen or if input < 0 then outPos == 0 (rdi, rbx, rax)
			push %rbx
			cmp $0, %edi
			jg SOPcont
			movq $0, %rdi
			jmp SOPret

			SOPcont :

		movq %rdi, %rbx
			leaq outBuf, %rdi
			call getBufLen
			movq %rbx, %rdi

			cmpq %rax, %rdi
			jl SOPret
			movq %rax, %rdi
			subq $1, %rdi

			SOPret :

		movq %rdi, outPos
			pop %rbx

			ret


			getText : #receieves loaded address in rdi and lenght to read in rsi, writes the content of inBuf to the first argument

			leaq inBuf, %rcx #inBuf loaded into rcx

			movq $0, %r8 #used as counter for parameter 1
			mov inPos, %r9

			GTloop :
		mov(%rcx, %r9, 1), %rdx #char value now loaded in rdx
			incq %r9

			mov %rdx, (%rdi, %r8, 1) #char value moved to parameter 1 pos r8

			incq %r8

			cmpq $maxLen, %r9
			je GTret

			cmp %rsi, %r8
			je GTret

			jmp GTloop
			GTret :

		movq %r8, %rax

			ret


			exit :
		mov $0, %ebx
			mov $1, %eax
			int $0x80




			.data
			msg :
		.ascii "Hello?\n"
			len = . - msg

			startMsg :
		.ascii "Startup!\n"
			startMsgLen = . - startMsg

			inBuf : .space 64
			outBuf : .space 64
			workBuf : .space 64
			inPos : .quad 0
			outPos : .quad 0
			workPos : .quad 0

	}
    foo();
    int* i = new int('K');
    int* u = new int('U');
    int e = 'T';
    bar(i);
    bar(u);
    bar(&e);
    cout << increment(10) << endl;
    cout << endl;

    int k=0;
    //cin >> k;

    inImage();
    inImage();

    cout << "get/set start" << endl;

    setInPos(10);

    cout << "Char: " << getChar() << endl;
    cout << "Pos: " << getInPos() << endl;
    setInPos(5);
    cout << "Char: " << getChar() << endl;
    cout << "Pos: " << getInPos() << endl;

    cout << "Length: " << retBufLen() << endl;
    for(int i=0;i<100;i++){
        //putChar('V');
    }
    cout << "Pos: " << getOutPos() << endl;
    char* s = "My boy, this peace is what all true warriors strive for!";
    //putText(s);
    //outImage();
    char* t = " I just wonder what Ganon is up to. ";
    //putText(t);
    //outImage();
    char* v =  "My boy, this peace is what all true warriors strive for! I just wonder what Ganon is up to. You majesty, Ganon and his minions have seized the island of Koridai! Hmmm... How can we help? It is written: Only Link can defeat Ganon.";
    putText(v);
    outImage();
    //outImage();

    cout << endl;
    char t2[100];
    cout << getText(t2,10) << endl;
    //getText(t,0);
    for(int i=0;i<10;i++){
        cout << t2[i];
    }
    cout << endl;
        for(int i=0;i<10;i++){
        cout << (int)t2[i]<<" ";
    }
    cout << endl;

    cout <<endl<< "Code has returned and is exiting" << endl;
    return 0;
}
