//
// Created by Toor on 2/15/2021.
//

#include "Block.h"


/*********************** CONSTRUCTORS **********************/
Block::Block(time_t timestamp, size_t nonce, size_t difficulty, string previousHash, string hash, TransactionData data)
        :
        timestamp{timestamp}, nonce{nonce}, difficulty{difficulty}, previousHash{previousHash}, blockHash{hash},
        data{data} {}

/*********************** STATIC METHODS **********************/
Block Block::genesis() {
    time_t currentTime;
    TransactionData data(0.0, "Genesis", "Genesis", time(&currentTime));

    Block genesis(time(&currentTime), 0, INITIAL_DIFFICULTY, "genesis", "genesis", data);
    return genesis;
}

Block Block::mineBlock(Block &lastBlock, TransactionData &transactionData) {
    string previousHash, hash;
    time_t timestamp;
    size_t difficulty, nonce = {0};
    previousHash = lastBlock.getHash();

    do {
        nonce++;
        difficulty = adjustDifficulty(lastBlock, time(&timestamp));
        hash = CryptoHash::hashing_to_SHA256(time(&timestamp), nonce, difficulty, previousHash,
                                             transactionData.getDataHash());
        //Dif check based on binary hash
    } while (Helper::hex_to_binary(hash).substr(0, difficulty) != Helper::repeat_string(difficulty, '0'));


    return Block(time(&timestamp), nonce, difficulty, previousHash, hash, transactionData);
}

size_t Block::adjustDifficulty(Block &originalBlock, time_t timestamp) {
    size_t difficulty;
    time_t timestampDifference;

    difficulty = originalBlock.getDifficulty();
    timestampDifference = timestamp - originalBlock.getTimestamp();

    //Lower limit
    if(difficulty < 1) {
        return 1;
    }

    //lowersTheDifficultyForA_SlowlyMinedBlock
    if (timestampDifference > MINE_RATE) {
        return difficulty - 1;
    }

    //raisesTheDifficultyFor_AQuicklyMinedBlock
    return difficulty + 1;
}

/*********************** OBJECT METHODS **********************/
/*
bool Block::isHashValid() {
    return generateBlockHash() == getHash();
}
*/

////Private Method
/*string Block::generateBlockHash() {
    hash<string> blockHash;
    CryptoHash cryptoHash;
    size_t defaultCPPHash_of_Data, defaultCPPHash_of_Block;
    string blockHash_toString, hashedBlock256;

    defaultCPPHash_of_Data = transactionData.getDataHash();
    blockHash_toString = to_string(getTimestamp()) + getPreviousHash();
    *//* "defaultCPPHash_of_Data << 1" = For your left shift operator "<<" it adds zeros for the number of bits given on the right.
1 << 20 Convert 1 to binary = 0001
adding the 20 zeros we get
000100000000000000000000
convert this to integer you get
1048576
which is actually 2^20 .*//*
    defaultCPPHash_of_Block = blockHash(blockHash_toString) ^ defaultCPPHash_of_Data << 1;
    hashedBlock256 = cryptoHash.hash_to_sha256(to_string(defaultCPPHash_of_Block));

    return hashedBlock256;
}*/


/*********************** OPERATORS OVERLOADING **********************/
bool Block::operator==(const Block &rhs) const {
    return (this->getHash() == rhs.getHash());
}

//TODO: Add TransactionData info
ostream &operator<<(ostream &os, const Block &block) {
    os << "Block {\n"
       << "timestamp: " << block.getTimestamp() << " ,\n"
       << "nonce: " << block.getNonce() << " ,\n"
       << "difficulty: " << block.getDifficulty() << " ,\n"
       << "hash: " << block.getHash() << " ,\n"
       << "lastHash: " << block.getPreviousHash() << " }\n";

    return os;
}

/*********************** GETTERS **********************/
time_t Block::getTimestamp() const {
    return this->timestamp;
}

string Block::getHash() const {
    return this->blockHash;
}

string Block::getPreviousHash() const {
    return this->previousHash;
}

size_t Block::getNonce() const {
    return this->nonce;
}

size_t Block::getDifficulty() const {
    return this->difficulty;
}

void Block::setDifficulty(size_t difficulty) {
    Block::difficulty = difficulty;
}









