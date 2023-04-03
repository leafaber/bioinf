#ifndef LCDF_H
#define LCDF_H

#include "cuckooFilter.h"
class LCDF {
    private:
        // initial cuckoo filter 
        CuckooFilter *cf;
    public:
        LCDF(int n_buckets, int n_entries, int level, int fp_size);
        ~LCDF();

        bool insert(string input);
        bool search(string input);  
        bool remove(string input);
        void printLCDF();
        // prints all cuckoo filters from this one until the end (leafs)
        void printCFs(CuckooFilter *ckf);
};

#endif
