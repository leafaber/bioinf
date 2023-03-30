/**********************************************************************
 *  A file that contains hashing implementation for genome k-meres    *
 **********************************************************************/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include "sha256.h"

/******************************************************************
 * Add sha-256 hashing using OpenSSL library | Author: Lea Faber  *
 ******************************************************************/                     

string sha256(const string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_sha256();

    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input.c_str(), input.size());
    EVP_DigestFinal_ex(mdctx, hash, NULL);
    EVP_MD_CTX_free(mdctx);

    stringstream ss;
    ss << hex << setfill('0');
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << setw(2) << static_cast<int>(hash[i]);
    }
    // returns a hash string in a hexadecimal format
    return ss.str();
}