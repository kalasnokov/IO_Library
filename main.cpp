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
    cout << getChar() << endl;
    cout << getInPos() << endl;
    setInPos(5);
    cout << getInPos() << endl;

    cout << retBufLen() << endl;
    //outImage();

    cout << "Code has returned and is exiting" << endl;
    return 0;
}
