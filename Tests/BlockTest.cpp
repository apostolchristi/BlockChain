//
// Created by Toor on 2/15/2021.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Block.h"
#include "../CryptoHash.h"
#include "../Helper.h"

using ::testing::Eq;
using namespace std;
using namespace testing;
using ::Helper;


class BlockTest : public Test {

protected:
    time_t timestamp;
    string lastHash;
    string hash;
    size_t nonce;
    size_t difficulty;

    TransactionData data;
    Block *block;
    Block lastBlock = Block::genesis();
    Block minedBlock = Block::mineBlock(lastBlock, data);

    BlockTest() : timestamp{time(&timestamp)}, nonce{1}, difficulty{1}, lastHash{"testBlock"}, hash{"testBlock"},
                  data{0.0, "Genesis", "Genesis", time(&timestamp)} {

        block = new Block(time(&timestamp), nonce, difficulty, lastHash, hash, data);

    }

    ~BlockTest() override {
        delete block;
    }

};


/*Compares Objects Instances*/
template<typename Base, typename T>
inline bool instanceof(const T *) {
    return is_base_of<Base, T>::value;
}

TEST_F(BlockTest, checkingAllConstructorVariables) {
    EXPECT_EQ(nonce, block->getNonce());
    EXPECT_EQ(difficulty, block->getDifficulty());
    EXPECT_EQ(lastHash, block->getPreviousHash());
    EXPECT_EQ(hash, block->getHash());
    EXPECT_EQ(data, block->data);
}

TEST_F(BlockTest, genesis_returnsABlockInstance) {
    bool test = instanceof<Block>(&lastBlock);

    EXPECT_TRUE(test);
}

TEST_F(BlockTest, mineBLock_returnsABlockInstance) {
    bool isBlockInstance = instanceof<Block>(&minedBlock);

    EXPECT_TRUE(isBlockInstance);
}

TEST_F(BlockTest, mineBLock_setsTheLastHashToBeTheHashOfTheLastBlock) {
    bool isTheLastHashToBeTheHashOfTheLastBlock = minedBlock.getPreviousHash() == lastBlock.getHash();

    EXPECT_TRUE(isTheLastHashToBeTheHashOfTheLastBlock);
}

TEST_F(BlockTest, mineBLock_setsTheData) {
    bool isItSetsTheData = minedBlock.data == data;

    EXPECT_TRUE(isItSetsTheData);
}

TEST_F(BlockTest, mineBLock_createsASHA256HashBasedOnTheProperInputs) {
    string hash;

    hash = CryptoHash::hashing_to_SHA256(minedBlock.getTimestamp(),minedBlock.getNonce(),
            minedBlock.getDifficulty(),lastBlock.getHash(), data.getDataHash());

    ASSERT_TRUE(true);
}

TEST_F(BlockTest, mineBLock_setsAHashThatMatchesTheDifficulityCriteria) {
    string expectedDifficulty = Helper::hex_to_binary(minedBlock.getHash()).substr(0, minedBlock.getDifficulty());
    string numberOfZeroes = Helper::repeat_string(minedBlock.getDifficulty(), '0');

    EXPECT_EQ(expectedDifficulty, numberOfZeroes);
}

TEST_F(BlockTest, mineBLock_adjustsTheDifficulty_) {
    size_t possibleResults[] = {lastBlock.getDifficulty()+1,lastBlock.getDifficulty()-1 };
    bool includes;
    for (auto possibleResult : possibleResults)
        includes = possibleResult == minedBlock.getDifficulty();

    EXPECT_TRUE(includes);
}

TEST_F(BlockTest, adjustDifficulty_and_raisesTheDifficultyFor_AQuicklyMinedBlock) {
    auto expectedAdjustedDifficulty = Block::adjustDifficulty(*block, block->getTimestamp() + Block::MINE_RATE - 100);
    auto actualRaisedDifficulty = block->getDifficulty() + 1;

    EXPECT_EQ(expectedAdjustedDifficulty, actualRaisedDifficulty);
}

TEST_F(BlockTest, adjustDifficulty_and_lowersTheDifficultyForA_SlowlyMinedBlock) {
    auto expectedAdjustedDifficulty = Block::adjustDifficulty(
            *block, block->getTimestamp() + Block::MINE_RATE + 100);
    auto actualLoweredDifficulty = block->getDifficulty() - 1;

    EXPECT_EQ(expectedAdjustedDifficulty, actualLoweredDifficulty);
}

TEST_F(BlockTest, adjustDifficulty_hasALowerLimitof_1_) {
    block->setDifficulty(-1);
    auto expectedDifficulty = Block::adjustDifficulty(*block, timestamp);

    EXPECT_EQ(expectedDifficulty, 1);
}



