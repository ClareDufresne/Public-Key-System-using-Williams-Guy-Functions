#include "publicKeySystem.h"
#include <iostream>

using namespace std;

int main(){
    long long Wa[4], Wb[4];       //representing {Lm, Km, Lm+1, Km+1}
    long long max1, max2;         //i value representing the number of times the algorithm is to be repeated
    long long P1, P2, p;
    long long Q = 1;

    //Eventually need to change this to calculate only Alice or Bob's information

    while (!getInitialValues(P1, P2, max1, max2, p)){
        cout << "Invalid input" << endl << endl;
    }
    if(publicKey(Wa, Wb, P1, P2, Q, p, max1, max2)){
        //Show that the results are the same
        cout << "L" << max1 << "," << max2 << ": " << positiveMod(Wa[0], p) << endl;
        cout << "L" << max2 << "," << max1 << ": "  << positiveMod(Wb[0], p) << endl;
    }
    else
        cout << "Error Keys do not match" << endl;

    return 0;
}