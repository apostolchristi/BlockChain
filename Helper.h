//
// Created by Toor on 2/24/2021.
//

#ifndef BLOCKCHAIN_HELPER_H
#define BLOCKCHAIN_HELPER_H


#include "string"
#include <sstream>

using namespace std;

class Helper {

public:
    static size_t string_to_sizeT(string &str);
    static string repeat_string(size_t difficulty, char value);
    static string hex_to_binary(basic_string<char> hex);
    void averageWork();


};


#endif //BLOCKCHAIN_HELPER_H
