#include <math.h>
#include "gmp.h"
#include "gmpxx.h"
#include <boost/multiprecision/gmp.hpp>
#include <boost/dynamic_bitset.hpp>
#include "publicKeySystem.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost::multiprecision;

mpz_int square (mpz_int num, mpz_int p);
mpz_int square_sec (mpz_int num, mpz_int p);
void generateValues(mpz_t P1, mpz_t P2, mpz_t p, mpz_int &a);
bool getIndividualInitialValues(mpz_int &P1, mpz_int &P2, mpz_int &a, mpz_int &p);
vector<bool> decToBinary(mpz_int n, int &numDigits);

//To be called by an individual
void getKey(){
    mpz_int W[4];               //representing {Lm, Km, Lm+1, Km+1}
    mpz_int a;                  //secret key
    mpz_int P1, P2, p;
    const mpz_int Q = 1;
    mpz_int La, Ka, Lb, Kb, delta; 
    
    individualInput(P1, P2, p, a);

    delta = (square(P1, p) - (4*P2)) % p;

    //Alice calls the first double and add algorithm
    doubleAndAddOne(W, a, P1, P2, Q, p, delta);

    //Alice send La and Ka to Bob
    La = positiveMod(W[0], p);
    Ka = positiveMod(W[1], p);
    cout << endl << "Send these initial values to the intended correspondant: " << endl;
    cout << "L: ";
    if(!mpz_out_str(NULL, 16, La.backend().data()))
        cout << "ERROR" << endl;
    cout << endl  << endl << "K: ";
    if(!mpz_out_str(NULL, 16, Ka.backend().data()))
        cout << "ERROR" << endl;
    cout << endl << endl;

    //Bob sends Lb and Kb to Alice
    cout << "Your correspondant should have sent you their initial values (in hex). Enter them here:" << endl;
    cout << "L: ";
    if(!mpz_inp_str(Lb.backend().data(), NULL, 16))
        cout << "ERROR" << endl;
    cout << "K: ";
    if(!mpz_inp_str(Kb.backend().data(), NULL, 16))
        cout << "ERROR" << endl;

    //Alice calls the second double and add algorithm
    W[0] = Lb;
    doubleAndAddTwo(W, a, P1, P2, Q, p, delta*square(Kb, p) % p);

    W[0] = positiveMod(W[0], p);

    cout << endl << "Shared key 1: ";
    if(!mpz_out_str(NULL, 16, W[0].backend().data()))
        cout << "ERROR" << endl;
    cout << endl << endl;
    cout << "Shared key 2: ";
    if(!mpz_out_str(NULL, 16, positiveMod(Kb * W[1], p).backend().data()))
        cout << "ERROR" << endl;
    cout << endl << endl;
    cout << "Keep these keys secret" << endl;
}

void individualInput(mpz_int &P1, mpz_int &P2, mpz_int &p, mpz_int &a){
    string choice = "";

    while(choice != "y" && choice != "n"){
        cout << "Would you like to generate values for P1, P2, and p? (y/n): ";
        cin >> choice;
    }
    if(choice == "y")
        generateValues(P1.backend().data(), P2.backend().data(), p.backend().data(), a);
    else{
        while(!getIndividualInitialValues(P1, P2, a, p)){
            cout << "Invalid Input" << endl;
        }
    }
}

void generateValues(mpz_t P1, mpz_t P2, mpz_t p, mpz_int &a){
    gmp_randstate_t state;
    int bits = 0;

    while(bits < 10 || bits > 4096){
            cout << endl << "Size of prime: ";
            cin >> bits;
        }

        gmp_randinit_mt (state);
        gmp_randinit_default (state);
        secure_gmp_seed(state, bits);

        getRandInput(P1, P2, p, bits, state);

        gmp_randclear(state);


        cout << "P1: ";
        if(!mpz_out_str(NULL, 16, P1))
            cout << "ERROR" << endl;
        cout << endl << endl << "P2: ";
        if(!mpz_out_str(NULL, 16, P2))
            cout << "ERROR" << endl;
        cout << endl << endl << "p: ";
        if(!mpz_out_str(NULL, 16, p))
            cout << "ERROR" << endl;
        cout << endl << endl;
        cout << "Share these values with your correspondant" << endl << endl;

        cout << "Enter secret integer: ";
        cin >> a;
        while(!validInput((mpz_int)P1, (mpz_int)P2, (mpz_int)p, 1, a, 2)){
            cout << "Enter secret integer: ";
            cin >> a;
        }
}

//Entire algorithm when we have both secret keys
bool publicKey(mpz_int Wa[4], mpz_int Wb[4], mpz_int P1, mpz_int P2, mpz_int Q, mpz_int p, mpz_int max1, mpz_int max2){
    mpz_int La, Ka, Lb, Kb;
    mpz_int delta = (square(P1, p) - (4*P2)) % p;

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
    cout << "Enter P1 (in hex): ";
    if(!mpz_inp_str(P1.backend().data(), NULL, 16))
        cout << "ERROR" << endl;
    cout << "Enter P2 (in hex): ";
    if(!mpz_inp_str(P2.backend().data(), NULL, 16))
        cout << "ERROR" << endl;
    cout << "Enter p (in hex): ";
    if(!mpz_inp_str(p.backend().data(), NULL, 16))
        cout << "ERROR" << endl;
    cout << endl << "Enter a: ";
    cin >> max1;
    cout << "Enter b: ";
    cin >> max2;

    return validInput(P1, P2, p, 1, max1, max2);
}

bool getIndividualInitialValues(mpz_int &P1, mpz_int &P2, mpz_int &a, mpz_int &p){
    cout << "Enter P1 (in hex): ";
    if(!mpz_inp_str(P1.backend().data(), NULL, 16))
        cout << "ERROR" << endl;
    cout << "Enter P2 (in hex): ";
    if(!mpz_inp_str(P2.backend().data(), NULL, 16))
        cout << "ERROR" << endl;
    cout << "Enter p (in hex): ";
    if(!mpz_inp_str(p.backend().data(), NULL, 16))
        cout << "ERROR" << endl;
    cout << "Enter secret integer: ";
    cin >> a;

    return validInput(P1, P2, p, 1, a, 2);
}

bool validInput(mpz_int P1, mpz_int P2, mpz_int p, mpz_int Q, mpz_int a, mpz_int b){
    mpz_int delta = (square(P1, p) - 2*P2) % p;
    mpz_int E = (square(P2 + 4 * Q, p) - (4 * Q * square(P1, p))) % p;
    mpz_int D = (E * square(delta, p) * square(Q, p)) % p;
	mpz_t gcd;     //legendre function uses the underlying mpz_t type (for which mpz_int is a wrapper)

    mpz_init(gcd);
    mpz_gcd(gcd, P1.backend().data(), P2.backend().data());

    if (Q == 1 && D != 0 && P1 != 0 && a != 0 && b != 0 && P1%2 == 0 && p%P1 != 0 && p%D != 0 && mpz_cmp_si(gcd, 1) == 0 && mpz_legendre(delta.backend().data(), p.backend().data()) == -1 && mpz_legendre(E.backend().data(), p.backend().data()) == -1){
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
    mpz_int V2 = (square(P1, p) - 2*P2 - 4*Q) % p;
    mpz_int wNext[4];                                                       //Wi+1 representing {Lm, Km, Lm+1, Km+1}
    int h = 0;                                                              //number of digits in the binary expansion of max
    vector<bool> m = decToBinary(max, h);

    //Set initial values L1, K1 for W0
    wPrev[0] = V2/(2*Q) % p;
    L1 = wPrev[0];
    wPrev[1] = U2/(2*Q) % p;
    K1 = wPrev[1];
    //Set L2 and K2 using (5)
    wPrev[2] = (square(wPrev[0], p) + delta * square(wPrev[1], p) - 2) % p;
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
            wNext[0] = (square_sec(*A, p) + delta * square_sec(*B, p) -2) % p;
            wNext[1] = (2 * *A * *B) % p;
            wNext[2] = (*A * *C + delta * *B * *D - L1) % p;
            wNext[3] = (*B * *C + *A * *D - 1) % p;
        }
        else{
            wNext[0] = (*A * *C + delta * *B * *D - L1) % p;
            wNext[1] = (*B * *C + *A * *D - 1) % p;
            wNext[2] = (square_sec(*C, p) + delta * square_sec(*D, p) - 2) % p;
            wNext[3] = (2 * *C * *D) % p;
        }

        //reset wPrev as wNext
        copy(wNext, wNext+4, wPrev);
    }

    return;
}

mpz_int square (mpz_int num, mpz_int p){
    mpz_int rop;
    mpz_int exp = 2;

    mpz_powm (rop.backend().data(), num.backend().data(), exp.backend().data(), p.backend().data());

    return rop;
}

mpz_int square_sec (mpz_int num, mpz_int p){
    mpz_int rop;
    mpz_int exp = 2;

    mpz_powm_sec(rop.backend().data(), num.backend().data(), exp.backend().data(), p.backend().data());

    return rop;
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

void getRandInput(mpz_t P1, mpz_t P2, mpz_t p, const int bits, gmp_randstate_t state){
    //P1 must be even, P2 must be odd and p must be prime
    mpz_urandomb (P1, state, bits);
    if(mpz_even_p(P1) == 0)
        mpz_add_ui(P1, P1, 1);

    //P2 must be odd since gcd(P1, P2) = 1
    mpz_urandomb (P2, state, bits);
    if(mpz_odd_p(P2) == 0)
        mpz_add_ui(P2, P2, 1);


    mpz_urandomb (p, state, bits);
    mpz_nextprime(p, p);

    while (!validInput((mpz_int)P1, (mpz_int)P2, (mpz_int)p, 1, 3, 4))
        mpz_add_ui(P1, P1, 2);
}


void secure_gmp_seed(gmp_randstate_t state, int bits) {
    const size_t SEED_BYTES = (static_cast<size_t>(bits) + 7) / 8;
    vector<char> buffer(SEED_BYTES);

    //Read the secure bytes from the OS's non-blocking random source
    ifstream urandom("/dev/urandom", ios::in | ios::binary);
    if (!urandom) {
        cerr << "Error: Could not open /dev/urandom for secure seeding." << endl;
        return;
    }
    
    urandom.read(buffer.data(), SEED_BYTES);
    urandom.close();

    // Convert the byte array into an mpz_t 
    mpz_t seed_val;
    mpz_init(seed_val);
    mpz_import(seed_val, SEED_BYTES, 1, 1, 0, 0, buffer.data());

    //Seed the state with the large, secure GMP integer
    gmp_randseed(state, seed_val);
    
    mpz_clear(seed_val);
}