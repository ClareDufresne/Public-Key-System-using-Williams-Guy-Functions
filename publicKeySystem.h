#include "gmp.h"
#include "gmpxx.h"
#include <boost/multiprecision/gmp.hpp>

#ifndef PUBLICKEYSYSTEM_H
#define PUBLICKEYSYSTEM_H

bool publicKey(boost::multiprecision::mpz_int Wa[4], boost::multiprecision::mpz_int Wb[4], boost::multiprecision::mpz_int P1, boost::multiprecision::mpz_int P2, boost::multiprecision::mpz_int Q, boost::multiprecision::mpz_int p, boost::multiprecision::mpz_int max1, boost::multiprecision::mpz_int max2);
bool getInitialValues(boost::multiprecision::mpz_int &P1, boost::multiprecision::mpz_int &P2, boost::multiprecision::mpz_int &max1, boost::multiprecision::mpz_int &max2, boost::multiprecision::mpz_int &p);
bool setInitialValues(boost::multiprecision::mpz_int &P1, boost::multiprecision::mpz_int &P2, boost::multiprecision::mpz_int &Q, boost::multiprecision::mpz_int &max1, boost::multiprecision::mpz_int &max2, boost::multiprecision::mpz_int &p);
void doubleAndAddOne(boost::multiprecision::mpz_int wPrev[4], boost::multiprecision::mpz_int max, boost::multiprecision::mpz_int P1, boost::multiprecision::mpz_int P2, boost::multiprecision::mpz_int Q, boost::multiprecision::mpz_int p, boost::multiprecision::mpz_int delta);
void doubleAndAddTwo(boost::multiprecision::mpz_int wPrev[4], boost::multiprecision::mpz_int max, boost::multiprecision::mpz_int P1, boost::multiprecision::mpz_int P2, boost::multiprecision::mpz_int Q, boost::multiprecision::mpz_int p, boost::multiprecision::mpz_int delta);
bool validInput(boost::multiprecision::mpz_int P1, boost::multiprecision::mpz_int P2, boost::multiprecision::mpz_int p, boost::multiprecision::mpz_int Q, boost::multiprecision::mpz_int a, boost::multiprecision::mpz_int b);
boost::multiprecision::mpz_int positiveMod (boost::multiprecision::mpz_int n, boost::multiprecision::mpz_int p);

#endif  