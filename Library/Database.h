//
// Created by Yujuan Sun on 2022/5/11.
//

#ifndef MDBS_DATABASE_H
#define MDBS_DATABASE_H

#include "Record.h"
#include "Transaction.h"
#include <array>
#include <unordered_map>

/**
 * Database is where store all the records needed
 * It allows transactions reading/writing records
 */
class Database {
private:
    /**
     * The database is a simple array of integers of size 1000
     */
    array<Record, 1000> records{};

    /**
     * Epochs are Time periods
     * which are used to ensure serializable recovery etc.
     */
    int epoch{0};

    /**
     * Transaction pool documents all the transactions
     * that has operations on the database
     */
    unordered_map<int, Transaction> transaction_pool;

public:
    /**
     * Begin the transaction
     * @param transactionID
     * @return: If the operation is successful/fail
     */
    STATUS begin(int transactionID);

    /**
     * The transaction read the record
     * @param transactionID
     * @param dataIndex: Which record is read
     * @return: If the operation is successful/fail
     */
    STATUS read(int transactionID, int dataIndex);


    /**
     * The transaction write value to the record
     * @param transactionID
     * @param dataIndex: Which record is written
     * @param value: new value of the record
     * @return: If the operation is successful/fail
     */
    STATUS write(int transactionID, int dataIndex, int value);


    /**
     * Commit protocol
     * @param transactionID
     * @return: If the operation is successful/fail
     */
    STATUS commit(int transactionID);

    /**
     * Epoch increment itself
     * @return: If the operation is successful/fail
     */
    STATUS incrementEpoch();


    /**
     * delete transaction from transaction pool
     * @param transactionID
     */
    void deleteTransaction(int transactionID);

    /**
     * Getter and setter
     */
    int getEpoch() const;

    const unordered_map<int, Transaction> &getTransactionPool() const;

};


#endif //MDBS_DATABASE_H
