#include "publicKeySystem.h"
#include "gmp.h"
#include "gmpxx.h"
#include <boost/multiprecision/gmp.hpp>
#include <iostream>

using namespace std;
using namespace boost::multiprecision;
 
int main(){
    mpz_int Wa[4], Wb[4];
    int counter = 0;
    mpz_int p1("5782935782937501517589374589012");
    mpz_int p2("57348957834692794073289071078914789175");
    mpz_int p("114826782447853736222709738832787700594077173068818371065416836151713391442277");

    mpz_int p1_1("57482935798047658916789178697189678196789175894738979878293789278922");
    mpz_int p2_1("21985718975107538271581783578192375817832758175897189256364534172890758913567810671");
    mpz_int p_1("11859976680394472864811041591105853062445438499113539460593341957778016878918097064653644712424603085934389167755979710805958511990357502000152407685025723");

    for(int i=18000; i<=18200; i++){
        for(int j=5122235; j<=5122735; j++){
            if(!publicKey(Wa, Wb, p1_1, p2_1, 1, p_1, i, j))
                counter++;
            cout << counter << " " << i << j << endl;
        }
    }
    cout << counter << " non-matching key pairs" << endl;
    cin.ignore();

    counter = 0;
    for(int i=18000; i<=19000; i++){
        for(int j=5122235; j<=5122735; j++){
            if(!publicKey(Wa, Wb, p1, p2, 1, p, i, j))
                counter++;
            cout << counter << " " << i << j << endl;
        }
    }
    cout << counter << " non-matching key pairs" << endl;
    cin.ignore();

    counter = 0;
    for(int i=65000; i<=65500; i++){
        for(int j=50000; j<=52000; j++){
            if(!publicKey(Wa, Wb, 8, 15, 1, 64853, i, j))
                counter++;
            cout << counter << " " << i << j << endl;
        }
    }
    cout << counter << " non-matching key pairs" << endl;
    cin.ignore();
    counter = 0;
    for(int i=28000; i<=29000; i++){
        for(int j=85000; j<=85500; j++){
            if(!publicKey(Wa, Wb, 930, 179, 1, 51481, i, j))
                counter++;
            cout << counter << " " << i << j << endl;
        }
    }
    cout << counter << " non-matching key pairs" << endl;
    cin.ignore();
    counter = 0;
    for(int i=2; i<=8; i++){
        for(int j=2; j<=8; j++){
            if(!publicKey(Wa, Wb, 10002, 43, 1, 11160307, i, j)){
                counter++;
                /*cout << "W" << i << "," << j << ": " << Wa[0] << " ";
                cout << "W" << j << "," << i << ": " << Wb[0] << endl;*/
            }
            cout << counter << " " << i << j << endl;
        }
    }
    cout << counter << " non-matching key pairs" << endl;
    cin.ignore();
    for(int i=28000; i<=29000; i++){
        for(int j=55000; j<=55500; j++){
            if(!publicKey(Wa, Wb, 56744, 47377, 1, 64853, i, j))
                counter++;
            cout << counter << " " << i << j << endl;
        }
    }
    cout << counter << " non-matching key pairs" << endl << endl;

    cout << "Testing done" << endl;

    return 0;
}