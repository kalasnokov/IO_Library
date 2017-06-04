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
    extern "C" void setOutPos(int position);
    extern "C" int getOutPos();
    extern "C" void putText(char* appender);
    extern "C" int getText(char* append_string, int amount_to_read);
    extern "C" void putInt(int value);
    extern "C" int getInt();
}

#endif // IOLIB_H_INCLUDED
