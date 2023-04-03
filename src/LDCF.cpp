/***************************************************************************************************
 *  A file containing LDCF implementation                                                          *
 ***************************************************************************************************/

#include "LDCF.h"

// Author: Lea Faber

LDCF::LDCF(int n_buckets, int n_entries, int fp_size) {
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