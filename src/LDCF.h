#ifndef LDCF_H
#define LDCF_H

#include "cuckooFilter.h"
class LDCF {
    private:
        // initial cuckoo filter 
        CuckooFilter *cf;
    public:
        LDCF(int n_buckets, int n_entries, int fp_size);
        ~LDCF();

        bool insert(string input);
        bool search(string input);  
        bool remove(string input);
        void printLDCF();
        // prints all cuckoo filters from this one until the end (leafs)
        void printCFs(CuckooFilter *ckf);
};

#endif
