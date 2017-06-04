#include <iostream>
#include "IOLib.h"


using namespace std;
int main()
{

    int k=0;
    //cin >> k;

    inImage();
    inImage();

    cout << "Found int: " << getInt() << endl;

    cout << "get/set start" << endl;

    setInPos(10);

    cout << "Char: " << getChar() << endl;
    cout << "Pos: " << getInPos() << endl;
    setInPos(0);
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

    cout << "Pos: " << getInPos() << endl;
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

    putInt(-11230);

    outImage();

    cout <<endl<< "Code has returned and is exiting" << endl;
    return 0;
}
