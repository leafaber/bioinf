/***************************************************************************************************
 *  A file contains Cuckoo Filter implementation used to create LDCF multi-level tree structure    *
 ***************************************************************************************************/

#include "cuckooFilter.h"

/*********************************************************************
 * Implement CF table creation (constructor)    | Author: Lea Faber  *
 * Create cuckooFilter.h file                   | Author: Lea Faber  *
 * Add printTable() functionality               | Author: Lea Faber  *
 * Add getFingerprint()                         | Author: Lea Faber  *
 * Implement getFpIndex()                       | Author: Lea Faber  *
 *********************************************************************/                     

// extract somehow the fp_length (= kmere length*2)
CuckooFilter::CuckooFilter(int n_buckets, int n_entires, int level, int fp_size){
    this->m = n_buckets;
    this->b = n_entires;
    this->fp_size = fp_size;    // size of a fingerprint that can be stored in a bucket entry
    this->level = level;

    // creating the CF table (2D array)
    // memory allocation
    buckets = new char*[m];
    for (int i = 0; i < m; i++) {
        buckets[i] = new char[b * (fp_size - level)];
    }
}

// insering k-meres to CF
bool CuckooFilter::insert(string fingerprint){
    return true;
}

// used for testing/displaying the contents of a CF
void CuckooFilter::printTable() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < b; j++) {
            std::cout << "Bucket " << i << ", Entry " << j << ": ";
            for (int k = 0; k < fp_size; k++) {
                std::cout << (int)buckets[i][j * fp_size + k] << " ";
            }
            std::cout << std::endl;
        }
    }
}

CuckooFilter::~CuckooFilter() {
    for (int i = 0; i < m; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
}


tuple<uint64_t, uint64_t> CuckooFilter::getFpIndex(string fingerprint, int m){
    /* 
        takes in a k-mere string (ex. "ACCTGAC")
        hashes it and calcs a bucket index for both hashes
        m is the number of buckets in the CF
    */
    string h1 = sha256(fingerprint);
    string h2 = md5(fingerprint);
    uint64_t idx1 = std::stoull(h1.substr(0, 16), nullptr, 16);
    uint64_t idx2 = std::stoull(h2.substr(0, 16), nullptr, 16); 
    return { idx1 % m , idx2 % m };
}

/* getFingerprint method:

 Hashes a nucleotide sequence (k-mere) and convertes it to a binary string, aka. fingerprint
 It is possible to change the hash function for the covertion to see how 
 the program changes results depending on the fp size
*/
string getFingerprint(string kmere, string (*hashFunc)(string)){
    // for each nucleotide in a kmere convert it to a binary representation and return the result
    string hash = hashFunc(kmere);
    string fingerprint = "";
    for (char c : hash) {
        fingerprint += bitset<8>(c).to_string();
    }
    return fingerprint;
}
