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
    string prefix;      
    char** buckets;     // ptr to CF table (2D array)

    // In LDCF each CF contains 2 ptrs to 2 other CFs (appending for 0 or 1)
    CuckooFilter *cf0;
    CuckooFilter *cf1;

public:
    CuckooFilter(int n_buckets, int n_entries, int level, int fp_size);
    ~CuckooFilter();

    void printTable();
    bool insert(string fp);
    bool search(string fp);  // To impl
    bool remove(string fp);  // to impl.
    tuple<uint64_t, uint64_t> getFpIndex(string fingerprint, int m);
};

string getFingerprint(string kmere, string (*hashFunc)(string));

#endif
