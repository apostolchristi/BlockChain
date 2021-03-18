//
// Created by Toor on 2/22/2021.
//

#include "BlockChain.h"

using namespace std;

/*********************** CONSTRUCTORS **********************/
BlockChain::BlockChain() {
    Block genesis = Block::genesis();
    this->chain.push_back(genesis);
}

/*********************** OBJECT METHODS **********************/
void BlockChain::addBlock(TransactionData data) {
    Block &lastBlock = this->chain.back();
    Block newBlock = Block::mineBlock(lastBlock, data);
    this->chain.push_back(newBlock);
}

/*********************** STATIC METHODS **********************/

bool BlockChain::isChainValid(vector<Block> &chain) {

    vector<Block>::iterator it;
    string validatedHash;

/*    //Check if the currentTime block has a validHash
    for (it = chain.begin(); it != chain.end(); ++it) {
        Block currentBlock = *it;
        if (!currentBlock.isHashValid()) {
            //INVALID
            return false;
        }*/

//        //Check if this is the first object(genesis)
//        if (it != chain.begin()) {
//            Block previousBlock = *(it - 1);
//            if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
//                return false;
//            }
//        }
//    }

    if (!(chain.at(0) == Block::genesis())) { return false; }

    for (int i = 1; i < chain.size(); i++) {
        Block &block = chain[i];
        string actualLastHash = chain[i - 1].getHash();
        size_t lastDifficulty = chain[i - 1].getDifficulty();

        if (block.getPreviousHash() != actualLastHash) { return false; }

        validatedHash = CryptoHash::hashing_to_SHA256(block.getTimestamp(), block.getNonce(), block.getDifficulty(),
                                                      block.getPreviousHash(), block.data.getDataHash());

        if (block.getHash() != validatedHash) { return false; }

        /* Prevents Difficulty to be adjusted by any intruder  */
        if (std::abs(int(lastDifficulty - block.getDifficulty())) > 1) { return false; }
    }

    return true;
}


/*********************** GETTERS **********************/
vector<Block> BlockChain::getChain() const {
    return this->chain;
}

void BlockChain::replaceChain(vector<Block> &chain) {

    if (chain.size() <= this->chain.size()) {
        cerr << "The incoming chain must be longer\n";
        return;
    }

    if (!BlockChain::isChainValid(chain)) {
        cerr << "The incoming chain must be valid\n";
        return;
    }
    cout << "Replacing chain with: new chain" << endl;
    this->chain = chain;

}
