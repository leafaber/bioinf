/***************************************************************************************************
 *  A file contains Cuckoo Filter implementation used to create LDCF multi-level tree structure    *
 ***************************************************************************************************/

#include "cuckooFilter.h"

/*********************************************************************
 * Implement CF table creation (constructor)    | Author: Lea Faber  *
 * Create cuckooFilter.h file                   | Author: Lea Faber  *
 * Add printTable() functionality               | Author: Lea Faber  *
 * Add nucleoidConverter()                      | Author: Lea Faber  *
 * Implement getKmereIndex()                    | Author: Lea Faber  *
 *********************************************************************/                     

CuckooFilter::CuckooFilter(int n_buckets, int n_entires, int fingerprint_size){
    this->m = n_buckets;
    this->b = n_entires;
    this->fp_size = fingerprint_size;

    // creating the CF table (2D array)
    // memory allocation
    buckets = new char*[m];
    for (int i = 0; i < m; i++) {
        buckets[i] = new char[b * fp_size];
    }
}

// insering k-meres to CF
bool CuckooFilter::insertElem(string fingerprint){
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


tuple<uint64_t, uint64_t> CuckooFilter::getKmereIndex(string kmere, int m){
    // takes in a k-mere string (ex. "ACCTGAC")
    // hashes it and calcs a bucket index for both hashes
    string h1 = sha256(kmere);
    string h2 = md5(kmere);
    uint64_t idx1 = std::stoull(h1.substr(0, 16), nullptr, 16);  // extract first 8 bytes (64 bits)
    uint64_t idx2 = std::stoull(h2.substr(0, 16), nullptr, 16);  // extract first 8 bytes (64 bits)
    return { idx1 % m , idx2 % m };
}

// maybe wont even use this functionality
// changes for example AG to 0011
string nucleoidConverter(char* nucleoid){
    switch(*nucleoid) {
    case 'A':
        return "00";
        break;
    case 'T':
        return "01";
        break;
    case 'C':
        return "10";
        break;
    case 'G':
        return "11";
        break;
    default:
        throw std::invalid_argument("Nucleoid can only have a value of A, T, C or G");
    }
}

/*
Some notes:
hashCF method 
k = k-mere size
h1 = first hash func
h2 = second hash func

A cuckoo filter is a compact variant of a cuckoo hash
table that stores only fingerprints — a bit string derived
from the item using a hash function
                        - Lea
*/