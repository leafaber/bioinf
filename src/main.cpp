#include <stdio.h>
#include <iostream>

#include "hashingFuncs.h"
/*
- svaka funkcija i klasa moraju biti komentirani
- treba naznačiti tko je napisao koji dio koda
- imena varijabli i komentari su na engleskom
*/

int main() {
  string input = "String to hash";
  cout << sha1(input) << endl;
  cout << sha256(input) << endl;
  cout << md5(input) << endl;
  return 0;
}

/**************************************************************************
 * Compiling and running the program (for now):                           *
 * g++ -o LDCF.out main.cpp hashingFuncs.cpp -lssl -lcrypto               *
 * ./LDCF.out                                                             *
 *                                   - Lea                                *
 **************************************************************************/