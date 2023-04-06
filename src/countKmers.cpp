/*************************************************************************************************************************
 *  This code uses LDCF object to count k-mers in a given genome by counting the number of unique additions into ldcf    *
 *************************************************************************************************************************/

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "LDCF.h"
using namespace std;

/*********************************************************************************************************************************
*   Read genome by k-mers and add them to ldcf if it's not already in it. Returns the number of insertions i.e. unique k-mers    *
*   author: Luka Mucko                                                                                                           *
/*********************************************************************************************************************************/
int count_k_mers(LDCF* ldcf, string genome, int k){
    ifstream file(genome);
    if (!file.is_open()){
        cout << "Error opening the file!" << endl;
        exit(1);
    }
    string delim;
    getline(file, delim);

    long unique_kmers = 0;
    char kmer[k+1];
    kmer[k] = '\0';
    auto start = chrono::high_resolution_clock::now();

    char c;
    int i;
    while(file){
        streampos pos = file.tellg();
        i=0;
        while(file.get(c) && i<k){
            if(c!='\n' && c!='>'){
                kmer[i]=c;
                i++;
            }else if (c=='>')
            {
                getline(file,delim);
                pos = file.tellg();
                i=0;
            }            
        }
        if(i<k){
            break;
        }
        if(!ldcf->search(string(kmer))){
            unique_kmers+=ldcf->insert(string(kmer));
        }
        file.seekg(pos);
        file.seekg(1, ios::cur);
    }

    auto end = chrono::high_resolution_clock::now();
    auto time_ms = chrono::duration_cast<chrono::milliseconds>(end-start);
    cout << "Done reading in: " << time_ms.count() << "ms\n";
    return unique_kmers;
}



int main(int argc, char* argv[]){
    int buckets, entries, fp_size, k;
    string genome;
    try{
        if (argc != 6) {
            throw invalid_argument("The program requires 5 additional args.");
        }
        buckets = stoi(argv[1]);
        entries = stoi(argv[2]);
        fp_size = stoi(argv[3]);
        k       = stoi(argv[4]);
        genome  = argv[5];
    } catch(exception& e){
        cerr << "Error: " << e.what() << endl;
    }

    LDCF ldcf = LDCF(buckets, entries, fp_size);
    
    int num_kmers = count_k_mers(&ldcf, genome, k);
    cout << "Unique "<< k << "-mers: " << num_kmers << endl;
}