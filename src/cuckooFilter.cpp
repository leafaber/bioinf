/***************************************************************************************************
 *  A file contains Cuckoo Filter implementation used to create LDCF multi-level tree structure    *
 ***************************************************************************************************/

#include "cuckooFilter.h"

// how many victim extractions before a new CF is appended
#define MAX_RELOCATION 5

/*****************************************************************************
 * Implement CF table creation (constructor)            | Author: Lea Faber  *
 * Create cuckooFilter.h file                           | Author: Lea Faber  *
 * Add printTable() functionality                       | Author: Lea Faber  *
 * Add getFingerprint()                                 | Author: Lea Faber  *
 * Implement getFpIndex()                               | Author: Lea Faber  *
 * Implement insertion of an element - insert()         | Author: Lea Faber  *  
 * Implement Cuckoo search()  (lookup)                  | Author: Lea Faber  *   
 * Implement element removal | remove()                 | Author: Lea Faber  *                   
 *****************************************************************************/                     

CuckooFilter::CuckooFilter(int n_buckets, int n_entries, int level, int fp_size, string prefix){
    this->m = n_buckets;
    this->b = n_entries;
    this->fp_size = fp_size;    // size of a fingerprint that can be stored in a bucket entry
    this->level = level;
    this->ent_size = fp_size - level;      
    this->prefix = prefix;

    // creating the CF table (2D array)
    // memory allocation
    buckets = new string*[m];
    for (int i = 0; i < m; i++) {
        buckets[i] = new string[b];
        for (int j = 0; j < b; j++) {
            buckets[i][j] = string(ent_size, 'N');
        }
    }
}

// insering k-meres to CF
bool CuckooFilter::insert(string input){
    string fp;
    // if the input is already a fingerprint
    if (input[0] == '0' || input[0] == '1'){
        fp = input;
    } else {
        // input is a k-mere (raw data) -> converting to fp
        fp = getFingerprint(input, fp_size);
    }
    
    // TO DO: searches the cor-responding leaf CF from the root according to its ﬁngerprint
    
    // if cf0 and cf1 are initiated, that means this CF is already full
    if (cf0 != nullptr && cf1 != nullptr){
        // char that is the prefix extension of the cf1 or cf0 cf
        if (fp[level] == '0'){
            cout << "cf0 not nullptr, insert to cf0" << endl;
            cf0->insert(fp);
            //cf0->printTable();
        } else {
            cout << "cf1 not nullptr, insert to cf1" << endl;
            cf1->insert(fp);
            //cf1->printTable();
        }
        return true;
    }
   
   for (int reloc = 0; reloc < MAX_RELOCATION; reloc++){
        // calculating the bucket indexes of the fp
        auto [ind1, ind2] = getFpIndex(fp);
        // checking if first bucket index is free
        for(int i = 0; i < b; i++){
            // an empty entry will be represented by "N..." string
            if(buckets[ind1][i].substr(0, 1) == "N"){
                // inserting just the postfix of the fp
                buckets[ind1][i] = fp.substr(fp_size - ent_size, ent_size);
                return true;
            }
        }
        // checking if second bucket index is free
        for(int i = 0; i < b; i++){
            if(buckets[ind2][i].substr(0, 1) == "N"){
                buckets[ind2][i] = fp.substr(fp_size - ent_size, ent_size);
                return true;
            }
        }
        // Eviction of a victim
        srand(time(NULL));
        // evict a random entry if no empty entry
        int eInd = rand() % b;    // random entry index
        string victim = buckets[ind1][eInd];
        // putting the orign fp into the entry
        buckets[ind1][eInd] = fp.substr(fp_size - ent_size, ent_size);
        // recover it to the original fp length of the victim
        fp = prefix + victim;
    }

    // append the LDCF, if no empty entry was found for the final victim
    // the while loops are here just in case
    while (cf0 == nullptr) {
        cf0 = new CuckooFilter(m, b, level + 1, fp_size, prefix + "0");
    }
    while (cf1 == nullptr) {
        cf1 = new CuckooFilter(m, b, level + 1, fp_size, prefix + "1");
    }

    if (fp[level] == '0'){
        //cf0->printTable();
        cout << "Create and insert to cf0" << endl;
        cf0->insert(fp);
        //cf0->printTable();
    } else if(fp[level] == '1'){
        //cf1->printTable();
        cout << "Create and insert to cf1" << endl;
        cf1->insert(fp);
        //cf1->printTable();
    }
    return true;
}


bool CuckooFilter::search(string input){
    string fp;
    // if the input is already a fingerprint
    if (input[0] == '0' || input[0] == '1'){
        fp = input;
    } else {
        // input is a k-mere (raw data) -> converting to fp
        fp = getFingerprint(input, fp_size);
    }
    // part of the pf stored in the entry
    string postfix = fp.substr(level, fp_size);
    // calculating the bucket indexes of the fp
    auto [ind1, ind2] = getFpIndex(fp);
    // checking the buckets for the wanted fp
    for(int i = 0; i < b; i++){
        // serching if the desired part of the fp is stored in any of the entries
        if(buckets[ind1][i] == postfix){
            // there is a possibility of the sequence existing in the set
            return true;
        }
        if(buckets[ind2][i] == postfix){
            // there is a possibility of the sequence existing in the set
            return true;
        }
    }

    // Propagate the search on the following CFs, if they exist
    if (cf0 != nullptr && cf1 != nullptr){
        // char that is the prefix extension of the cf1 or cf0 cf
        if (fp[level] == '0'){
            return cf0->search(fp);
        } else {
            return cf1->search(fp);
        }
    }
    // if not found
    return false;
}

bool CuckooFilter::remove(string input){
    // similar to search, just fills the entry with Ns
    string fp;
    // if the input is already a fingerprint
    if (input[0] == '0' || input[0] == '1'){
        fp = input;
    } else {
        // input is a k-mere (raw data) -> converting to fp
        fp = getFingerprint(input, fp_size);
    }
    // part of the pf stored in the entry
    string postfix = fp.substr(level, fp_size);
    // calculating the bucket indexes of the fp
    auto [ind1, ind2] = getFpIndex(fp);
    // checking the buckets for the wanted fp
    for(int i = 0; i < b; i++){
        // serching if the desired part of the fp is stored in any of the entries
        if(buckets[ind1][i] == postfix){
            // fills the entry with Ns  / deletes the value
            buckets[ind1][i] = string(ent_size, 'N');
            // returns that it removed something
            return true;
        }
        if(buckets[ind2][i] == postfix){
            // fills the entry with Ns / deletes the value
            buckets[ind2][i] = string(ent_size, 'N');
            // returns that it removed something
            return true;
        }
    }

    // Propagate the removal on the following CFs, if they exist
    if (cf0 != nullptr && cf1 != nullptr){
        // char that is the prefix extension of the cf1 or cf0 cf
        if (fp[level] == '0'){
            return cf0->remove(fp);
        } else {
            return cf1->remove(fp);
        }
    }
    // nothing removed
    return false;
}

// used for testing/displaying the contents of a CF
void CuckooFilter::printTable() {
    cout << "Table (prefix) " + prefix << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < b; j++) {
            cout << "Bucket " << i << ", Entry " << j << ": ";
            cout << buckets[i][j] << endl;
        }
    }
    cout << endl;
}

CuckooFilter::~CuckooFilter() {
    for (int i = 0; i < m; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;

    delete cf0;
    delete cf1;
}

tuple<uint64_t, uint64_t> CuckooFilter::getFpIndex(string fingerprint){
    /* 
        takes in a k-mere string (ex. "ACCTGAC")
        hashes it and calcs a bucket index for both hashes
        m is the number of buckets in the CF
    */
   // change to one hash and other is an XOR
    string h1 = sha1(fingerprint);
    string h2 = md5(fingerprint);
    uint64_t idx1 = std::stoull(h1.substr(0, 16), nullptr, 16);
    uint64_t idx2 = std::stoull(h2.substr(0, 16), nullptr, 16); 
    return { idx1 % this->m , idx2 % this->m };
}

/* getFingerprint method:

 Hashes a nucleotide sequence (k-mere) and convertes it to a binary string, aka. fingerprint
 It is possible to change the hash function for the covertion to see how 
 the program changes results depending on the fp size
*/
string CuckooFilter::getFingerprint(string kmere, int fp_size){
    // for each nucleotide in a kmere convert it to a binary representation and return the result
    string hash = sha256(kmere);
    string fingerprint = "";
    for (char c : hash) {
        fingerprint += bitset<8>(c).to_string();
    }
    return fingerprint.substr(0, fp_size);
}
