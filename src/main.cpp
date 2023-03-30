#include <stdio.h>
#include <iostream>

#include "sha256.h"
/*
- svaka funkcija i klasa moraju biti komentirani
- treba naznačiti tko je napisao koji dio koda
- imena varijabli i komentari su na engleskom
*/

int main() {
  string input = "String to hash";
  string hash = sha256(input);
  cout << hash << endl;

  return 0;
}

/**********************************************************************
 * Compiling and running the program (for now):                       *
 * g++ -o LDCF main.cpp sha256.cpp -lssl -lcrypto | ./LDCF            *
 *                                   - Lea                            *
 **********************************************************************/