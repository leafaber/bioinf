#ifndef CUCKOO_FILTER_H
#define CUCKOO_FILTER_H

#include "hashingFuncs.h"
#include <tuple>
#include <bitset>

class CuckooFilter {
private:
    int m;              // # of buckets
    int b;              // # of entries in a bucket
    int level;          // level of the CF, starts from 0
    int fp_size;        // size of a original fingerprint
    int ent_size;       // size of an entry (fp_size - level)
    string prefix;      // string of size level
    string** buckets;     // ptr to CF table (2D array)

public:
    // In LDCF each CF contains 2 ptrs to 2 other CFs (appending for 0 or 1)
    CuckooFilter *cf0;
    CuckooFilter *cf1;

    CuckooFilter(int n_buckets, int n_entries, int level, int fp_size, string prefix);
    ~CuckooFilter();

    void printTable();
    bool insert(string input);
    bool search(string input); 
    bool remove(string input);  
    string getFingerprint(string kmere, int fp_size);
    // get bucket index 
    tuple<uint64_t, uint64_t> getFpIndex(string fingerprint);
};

string getFingerprint(string kmere, string (*hashFunc)(string));

#endif
