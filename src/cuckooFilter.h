#ifndef CUCKOO_FILTER_H
#define CUCKOO_FILTER_H

#include "hashingFuncs.h"

class CuckooFilter {
private:
    int m;          // # of buckets
    int b;          // # of entries in a bucket
    int fp_size;    // size of a fingerprint
    char** buckets; // ptr to CF table (2D array)

    // In LDCF each CF contains 2 ptrs to 2 other CFs (appending for 0 or 1)
    CuckooFilter *cf0;
    CuckooFilter *cf1;

public:
    CuckooFilter(int n_buckets, int n_entries, int fingerprint_size);
    ~CuckooFilter();

    void printTable();
    bool insertElem(char* fp);
    bool searchElem(char* fp);  // To impl
    bool removeElem(char* fp);  // to impl.
};

#endif
