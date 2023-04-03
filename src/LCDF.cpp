#include "LCDF.h"

// Author: Lea Faber

LCDF::LCDF(int n_buckets, int n_entries, int level, int fp_size) {
    // first prefix is "", because the root doesn't have a prefix
    cf = new CuckooFilter(n_buckets, n_entries, level, fp_size, "");
}

LCDF::~LCDF() {
    delete cf;
}

bool LCDF::insert(string input){
    return cf->insert(input);
}

bool LCDF::search(string input){
    return cf->search(input);
}

bool LCDF::remove(string input){
    return cf->remove(input);
}

void LCDF::printLCDF(){
    // prints LCDF from the root
    printCFs(cf);
}

void LCDF::printCFs(CuckooFilter *ckf){
    ckf->printTable();
    if (ckf->cf0 != nullptr && ckf->cf1 != nullptr){
        // propagates the print operation to other cfs if they exist
        printCFs(ckf->cf0);
        printCFs(ckf->cf1);
    }
}