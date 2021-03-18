//
// Created by Toor on 2/19/2021.
//

#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <bitset>
#include "CryptoHash.h"

using namespace std;

string CryptoHash::hashing_to_SHA256(time_t timestamp, size_t nonce, size_t difficulty, const basic_string<char>& previousHash, size_t hashedData) {
    stringstream stream;
    stream << timestamp << nonce << difficulty << previousHash << hashedData;

    return hash_to_sha256(stream.str());
}

string CryptoHash::hashing_to_SHA256(const basic_string<char>& value) {
    return hash_to_sha256(value);
}


string CryptoHash::hash_to_sha256(basic_string<char> value) {
    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    auto *arg = new unsigned char[value.length()];

    for (int i = 0; i < value.length(); ++i) {
        arg[i] = value[i];
    }

    sha256_init(&ctx);
    sha256_update(&ctx, arg, value.length());
    sha256_final(&ctx, buf);

    delete[]arg;
    return hashed256BYTE_to_hex(buf);
}

string CryptoHash::hashed256BYTE_to_hex(unsigned char *buf) {
    stringstream ss;

    for (int i = 0; i < SHA256_BLOCK_SIZE; ++i) {
//        printf ("%02x", buf[i]);
        ss << hex << setw(2) << setfill('0') << (int) buf[i];
    }

    string hashedHexValue = ss.str();
    return hashedHexValue;
}

string CryptoHash::hashed256BYTE_to_binary(unsigned char *buf) {
    string hashedBinaryValue;

    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        hashedBinaryValue += bitset<8>(buf[i]).to_string();
    }

    return hashedBinaryValue;
}







