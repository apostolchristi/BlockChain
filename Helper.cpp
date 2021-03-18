//
// Created by Toor on 2/24/2021.
//

#include <vector>
#include <numeric>
#include "Helper.h"
#include "TransactionData.h"
#include "BlockChain.h"

using namespace std;

/*********************** STATIC METHODS **********************/
size_t Helper::string_to_sizeT(string &str) {
    stringstream stream(str);
    size_t result;
    stream >> result;

    return result;
}

string Helper::repeat_string(size_t difficulty, char value) {
    string repeated_string;
    for (int i = 0; i < difficulty; ++i) {
        repeated_string += value;
    }
    return repeated_string;
}

string Helper:: hex_to_binary(basic_string<char> hex) {
    long int i = 0;
    string binaryValue;

    while (hex[i]) {

        switch (hex[i]) {
            case '0':
                binaryValue += "0000";
                break;
            case '1':
                binaryValue += "0001";
                break;
            case '2':
                binaryValue += "0010";
                break;
            case '3':
                binaryValue += "0011";
                break;
            case '4':
                binaryValue += "0100";
                break;
            case '5':
                binaryValue += "0101";
                break;
            case '6':
                binaryValue += "0110";
                break;
            case '7':
                binaryValue += "0111";
                break;
            case '8':
                binaryValue += "1000";
                break;
            case '9':
                binaryValue += "1001";
                break;
            case 'A':
            case 'a':
                binaryValue += "1010";
                break;
            case 'B':
            case 'b':
                binaryValue += "1011";
                break;
            case 'C':
            case 'c':
                binaryValue += "1100";
                break;
            case 'D':
            case 'd':
                binaryValue += "1101";
                break;
            case 'E':
            case 'e':
                binaryValue += "1110";
                break;
            case 'F':
            case 'f':
                binaryValue += "1111";
                break;
            default:
                cout << "\nInvalid hexadecimal digit "
                     << hex[i];
        }
        i++;
    }
    return binaryValue;
}

void Helper::averageWork() {
    time_t timestamp, prevTimeStamp, nextTimestamp, timeDiff;
    double average;
    vector<size_t> times;
    TransactionData data{0.0, "initial", "initial", time(&timestamp)};
    auto *blockChain = new BlockChain();

    blockChain->addBlock(data);

    for (size_t i = 0; i < 10000; i++) {
        prevTimeStamp = blockChain->chain.at(blockChain->chain.size() - 1).getTimestamp();

        blockChain->addBlock(TransactionData{(double) i, "initial", "initial", time(&timestamp)});
        Block &nextBlock = blockChain->chain.at(blockChain->chain.size() - 1);

        nextTimestamp = nextBlock.getTimestamp();
        timeDiff = nextTimestamp - prevTimeStamp;
        times.push_back(timeDiff);

        average = (double) accumulate(times.begin(), times.end(), 0) / times.size();

        cout << "Time to mine block: " << timeDiff << "ms. Difficulty: " << nextBlock.getDifficulty()
             << ". Average time: " << average << "ms" << endl;

    }
}




