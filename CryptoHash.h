//
// Created by Toor on 2/19/2021.
//

#ifndef BLOCKCHAIN_CRYPTOHASH_H
#define BLOCKCHAIN_CRYPTOHASH_H


#include <string>
#include "lib/sha256.h"

using namespace std;

class CryptoHash {

public:
    static string hashing_to_SHA256(time_t timestamp, size_t nonce, size_t difficulty, const basic_string<char>& previousHash, size_t hashedData);
    static string hashing_to_SHA256(const basic_string<char>& value);


        private:
    static string hash_to_sha256(basic_string<char> value);
    static string hashed256BYTE_to_hex(unsigned char *buf);
    static string hashed256BYTE_to_binary(unsigned char *buf);
};


#endif //BLOCKCHAIN_CRYPTOHASH_H
