#include <iostream>
#include "Block.cpp"
#include "TransactionData.h"
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <numeric>
#include <pstl/execution_defs.h>
#include "CryptoHash.h"
#include "Helper.h"
#include "lib/sha256.h"
#include "BlockChain.h"

using namespace std;

void averageWork() {
    time_t timestamp, prevTimeStamp, nextTimestamp, timeDiff;
    double average;
    vector<size_t> times;
    TransactionData data{0.0, "initial", "initial", time(&timestamp)};
    BlockChain *blockChain = new BlockChain();

    blockChain->addBlock(data);

    cout << "First block " << blockChain->chain[blockChain->chain.size() - 1];

    for (size_t i = 0; i < 2; i++) {
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


int main(int argc, char *argv[]) {
    time_t timestamp {time(&timestamp)};
    const TransactionData DATA (1, "test", "test", timestamp);
//    averageWork();



    string hex_val, bin_val;

//    hex_val = CryptoHash::hashing_to_SHA256(1212, 1, 1, "foo", 233);
//
//    hex_val = CryptoHash::hashing_to_SHA256("foo");
//
//    cout << "hex: " << hex_val << endl;
//    bin_val = Helper::hex_to_binary(hex_val);
//    cout << "bin: " << bin_val << endl;







    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();


    return 0;
}
