#include "publicKeySystem.h"
#include <ctime>
#include <stdio.h>
#include "gmp.h"
#include "gmpxx.h"
#include <boost/multiprecision/gmp.hpp>
#include <boost/chrono/include.hpp>
#include <cmath>

using namespace std;
using namespace boost::multiprecision;
using namespace boost::chrono;

void getRandInput(mpz_t P1, mpz_t P2, mpz_t p, mpz_t a, mpz_t b, const int bits, gmp_randstate_t state);

int main(){
    mpz_int Wa[4], Wb[4];
    mpz_t P1, P2, p, a, b;
    gmp_randstate_t state;
    char* s;
    int bits = 64;
    double avgCount = 0;
    int errorCounter = 0;
    const int reps = 100;             //number of iterations per bit size


    mpz_inits(P1, P2, p, a, b, NULL);

    gmp_randinit_mt (state);
    gmp_randinit_default (state);

    gmp_randseed_ui(state, time(NULL));

    cout << "Delays are expected for larger prime generation" << endl << endl;
    for(int i=0; i<7; i++){
        for(int j= 0; j<reps; j++){
            getRandInput(P1, P2, p, a, b, bits, state);

            system_clock::time_point start = system_clock::now();
            if(!publicKey(Wa, Wb, P1, P2, 1, p, a, b))
                errorCounter++;

            avgCount += duration_cast<microseconds>(system_clock::now() - start).count();

        }
        cout << "Average for " << bits << " bit prime (over " << reps << " reps): " << avgCount/reps << " microseconds = " << (double)(avgCount/reps)/1000000 << " seconds" << endl;
        bits *= 2;
        avgCount = 0;
    }

    cout << endl << errorCounter << " errors" << endl;

    mpz_clears(P1, P2, p, a, b, NULL);
    gmp_randclear(state);

    return 0;
}



void getRandInput(mpz_t P1, mpz_t P2, mpz_t p, mpz_t a, mpz_t b, const int bits, gmp_randstate_t state){
    //P1 must be even, P2 must be odd and p must be prime
    mpz_urandomb (P1, state, bits);
    if(mpz_even_p(P1) == 0)
        mpz_add_ui(P1, P1, 1);

    //make P2 prime so gcd(P1, P2) will be 1
    mpz_urandomb (P2, state, bits);
    mpz_prevprime(P2, P2);

    mpz_urandomb (p, state, bits);
    mpz_nextprime(p, p);

    //generate random a and b values
    mpz_urandomb (a, state, bits);
    mpz_urandomb (b, state, bits);

    while (!validInput((mpz_int)P1, (mpz_int)P2, (mpz_int)p, 1, (mpz_int)a, (mpz_int)b))
        mpz_add_ui(P1, P1, 2);
}