#include <math.h>
#include <algorithm>
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include "jacobi/include/jacobi.h"
#include "publicKeySystem.h"
 
using namespace std;

long long getBinaryDigits(long long n);
long long square (long long num, long long p);
long long gcd(long long a, long long b);

bool publicKey(long long Wa[4], long long Wb[4], long long P1, long long P2, long long Q, long long p, long long max1, long long max2){
    long long La, Ka, Lb, Kb;
    long long delta = ((long long)(pow((double)P1, 2)) - 4*P2) % p;

    //Alice calls the first double and add algorithm
    doubleAndAddOne(Wa, max1, P1, P2, Q, p, delta);
    //Alice send La and Ka to Bob
    La = Wa[0];
    Ka = Wa[1];
        
    //Bob calls the first double and add algorithm
    doubleAndAddOne(Wb, max2, P1, P2, Q, p, delta);
    //Bob sends Lb and Kb to Alice
    Lb = Wb[0];
    Kb = Wb[1];

    //Alice calls the second double and add algorithm
    Wa[0] = Lb;
    doubleAndAddTwo(Wa, max1, P1, P2, Q, p, delta*square(Kb, p) % p);

    //Bob calls the second double and add algorithm
    Wb[0] = La;
    doubleAndAddTwo(Wb, max2, P1, P2, Q, p, delta*square(Ka, p) % p);

    Wa[0] = positiveMod(Wa[0], p);
    Wb[0] = positiveMod(Wb[0], p);

    if(Wa[0] == Wb[0])
        return true;

    return false;
}

bool getInitialValues(long long &P1, long long &P2, long long &max1, long long &max2, long long &p){
    cout << "Enter P1: ";
    cin >> P1;
    cout << "Enter P2: ";
    cin >> P2;
    cout << "Enter p: ";
    cin >> p;
    cout << "Enter a: ";
    cin >> max1;
    cout << "Enter b: ";
    cin >> max2;

    return validInput(P1, P2, p, 1, max1, max2);
}

//Function for testing
bool setInitialValues(long long &P1, long long &P2, long long &Q, long long &max1, long long &max2, long long &p){
    P1 = 4;     //2|P1
    P2 = 15;    
    Q = 1;      //Q will always equal 1 for the crypto algorithm
    max1 = 3;
    max2 = 5;
    p = 179;

    return validInput(P1, P2, p, Q, max1, max2);
}

bool validInput(long long P1, long long P2, long long p, long long Q, long long a, long long b){
    long long delta = square(P1, p) - 2*P2;
    long long E = square(P2 + 4 * Q, p) - (4 * Q * square(P1, p));
    long long D = E * square(delta, p) * square(Q, p);

    //legendre
    if (a != 0 && b != 0 && P1%2 == 0 && p%P1 != 0 && p%D != 0 && gcd(P1, P2) == 1 && jacobi_new(&delta, &p) == -1 && jacobi_new(&E, &p) == -1)
        return true;

    return false;
}

void doubleAndAddOne(long long wPrev[4], long long max, long long P1, long long P2, long long Q, long long p, long long delta){
    long long L1, K1;
    long long *A = &wPrev[0], *B = &wPrev[1], *C = &wPrev[2], *D = &wPrev[3]; //so equations resemble those in the paper
    long long U2 = P1;
    long long V2 = ((long long)(pow((double)P1, 2)) - 2*P2 - 4*Q) % p;
    long long wNext[4];                                                       //Wi+1 representing {Lm, Km, Lm+1, Km+1}
    long long h = getBinaryDigits(max);
    boost::dynamic_bitset<> m(h, max);                                  //binary expansion of max

    //Set initial values L1, K1 for W0
    wPrev[0] = V2/(2*Q) % p;
    L1 = wPrev[0];
    wPrev[1] = U2/(2*Q) % p;
    K1 = wPrev[1];
    //Set L2 and K2 using (5)
    wPrev[2] = ((long long)(pow((double)wPrev[0], 2)) + delta * (long long)(pow((double)wPrev[1], 2)) - 2) % p;
    wPrev[3] = (2 * wPrev[0] * wPrev[1]) % p;

    //Compute Wi+1 using Wi until Wh = {Lm, Km, Lm+1, Km+1}
    for(long long i = h-1; i > 0; i--){
        if(m[i-1] == 0){
            wNext[0] = (square(*A, p) + delta * square(*B, p) - 2) % p;
            wNext[1] = (2 * *A * *B) % p;
            wNext[2] = (*A * *C + delta * *B * *D - L1) % p;
            wNext[3] = (*B * *C + *A * *D - K1) % p;
        }
        else{
            wNext[0] = (*A * *C + delta * *B * *D - L1) % p;
            wNext[1] = (*B * *C + *A * *D - K1) % p;
            wNext[2] = (square(*C, p) + delta * square(*D, p) - 2) % p;
            wNext[3] = (2 * *C * *D) % p;
        }

        //reset wPrev as wNext
        copy(wNext, wNext+4, wPrev);
    }

    return;
}

void doubleAndAddTwo(long long wPrev[4], long long max, long long P1, long long P2, long long Q, long long p, long long delta){
    long long *A = &wPrev[0], *B = &wPrev[1], *C = &wPrev[2], *D = &wPrev[3]; //so equations resemble those in the paper
    long long wNext[4];                                                       //Wi+1 representing {Lm, Jm, Lm+1, Jm+1}
    long long L1;
    long long h = getBinaryDigits(max);
    boost::dynamic_bitset<> m(h, max);                                  //binary expansion of max

    //Set L2 and J2 using (8) to get w0 = {L1, 1, L2, J2}
    L1 = wPrev[0];
    wPrev[1] = 1;
    wPrev[2] = (square(L1, p) + delta - 2) % p;
    wPrev[3] = (2 * L1) % p;

    //Comput Wi+1 using Wi until Wh = {Lm, Jm, Lm+1, Jm+1}
    for(long long i = h-1; i > 0; i--){
        if(m[i-1] == 0){
            wNext[0] = (square(*A, p) + delta * square(*B, p) -2) % p;
            wNext[1] = (2 * *A * *B) % p;
            wNext[2] = (*A * *C + delta * *B * *D - L1) % p;
            wNext[3] = (*B * *C + *A * *D - 1) % p;
        }
        else{
            wNext[0] = (*A * *C + delta * *B * *D - L1) % p;
            wNext[1] = (*B * *C + *A * *D - 1) % p;
            wNext[2] = (square(*C, p) + delta * square(*D, p) - 2) % p;
            wNext[3] = (2 * *C * *D) % p;
        }

        //reset wPrev as wNext
        copy(wNext, wNext+4, wPrev);
    }

    return;
}

long long square (long long num, long long p){
    return (long long)pow((double) num, 2) % p;
}

//return the positive value of n mod p
long long positiveMod (long long n, long long p){
    n = n % p;
    if(n < 0)
        n = n+p;

    return n;
}

//given a decimal long longeger, return the number of digits in the binary expansion of that number
long long getBinaryDigits(long long n){
    return 1 + (long long) log2 ((double) n);
}

//https://www.geeksforgeeks.org/gcd-in-cpp/
long long gcd(long long a, long long b) 
{ 
    // Everything divides 0 
    if (a == 0) 
        return b; 
    if (b == 0) 
        return a; 
  
    // base case 
    if (a == b) 
        return a; 
  
    // a is greater 
    if (a > b) 
        return gcd(a - b, b); 
    return gcd(a, b - a); 
}