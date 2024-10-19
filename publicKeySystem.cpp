#include <math.h>
#include "gmp.h"
#include "gmpxx.h"
#include <boost/multiprecision/gmp.hpp>
#include <boost/dynamic_bitset.hpp>
//#include "jacobi/include/jacobi.h"
#include "publicKeySystem.h"
#include <iostream>

using namespace std;
using namespace boost::multiprecision;

//int getBinaryDigits(mpz_int n);
vector<bool> decToBinary(mpz_int n, int &numDigits);
mpz_int square (mpz_int num, mpz_int p);
mpz_int gcd(mpz_int a, mpz_int b);

bool publicKey(mpz_int Wa[4], mpz_int Wb[4], mpz_int P1, mpz_int P2, mpz_int Q, mpz_int p, mpz_int max1, mpz_int max2){
    mpz_int a=0, b=1;
    mpz_int La, Ka, Lb, Kb;
    mpz_int delta = (pow(P1, 2) - (4*P2)) % p;

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

bool getInitialValues(mpz_int &P1, mpz_int &P2, mpz_int &max1, mpz_int &max2, mpz_int &p){
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
bool setInitialValues(mpz_int &P1, mpz_int &P2, mpz_int &Q, mpz_int &max1, mpz_int &max2, mpz_int &p){
    P1 = 4;     //2|P1
    P2 = 15;    
    Q = 1;      //Q will always equal 1 for the crypto algorithm
    max1 = 3;
    max2 = 5;
    p = 179;

    return validInput(P1, P2, p, Q, max1, max2);
}

bool validInput(mpz_int P1, mpz_int P2, mpz_int p, mpz_int Q, mpz_int a, mpz_int b){
    mpz_int delta = (square(P1, p) - 2*P2) % p;
    mpz_int E = (square(P2 + 4 * Q, p) - (4 * Q * square(P1, p))) % p;
    mpz_int D = (E * square(delta, p) * square(Q, p)) % p;
	mpz_t gcd;     //legendre function uses the underlying mpz_t type (for which mpz_int is a wrapper)

    mpz_init(gcd);
    mpz_gcd(gcd, P1.backend().data(), P2.backend().data());

    if (a != 0 && b != 0 && P1%2 == 0 && p%P1 != 0 && p%D != 0 && mpz_cmp_si(gcd, 1) == 0 && mpz_legendre(delta.backend().data(), p.backend().data()) == -1 && mpz_legendre(E.backend().data(), p.backend().data()) == -1){
        mpz_clear(gcd);
        return true;
    }

    mpz_clear(gcd);
    return false;
}
 
void doubleAndAddOne(mpz_int wPrev[4], mpz_int max, mpz_int P1, mpz_int P2, mpz_int Q, mpz_int p, mpz_int delta){
    mpz_int L1, K1;
    mpz_int *A = &wPrev[0], *B = &wPrev[1], *C = &wPrev[2], *D = &wPrev[3]; //so equations resemble those in the paper
    mpz_int U2 = P1;
    mpz_int V2 = (pow(P1, 2) - 2*P2 - 4*Q) % p;
    mpz_int wNext[4];                                                       //Wi+1 representing {Lm, Km, Lm+1, Km+1}
    int h = 0;                                                              //number of digits in the binary expansion of max
    vector<bool> m = decToBinary(max, h);
    //boost::dynamic_bitset<> m(h, max);                                  //binary expansion of max

    //Set initial values L1, K1 for W0
    wPrev[0] = V2/(2*Q) % p;
    L1 = wPrev[0];
    wPrev[1] = U2/(2*Q) % p;
    K1 = wPrev[1];
    //Set L2 and K2 using (5)
    wPrev[2] = (pow(wPrev[0], 2) + delta * pow(wPrev[1], 2) - 2) % p;
    wPrev[3] = (2 * wPrev[0] * wPrev[1]) % p;

    //Compute Wi+1 using Wi until Wh = {Lm, Km, Lm+1, Km+1}
    for(int i = h-1; i > 0; i--){
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

void doubleAndAddTwo(mpz_int wPrev[4], mpz_int max, mpz_int P1, mpz_int P2, mpz_int Q, mpz_int p, mpz_int delta){
    mpz_int *A = &wPrev[0], *B = &wPrev[1], *C = &wPrev[2], *D = &wPrev[3]; //so equations resemble those in the paper
    mpz_int wNext[4];                                                       //Wi+1 representing {Lm, Jm, Lm+1, Jm+1}
    mpz_int L1;
    int h = 0;                                                              //number of digits in the binary expansion of max
    vector<bool> m = decToBinary(max, h);
    
    //Set L2 and J2 using (8) to get w0 = {L1, 1, L2, J2}
    L1 = wPrev[0];
    wPrev[1] = 1;
    wPrev[2] = (square(L1, p) + delta - 2) % p;
    wPrev[3] = (2 * L1) % p;

    //Comput Wi+1 using Wi until Wh = {Lm, Jm, Lm+1, Jm+1}
    for(int i = h-1; i > 0; i--){
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

mpz_int square (mpz_int num, mpz_int p){
    return pow(num, 2) % p;
}

//return the positive value of n mod p
mpz_int positiveMod (mpz_int n, mpz_int p){
    n = n % p;
    if(n < 0)
        n = n+p;

    return n;
}

vector<bool> decToBinary(mpz_int n, int &numDigits)
{
	vector<bool> binaryNum;

	numDigits = 0;
	while (n > 0) {
		binaryNum.push_back((int)(n % 2));
		n = n / 2;
		numDigits++;
	}

	return binaryNum;
}

//given a decimal mpz_integer, return the number of digits in the binary expansion of that number
/*int getBinaryDigits(mpz_int n){
    return 1 + (mpz_int) log2 ((double) n);
}*/

//https://www.geeksforgeeks.org/gcd-in-cpp/
mpz_int gcd(mpz_int a, mpz_int b) 
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