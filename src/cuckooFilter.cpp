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
    this->ent_size = fp_size - level;      
    
    // creating the CF table (2D array)
    // memory allocation
    buckets = new string*[m];
    for (int i = 0; i < m; i++) {
        buckets[i] = new string[b];
        for (int j = 0; j < b; j++) {
            buckets[i][j] = string(ent_size, 'N');
        }
    }
}

// insering k-meres to CF
bool CuckooFilter::insert(string kmere){
    // raw data (k-mere) to fp convertion
   string fp = getFingerprint(kmere, fp_size);
    auto [ind1, ind2] = getFpIndex(fp);
    // checking if first bucket index is free
    for(int i = 0; i < b; i++){
        // an empty entry will be represented by "N..." string
        if(buckets[ind1][i].substr(0, 1) == "N"){
            // inserting just the postfix of the fp
            buckets[ind1][i] = fp.substr(fp_size - ent_size, ent_size);
            return true;
        }
    }
    // checking if second bucket index is free
    for(int i = 0; i < b; i++){
        if(buckets[ind2][i].substr(0, 1) == "N"){
            buckets[ind2][i] = fp.substr(fp_size - ent_size, ent_size);
            return true;
        }
    }
    // TO DO: remove a victim
    return true;
}

// used for testing/displaying the contents of a CF
void CuckooFilter::printTable() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < b; j++) {
            cout << "Bucket " << i << ", Entry " << j << ": ";
            std::cout << buckets[i][j] << endl;
        }
    }
}

CuckooFilter::~CuckooFilter() {
    for (int i = 0; i < m; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
}

tuple<uint64_t, uint64_t> CuckooFilter::getFpIndex(string fingerprint){
    /* 
        takes in a k-mere string (ex. "ACCTGAC")
        hashes it and calcs a bucket index for both hashes
        m is the number of buckets in the CF
    */
   // change to one hash and other is an XOR
    string h1 = sha1(fingerprint);
    string h2 = md5(fingerprint);
    uint64_t idx1 = std::stoull(h1.substr(0, 16), nullptr, 16);
    uint64_t idx2 = std::stoull(h2.substr(0, 16), nullptr, 16); 
    return { idx1 % this->m , idx2 % this->m };
}

/* getFingerprint method:

 Hashes a nucleotide sequence (k-mere) and convertes it to a binary string, aka. fingerprint
 It is possible to change the hash function for the covertion to see how 
 the program changes results depending on the fp size
*/
string CuckooFilter::getFingerprint(string kmere, int fp_size){
    // for each nucleotide in a kmere convert it to a binary representation and return the result
    string hash = sha256(kmere);
    string fingerprint = "";
    for (char c : hash) {
        fingerprint += bitset<8>(c).to_string();
    }
    return fingerprint.substr(0, fp_size);
}
