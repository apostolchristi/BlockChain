//
// Created by Toor on 2/15/2021.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include <ctime>
#include <string>
#include <sstream>
#include "TransactionData.h"
#include "CryptoHash.h"
#include "Helper.h"

using namespace std;



class Block {

public:
    static constexpr size_t INITIAL_DIFFICULTY {3};
    static constexpr size_t MINE_RATE {100};

private:
    time_t timestamp;
    size_t nonce;
    size_t difficulty;
    string blockHash;
    string previousHash;

    //Private Method
//    string generateBlockHash();
    static string generateBlockHash(Block &lastBlock, TransactionData &transactionData);


public:
    TransactionData data;

    /*********************** CONSTRUCTORS **********************/
    Block(time_t timestamp, size_t nonce, size_t difficulty, string previousHash, string hash, TransactionData data);

    ~Block() = default;

    /*********************** OBJECT METHODS **********************/
//    bool isHashValid();



    /*********************** STATIC METHODS **********************/
    static Block genesis();

    static Block mineBlock(Block &lastBlock, TransactionData &transactionData);
    static size_t adjustDifficulty(Block &originalBlock, time_t timestamp);

    /*********************** OPERATORS OVERLOADING **********************/
    bool operator==(const Block &rhs) const;

    friend ostream &operator<<(ostream &os, const Block &block);

    /*********************** GETTERS **********************/
    time_t getTimestamp() const;

    size_t getNonce() const;

    size_t getDifficulty() const;

    string getHash() const;

    string getPreviousHash() const;

    //FIXME:just for test purposes. Remove me later.
    void setDifficulty(size_t difficulty);
};

#endif //BLOCKCHAIN_BLOCK_H
