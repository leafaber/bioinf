#ifndef LDCF_H
#define LDCF_H

#include "cuckooFilter.h"
#include <cmath>

class LDCF {
    private:
        // initial cuckoo filter 
        int m;              // # of buckets
        int b;              // # of entries in a bucket
        int fp_size;        // size of a original fingerprint
        CuckooFilter *cf;
    public:
        LDCF(int n_buckets, int n_entries, int fp_size);
        ~LDCF();

        bool insert(string input);
        bool search(string input);  
        bool remove(string input);
        int getCFCount(CuckooFilter *ckf);
        int getLDCFCount();
        float getFalsePosRate();
        void printLDCF();
        // prints all cuckoo filters from this one until the end (leafs)
        void printCFs(CuckooFilter *ckf);
};

int count_k_mers(LDCF* ldcf, string genome, int k);

#endif
