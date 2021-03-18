//
// Created by Toor on 2/15/2021.
//

#include "TransactionData.h"


TransactionData::TransactionData() : amount{0.0}, senderKey{"nullptr"}, receiverKey("nullptr"),
                                     timestamp{time(&timestamp)} {

}

TransactionData::TransactionData(double amount, string senderKey, string receiverKey, time_t time)
        : amount{amount}, senderKey{senderKey}, receiverKey{receiverKey}, timestamp{time} {

}

size_t TransactionData::getDataHash() {
    hash<string> dataHash;
    string data_ToString;
    size_t defaultCPPHash_of_Data;

    data_ToString = to_string(amount) + receiverKey + senderKey + to_string(timestamp);
    defaultCPPHash_of_Data = dataHash(data_ToString);

    return defaultCPPHash_of_Data;
}

bool TransactionData::operator==(const TransactionData &rhs) const {
    return (this->senderKey == rhs.senderKey);
}
