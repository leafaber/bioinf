/**********************************************************************
 *  A file that contains hashing implementation for genome k-meres    *
 **********************************************************************/

#include "hashingFuncs.h"

/********************************************************************
 * Add hashing functions using OpenSSL library | Author: Lea Faber  *
 * Create hashFunction.h file                  | Author: Lea Faber  *
 ********************************************************************/                     

/* 
 * The more hash functions are used, the probability of false positives will be lower, 
 * but it will take longer to insert or query an element in the filter. (Bloom filter)
 * 
 * Only 2 hash functions are used in CF, need to decide which ones.
 * Idea (alternative):
 *       instead of using e.g sha1 and md5 the second hash func. is just an XOR of the first
 *       h1 (x) = hash(x)
 *       h2 (x) = h1 (x) ⊕ hash(ξx )
 *                                                             - Lea
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

