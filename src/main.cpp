
#include "LDCF.h"

/********************************************************************
 * Argument parsing and LDCF initialization    | Author: Lea Faber  *
 ********************************************************************/                     

/* Initialization ot the LDCF:

Requires the # of buckets, # of entries and the size of the fingerprint 
By canging the fingerprint size, the change in false positive results can be easily seen:
                                          - Lea
*/

int main(int argc, char* argv[]) {
  // default lcdf
  int buckets, entries, fp_size;
  try{
    if (argc != 4) {
      throw invalid_argument("The program requires 3 additional integer args.");
    }
    buckets = stoi(argv[1]);
    entries = stoi(argv[2]);
    fp_size = stoi(argv[3]);
  } catch(exception& e){
    cerr << "Error: " << e.what() << endl;
  }

  // Example: LCDF lcdf = LCDF(3, 1, 10);
  LDCF lcdf = LDCF(buckets, entries, fp_size);
  
  // Just testing some functions out
  string input = "String to hash";
  lcdf.printLDCF();
  lcdf.insert(input);
  lcdf.printLDCF();
  lcdf.insert(input);
  lcdf.printLDCF();
  lcdf.insert(input);
  lcdf.printLDCF();
  lcdf.insert(input);
  lcdf.printLDCF();
  lcdf.insert(input);
  
  cout << "Find existing: " << lcdf.search(input) << endl;
  cout << "Find nonexisting: " << lcdf.search("Ne postoji") << endl;
  cout << "Remove existing: " << lcdf.remove(input) << endl;
  lcdf.printLDCF();
  return 0;
}

/******************************************************************************************
 * Compiling the program:                                                                 *
 * g++ -o LDCF.out main.cpp cuckooFilter.cpp hashingFuncs.cpp LDCF.cpp -lssl -lcrypto     *
 *                                                                                        *
 * Running the program requires 3 additional arguments:                                   *
 * ./LDCF.out [(int) buckets] [(int) entries] [(int) fp size]                             *
 *                                                                                        *       
 * E.g. ./LDCF.out 3 1 10                                                                 *
 *                                                                        - Lea           *
 ******************************************************************************************/
