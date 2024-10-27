#include "gmp.h"
#include "gmpxx.h"
#include <boost/multiprecision/gmp.hpp>

#ifndef PUBLICKEYSYSTEM_H
#define PUBLICKEYSYSTEM_H

/*
 * Function: getKey
 * Input:
 * Return:
 * Description: To be called by each correspondant individually. Will require collaberation
 *              between correspondants in order to calculate their shared keys.
*/
void getKey();

/*
 * Function: publicKey
 * Input:
 *          Wa and Wb representing {Lm, Km, Lm+1, Km+1} for correspondant a and correspondant b
 *          P1, P2, Q, and p values as described in ______________
 *          max1 and max2 are the secret values of correspondants a and b
 * Return:  true if the secret keys match, false otherwise
 * Description: Run the entire algorithmn rather than prompting two separate correspondants
 * Assumptions: P1, P2, Q, p, max1, and max2 have already been initialized and validated. This
 *              can be done by calling getInitialValues or by initializing and calling validInput
*/
bool publicKey(boost::multiprecision::mpz_int Wa[4], boost::multiprecision::mpz_int Wb[4], boost::multiprecision::mpz_int P1, boost::multiprecision::mpz_int P2, boost::multiprecision::mpz_int Q, boost::multiprecision::mpz_int p, boost::multiprecision::mpz_int max1, boost::multiprecision::mpz_int max2);

/*
 * Function: getInitialValues
 * Input:
 * Return:  true if all input is valid, false otherwise
 *          P1, P2, and p as described in _____________
 *          max1 and max2 are the secret values of correspondants a and b
 * Description: Prompt and validate all initial input values for two correspondants. Use this
 *              function before publicKey
*/
bool getInitialValues(boost::multiprecision::mpz_int &P1, boost::multiprecision::mpz_int &P2, boost::multiprecision::mpz_int &max1, boost::multiprecision::mpz_int &max2, boost::multiprecision::mpz_int &p);

/*
 * Function: individualInput
 * Input:
 * Return:
 *          P1, P2, and p as described in _____________
 *          a is the secret value for one correspondant
 * Description: To be called by individual correspondants. 
 *              Gives the option to randomly generate P1, P2 and p. Otherwise prompts for
 *              P1, P2 and p. Prompts for a and validates all input. Will continue to 
 *              prompt until valid input is entered.
*/
void individualInput(boost::multiprecision::mpz_int &P1, boost::multiprecision::mpz_int &P2, boost::multiprecision::mpz_int &p, boost::multiprecision::mpz_int &a);

/*
 * Function: doubleAndAddOne
 * Input:   
 *          max is the secret value of one correspondant
 *          P1, P2, p, Q, and delta as described in __________
 * Return:  wPrev representing {Lm, Km, Lm+1, Km+1}
 * Description: performs case 1, as described in __________, pgs. 2-3) to obtain {Lmax, Kmax, Lmax+1, Kmax+1}
 * Assumptions: P1, P2, Q, p, and max have already been initialized and validated. 
 *              delta has been calculated as described in ______. 
*/
void doubleAndAddOne(boost::multiprecision::mpz_int wPrev[4], boost::multiprecision::mpz_int max, boost::multiprecision::mpz_int P1, boost::multiprecision::mpz_int P2, boost::multiprecision::mpz_int Q, boost::multiprecision::mpz_int p, boost::multiprecision::mpz_int delta);

/*
 * Function: doubleAndAddTwo
 * Input:   
 *          max is the secret value of one correspondant
 *          P1, P2, p, Q, and delta as described in __________
 * Return:  wPrev representing {Lm, Jm, Lm+1, Jm+1}
 * Description: performs case 2, as described in __________, p. 3) to obtain {Lmax, Jmax, Jmax+1, Jmax+1}
 * Assumptions: P1, P2, Q, p, and max have already been initialized and validated. 
 *              wPrev[0] = Lmax of the other correspondant
 *              delta has been calculated as described in ______. 
 *              Q is equal to one
*/
void doubleAndAddTwo(boost::multiprecision::mpz_int wPrev[4], boost::multiprecision::mpz_int max, boost::multiprecision::mpz_int P1, boost::multiprecision::mpz_int P2, boost::multiprecision::mpz_int Q, boost::multiprecision::mpz_int p, boost::multiprecision::mpz_int delta);

/*
 * Function: validInput
 * Input:        
 *          P1, P2, p, and Q as described in __________
 *          a and b are the secret values of the two correspondants. (When only one value is
 *          known any non-zero integer can be used in the other's place)
 * Return:  true if all input values are valid as described in ________, false otherwise
 * Description: calculates D, E and delta values as described in ______. For input to be valid,
 *              D, P1, a, and b must be non-zero, Q must be 1, P1 must be even, p must not be divisible by P1
 *              or D, gcd(P1, P2) = 1, and the legendre symbols (delta | p) and (E | p) must be -1    
 */
bool validInput(boost::multiprecision::mpz_int P1, boost::multiprecision::mpz_int P2, boost::multiprecision::mpz_int p, boost::multiprecision::mpz_int Q, boost::multiprecision::mpz_int a, boost::multiprecision::mpz_int b);

/*
 * Function: positiveMod
 * Input:
 * Return:
 * Description: return the positive value of n mod p
*/
boost::multiprecision::mpz_int positiveMod (boost::multiprecision::mpz_int n, boost::multiprecision::mpz_int p);

/*
 * Function: getRandInput
 * Input:
 *          bits indicates the size of values to be generated
 *          state object for random number generation
 * Return:  P1, P2 and p as described in _______
 * Description: generate a random even number for P1 and random primes for P2 and p. Repeatedly
 *              calls validInput and iterates P1 until a valid combination is reached. 
 * Assumptions: state has been initialized and seeded
 *              P1, P2 and p have been initalized
*/
void getRandInput(mpz_t P1, mpz_t P2, mpz_t p, const int bits, gmp_randstate_t state);

#endif  