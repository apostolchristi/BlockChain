//
// Created by Toor on 2/19/2021.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../CryptoHash.h"
using namespace std;

class HashTestFixture : public testing::Test {

public:
    CryptoHash *obj;

    HashTestFixture() {
        obj = new CryptoHash();
    }

    ~HashTestFixture() override {
        delete obj;
    }

};

TEST_F(HashTestFixture, GeneratesASHA256Output) {
    string arg = "foo";
    string hashedHexValue = CryptoHash::hashing_to_SHA256(arg);
    string hash = "2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae";
    EXPECT_EQ(hash, hashedHexValue);

}
