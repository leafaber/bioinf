
#include "LDCF.h"
#include <fstream>
/*********************************************************************************
 * Argument parsing and LDCF initialization    | Authors: Lea Faber, Luka Mucko  *
 *********************************************************************************/                     

/* Initialization ot the LDCF:

Requires the # of buckets, # of entries and the size of the fingerprint 
By canging the fingerprint size, the change in false positive results can be easily seen:
                                          - Lea
*/


int main(int argc, char* argv[]) {
  int buckets, entries, fp_size, k;
  string genome;

  try{
    if (argc != 6) {
      throw invalid_argument("The program requires 5 additional args.");
    }
    buckets = stoi(argv[1]);
    entries = stoi(argv[2]);
    fp_size = stoi(argv[3]);
    k       = stoi(argv[4]);
    genome  = argv[5];
  } catch(exception& e){
    cerr << "Error: " << e.what() << endl;
  }

  // Example: LCDF lcdf = LCDF(3, 1, 10);
  LDCF ldcf = LDCF(buckets, entries, fp_size);
  

  ofstream outfile;
  outfile.open("results.txt", ios_base::app);
  int num_kmers = count_k_mers(&ldcf, genome, k);
  outfile << "Unique "<< k << "-mers: " << num_kmers << endl;
  outfile << "Size of LDCF in MB: " << ldcf.sizeInMB() << " MB" << endl;

  outfile.close();
  /* Just testing some functions out
  string input = "String to hash";
  ldcf.printLDCF();

  cout << "CF count: " << ldcf.getLDCFCount() << endl;
  cout << "CF false pos. rate: " << ldcf.getFalsePosRate() << endl;
  ldcf.insert(input);
  ldcf.printLDCF();
  ldcf.insert(input);
  ldcf.printLDCF();
  ldcf.insert("String to hash2");
  ldcf.printLDCF();
  ldcf.insert("String to hash3");

  cout << "CF count: " << ldcf.getLDCFCount() << endl;
  cout << "CF false pos. rate: " << ldcf.getFalsePosRate() << endl;
  ldcf.printLDCF();
  ldcf.insert("String to hash4");
  ldcf.printLDCF();

  cout << "CF count: " << ldcf.getLDCFCount() << endl;
  cout << "Find existing: " << ldcf.search(input) << endl;
  cout << "Find nonexisting: " << ldcf.search("Ne postoji") << endl;
  cout << "Remove existing: " << ldcf.remove(input) << endl;
  ldcf.printLDCF();

  cout << "CF count: " << ldcf.getLDCFCount() << endl;
  cout << "CF false pos. rate: " << ldcf.getFalsePosRate() << endl;
  */
  return 0;
}

/******************************************************************************************************
 * Compiling the program:                                                                             *
 * g++ -o LDCF.out main.cpp cuckooFilter.cpp hashingFuncs.cpp LDCF.cpp countKmers.cpp -lssl -lcrypto  *
 *                                                                                                    *
 * Running the program requires 5 additional arguments:                                               *
 * ./LDCF.out [(int) buckets] [(int) entries] [(int) fp size] [(int) k-mere size] [(string) .fna src] *
 *                                                                                                    *       
 * E.g. ./LDCF.out 10000 100 256 200 ecoli_genome.txt                                                 *
 *                                                                        - Lea                       *
 ******************************************************************************************************/
