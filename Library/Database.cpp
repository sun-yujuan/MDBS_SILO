//
// Created by Yujuan Sun on 2022/5/11.
//

#include <iostream>
#include "Database.h"

STATUS Database::begin(int transactionID) {
    transaction_pool.insert({transactionID, Transaction(transactionID)});
    return STATUS::SUCCESS;
}


STATUS Database::read(int transactionID, int dataIndex) {
    auto search = transaction_pool.find(transactionID);

    // If there is no such transaction, read fail
    if (search == transaction_pool.end()) {
        return STATUS::FAIL;
    }

    // Add the read operation to the read_set
    search->second.addRead(ReadRecords(&records.at(dataIndex)));

    auto record = search->second.getChangedRecords().find(dataIndex);
    if (record != search->second.getChangedRecords().end()) {
        cout << record->second << '\t';
    } else {
        cout << records.at(dataIndex).getValue() << '\t';
    }

    return STATUS::SUCCESS;
}


STATUS Database::write(int transactionID, int dataIndex, int value) {
    auto search = transaction_pool.find(transactionID);

    // If there is no such transaction, write fail
    if (search == transaction_pool.end()) {
        return STATUS::FAIL;
    }

    // Add the read operation to the read_set
    search->second.addWrite(WriteRecords(&records.at(dataIndex), value));
    search->second.getChangedRecords().insert({dataIndex, value});
    return STATUS::SUCCESS;
}


STATUS Database::commit(int transactionID) {
    auto search = transaction_pool.find(transactionID);

    // If there is no such transaction, write fail
    if (search == transaction_pool.end()) {
        return STATUS::FAIL;
    }

    Transaction transaction = search->second;
    // Phase 1
    // lock the record written by this transaction
    // if the record is already locked by other transaction, commit failed.
    for (const auto &item: transaction.getWriteSet()) {
        if (item.record->isLocked() && item.record->getLockedBy() != transactionID) {
            return STATUS::FAIL;
        }

        item.record->setLocked(true);
        item.record->setLockedBy(transactionID);
    }

    // Phase 2
    for (const auto &item: transaction.getReadSet()) {
        // Examine the lock bit of record
        // If the record is locked by other transaction, commit failed.
        if (item.record->isLocked() && item.record->getLockedBy() != transactionID) {
            return STATUS::FAIL;
        }
        // Compare the latest TID of record with the TID in the read set
        if (item.original_TID != item.record->getTid()) {
            return STATUS::FAIL;
        }
    }

    // Phase 3
    // finish all write operation and release locks and update record
    for (const auto &item: transaction.getWriteSet()) {
        // update the value of record
        item.record->setValue(item.value);
        // update the latest transaction ID of record
        item.record->setTid(transactionID);
        // release write lock
        item.record->setLocked(false);
    }

    return STATUS::SUCCESS;
}


STATUS Database::incrementEpoch() {
    epoch++;
    return STATUS::SUCCESS;
}

int Database::getEpoch() const {
    return epoch;
}

const unordered_map<int, Transaction> &Database::getTransactionPool() const {
    return transaction_pool;
}

// help method
void Database::deleteTransaction(int transactionID) {
    for (auto it = transaction_pool.begin(); it != transaction_pool.end();) {
        if (it->first == transactionID) {
            it = transaction_pool.erase(it);
        } else {
            ++it;
        }
    }
}




