#include <stdio.h>
#include <iostream>
#include "cuckooFilter.h"

/*
- svaka funkcija i klasa moraju biti komentirani
- treba naznačiti tko je napisao koji dio koda
- imena varijabli i komentari su na engleskom
*/

int main() {
  // Just testing some functions out
  string input = "String to hash";
  /*
  cout << sha1(input) << endl;
  cout << sha256(input) << endl;
  cout << md5(input) << endl;
  */
 // first prefix is "", because the root doesnt have a prefix
  CuckooFilter cf = CuckooFilter(3, 1, 0, 10, "");
  cf.printTable();
  cf.insert(input);
  cf.printTable();
  cf.insert(input);
  cf.printTable();
  cf.insert(input);
  cf.printTable();
  cf.insert(input);
  cf.printTable();
  cf.insert(input);
  // cout << cf.getFingerprint(input, md5) << endl;
  return 0;
}

/******************************************************************************
 * Compiling and running the program (for now):                               *
 * g++ -o LDCF.out main.cpp cuckooFilter.cpp hashingFuncs.cpp -lssl -lcrypto  *
 * ./LDCF.out                                                                 *
 *                                   - Lea                                    *
 ******************************************************************************/
