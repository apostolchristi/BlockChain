//
// Created by Toor on 2/22/2021.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <vector>
#include <memory>
#include "Block.h"
#include "CryptoHash.h"

using namespace std;

class BlockChain {
private:

public:

    vector<Block> chain;

    /*********************** CONSTRUCTORS **********************/
    BlockChain();

    /*********************** OBJECT METHODS **********************/
    void addBlock(TransactionData data);
    void replaceChain(vector<Block> &chain);

    /*********************** STATIC METHODS **********************/
   static bool isChainValid(vector<Block> &chain);

    /*********************** GETTERS **********************/
    vector<Block> getChain() const;
};


#endif //BLOCKCHAIN_BLOCKCHAIN_H
