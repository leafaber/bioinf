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
int count_k_mers(LDCF* ldcf, const string genome_file, int k) {
    ifstream file(genome_file);
    if (!file.is_open()) {
        cerr << "Error opening the file: " << genome_file << endl;
        exit(1);
    }

    // Read the entire genome string into memory
    file.seekg(0, ios::end);
    size_t genome_size = file.tellg();
    char* genome = new char[genome_size + 1];
    file.seekg(0, ios::beg);
    file.read(genome, genome_size);
    genome[genome_size] = '\0';
    file.close();

    // Process k-mers
    long unique_kmers = 0;
    char kmer[k + 1];
    kmer[k] = '\0';
    auto start = chrono::high_resolution_clock::now();

    const char* p = genome;
    const char* end = genome + genome_size - k;
    while (p <= end) {
        copy(p, p + k, kmer);
        unique_kmers += ldcf->insert(string(kmer));
        ++p;
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end_time - start);
    ofstream outfile;
    outfile.open("results.txt", ios::trunc);
    outfile << "RESULTS:" <<endl;
    outfile << "Done reading in: " << elapsed_time.count() << "ms\n";
    outfile.close();
    delete[] genome;
    return unique_kmers;
}

