/**********************************************************************
 *  A file that contains hashing implementation for genome k-meres    *
 **********************************************************************/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include "hashingFuncs.h"

/********************************************************************
 * Add hashing functions using OpenSSL library | Author: Lea Faber  *
 ********************************************************************/                     

/* 
 * The more hash functions are used, the probability of false positives will be lower, 
 * but it will take longer to insert or query an element in the filter.
 */

// 160-bit hash value
string sha1(const string& input) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_sha1();

    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input.c_str(), input.size());
    EVP_DigestFinal_ex(mdctx, hash, NULL);
    EVP_MD_CTX_free(mdctx);

    stringstream ss;
    ss << hex << setfill('0');
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        ss << setw(2) << static_cast<int>(hash[i]);
    }
    // returns a hash string in a hexadecimal format
    return ss.str();
}

// 256-bit hash value
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

string md5(const string& input) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_md5();

    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input.c_str(), input.size());
    EVP_DigestFinal_ex(mdctx, hash, NULL);
    EVP_MD_CTX_free(mdctx);

    stringstream ss;
    ss << hex << setfill('0');
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        ss << setw(2) << static_cast<int>(hash[i]);
    }
    // returns a hash string in a hexadecimal format
    return ss.str();
}

