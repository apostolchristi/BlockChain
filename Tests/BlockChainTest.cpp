//
// Created by Toor on 2/22/2021.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Block.h"
#include "../CryptoHash.h"
#include "../BlockChain.h"

using ::testing::Eq;
using namespace std;
using namespace testing;

class BlockChainTest : public Test {

public:
    BlockChain *blockChain, *newChain;
    vector<Block> originalChain;

protected:

    BlockChainTest() {
                blockChain = new BlockChain();
                newChain = new BlockChain();
        originalChain = blockChain->chain;

    }

//    void SetUp() override {
//        blockChain = new BlockChain();
//        newChain = new BlockChain();
//
//        originalChain = blockChain->chain;
//    }

};

template<typename Base, typename T>
inline bool instanceof(const T *) {
    return std::is_base_of<Base, T>::value;
}


TEST_F(BlockChainTest, doesItStartWithTheGenesisBlocK) {
    bool isGenesisFirstBlockInTheChain = blockChain->chain.at(0) == Block::genesis();
    EXPECT_TRUE(isGenesisFirstBlockInTheChain);
}


TEST_F(BlockChainTest, addANewBlockToTheChain) {
    TransactionData data;
    blockChain->addBlock(data);
    bool isThisNewBlock = blockChain->chain.back().data == data;
    EXPECT_TRUE(isThisNewBlock);
}


TEST_F(BlockChainTest, whenTheChainDoesNotStartWithTheGenesisBlock) {
    bool isValidGenesis = BlockChain::isChainValid(blockChain->chain);
    EXPECT_FALSE(isValidGenesis);
}

TEST_F(BlockChainTest, whenTheNewChain_isNotLonger_and_doesNotReplaceTheChain) {
    time_t currentTime;
    TransactionData data(0.0, "Genesis", "Genesis", time(&currentTime));

    newChain->chain[0] = Block (time(&currentTime),1, 3,  "fake-genesis", "fake-genesis", data);

    blockChain->replaceChain(newChain->chain);
    EXPECT_EQ( blockChain->chain, originalChain);
}

TEST_F(BlockChainTest, whenTheNewChain_isLonger_and_doesNotReplaceTheChain) {
    time_t currentTime;

    newChain->addBlock( TransactionData (0.0, "Bears", "Bears", time(&currentTime)));
    newChain->addBlock( TransactionData (0.0, "Beets", "Beets", time(&currentTime)));
    newChain->addBlock( TransactionData (0.0, "BattleStar", "BattleStar", time(&currentTime)));

    newChain->chain[2].getHash() = "some fake hash";
}

TEST_F(BlockChainTest, whenTheNewChain_isLonger_and_replacesTheChain) {
    time_t currentTime;

    newChain->addBlock( TransactionData (0.0, "Bears", "Bears", time(&currentTime)));
    newChain->addBlock( TransactionData (0.0, "Beets", "Beets", time(&currentTime)));
    newChain->addBlock( TransactionData (0.0, "BattleStar", "BattleStar", time(&currentTime)));

}

TEST_F(BlockChainTest, whenThenNewChain_containsABlockWith_aJumpedDifficulty) {
    auto lastBlock = blockChain->chain[blockChain->chain.size()-1];
    auto previousHash = lastBlock.getHash();
    time_t timestamp {time(&timestamp)};
    TransactionData transactionData(0.0, "Bears", "Bears", time(&timestamp));
    size_t nonce {0};
    size_t difficulty = lastBlock.getDifficulty() - 3;
    string hash;

    hash = CryptoHash::hashing_to_SHA256(timestamp, nonce, difficulty, previousHash,
                                         transactionData.getDataHash());

    Block badBlock = Block(timestamp,nonce, difficulty, previousHash, hash, transactionData);

    blockChain->chain.push_back(badBlock);

    bool expectedBlockFromBlockchain = BlockChain::isChainValid(blockChain->chain);

    ASSERT_THAT(expectedBlockFromBlockchain, false);



}

string building_the_hash(size_t timestamp, size_t nonce, size_t difficulty, string &previousHash, size_t hashedData);

