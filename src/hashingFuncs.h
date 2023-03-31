#ifndef SHA256_H
#define SHA256_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>

using namespace std;

string sha1(const string& input);
string sha256(const string& input);
string md5(const string& input);

#endif
