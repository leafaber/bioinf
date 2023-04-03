
#include "LCDF.h"

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
 
  LCDF lcdf = LCDF(3, 1, 0, 10);
  lcdf.printLCDF();
  lcdf.insert(input);
  lcdf.printLCDF();
  lcdf.insert(input);
  lcdf.printLCDF();
  lcdf.insert(input);
  lcdf.printLCDF();
  lcdf.insert(input);
  lcdf.printLCDF();
  lcdf.insert(input);
  
  cout << "Find existing: " << lcdf.search(input) << endl;
  cout << "Find nonexisting: " << lcdf.search("Ne postoji") << endl;
  cout << "Remove existing: " << lcdf.remove(input) << endl;
  lcdf.printLCDF();
  // cout << cf.getFingerprint(input, md5) << endl;
  return 0;
}

/***************************************************************************************
 * Compiling and running the program (for now):                                        *
 * g++ -o LDCF.out main.cpp cuckooFilter.cpp hashingFuncs.cpp LCDF.cpp -lssl -lcrypto  *
 * ./LDCF.out                                                                          *
 *                                   - Lea                                             *
 ***************************************************************************************/
