#include "publicKeySystem.h"
#include "gmp.h"
#include "gmpxx.h"
#include <boost/multiprecision/gmp.hpp>
#include <iostream>
 
using namespace std;
using namespace boost::multiprecision;

void individualKeys();
void bothKeys();

int main(){
    individualKeys();    

    return 0;
}

void individualKeys(){
    getKey();
}

void bothKeys(){
    mpz_int Wa[4], Wb[4];       //representing {Lm, Km, Lm+1, Km+1}
    mpz_int max1, max2;         //i value representing the number of times the algorithm is to be repeated
    mpz_int P1, P2, p;
    const mpz_int Q = 1;
 
    while (!getInitialValues(P1, P2, max1, max2, p)){
        cout << "Invalid input" << endl << endl;
    }
    if(publicKey(Wa, Wb, P1, P2, Q, p, max1, max2)){
        //Show that the results are the same
        cout << "L" << max1 << "," << max2 << ": " << positiveMod(Wa[0], p) << endl;
        cout << "L" << max2 << "," << max1 << ": "  << positiveMod(Wb[0], p) << endl;
    }
    else{
        cout << "Error Keys do not match" << endl;
        cout << "L" << max1 << "," << max2 << ": " << positiveMod(Wa[0], p) << endl;
        cout << "L" << max2 << "," << max1 << ": "  << positiveMod(Wb[0], p) << endl; 
    }
}