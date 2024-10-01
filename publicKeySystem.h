#ifndef PUBLICKEYSYSTEM_H
#define PUBLICKEYSYSTEM_H

bool publicKey(long long Wa[4], long long Wb[4], long long P1, long long P2, long long Q, long long p, long long max1, long long max2);
bool getInitialValues(long long &P1, long long &P2, long long &max1, long long &max2, long long &p);
bool setInitialValues(long long &P1, long long &P2, long long &Q, long long &max1, long long &max2, long long &p);
void doubleAndAddOne(long long wPrev[4], long long max, long long P1, long long P2, long long Q, long long p, long long delta);
void doubleAndAddTwo(long long wPrev[4], long long max, long long P1, long long P2, long long Q, long long p, long long delta);
bool validInput(long long P1, long long P2, long long p, long long Q, long long a, long long b);
long long positiveMod (long long n, long long p);
 
#endif  