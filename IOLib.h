#ifndef IOLIB_H_INCLUDED
#define IOLIB_H_INCLUDED

namespace{
    extern "C" void foo();
    extern "C" void bar(int* c);
    extern "C" int increment(int i);
    extern "C" void inImage();
    extern "C" void outImage();
    extern "C" char getChar();
    extern "C" int getInPos();
    extern "C" void setInPos(int pos);
    extern "C" int retBufLen();
    extern "C" void putChar(char c);
    extern "C" void setOutPos(int pos);
    extern "C" int getOutPos();
    extern "C" void putText(char*);
    extern "C" int getText(char*, int);
}

#endif // IOLIB_H_INCLUDED
