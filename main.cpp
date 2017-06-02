#include <iostream>
#include "IOLib.h"
using namespace std;
int main()
{
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

    putChar('V');
    outImage();
    //outImage();

    cout <<endl<< "Code has returned and is exiting" << endl;
    return 0;
}
