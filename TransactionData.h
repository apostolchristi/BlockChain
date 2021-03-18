//
// Created by Toor on 2/15/2021.
//

#ifndef BLOCKCHAIN_TRANSACTIONDATA_H
#define BLOCKCHAIN_TRANSACTIONDATA_H

#include "string"
#include "iostream"
#include "CryptoHash.h"
#include "Helper.h"
using namespace std;


struct TransactionData {

    double amount;
    string senderKey;
    string receiverKey;
    time_t timestamp;

    TransactionData();
    TransactionData(double amount, string senderKey, string receiverKey, time_t time);
    size_t getDataHash();

    bool operator==(const TransactionData &rhs) const;


};


#endif //BLOCKCHAIN_TRANSACTIONDATA_H
