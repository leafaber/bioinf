/***************************************************************************************************
 *  A file containing LDCF implementation                                                          *
 ***************************************************************************************************/

#include "LDCF.h"

// Author: Lea Faber

LDCF::LDCF(int n_buckets, int n_entries, int fp_size) {
    this->m = n_buckets;
    this->b = n_entries;
    this->fp_size = fp_size;
    // Initial CF starts form the 0 (root)
    // first prefix is "" because the root doesn't have a prefix
    cf = new CuckooFilter(n_buckets, n_entries, 0, fp_size, "");
}

LDCF::~LDCF() {
    delete cf;
}

bool LDCF::insert(string input){
    return cf->insert(input);
}

bool LDCF::search(string input){
    return cf->search(input);
}

bool LDCF::remove(string input){
    return cf->remove(input);
}

void LDCF::printLDCF(){
    // prints LCDF from the root
    printCFs(cf);
}

void LDCF::printCFs(CuckooFilter *ckf){
    ckf->printTable();
    if (ckf->cf0 != nullptr && ckf->cf1 != nullptr){
        // propagates the print operation to other cfs if they exist
        printCFs(ckf->cf0);
        printCFs(ckf->cf1);
    }
}

int LDCF::getLDCFCount(){
    // counts from the root
    return getCFCount(cf);
}
// counts how many CFs are in the LDCF
int LDCF::getCFCount(CuckooFilter *ckf){
    int cnt = 1;
    if (ckf->cf0 != nullptr && ckf->cf1 != nullptr){
        cnt += getCFCount(ckf->cf0);
        cnt += getCFCount(ckf->cf1);
    }
    return cnt;
}
/*
False positive rate of LDCF is approx. (2*b*s)/(2^f)
Note: this is NOT compact LDCF 
s = # of CFs used in LDCF
b = # of entries in a bucket
f = fingerprint size

By this function you can clearly see that by using the bigger fingerprint 
the false positive rate is smaller
                                        - Lea
*/
float LDCF::getFalsePosRate(){
    int s = getLDCFCount();
    return float((2*b*s)/pow(2, fp_size));
}