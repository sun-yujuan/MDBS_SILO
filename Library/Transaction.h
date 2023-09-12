//
// Created by Yujuan Sun on 2022/5/4.
//

#ifndef MDBS_TRANSACTION_H
#define MDBS_TRANSACTION_H


#include "Record.h"
#include <list>
#include <unordered_map>

using namespace std;

/**
 * ReadRecords is a part of transaction
 * to document the record that read by the transaction
 */
struct ReadRecords {
    Record *record;

    /**
     * The original TID document the Transaction ID that observed during execution.
     * If it is no longer the latest version or is locked by another transaction,
     * the transaction releases its locks and aborts
     */
    int original_TID;

    explicit ReadRecords(Record *record) : record(record), original_TID(record->getTid()) {}

};

/**
 * WriteRecords is a part of transaction
 * to document the record that written by the transaction
 */
struct WriteRecords {

    Record *record;

    /** The new value being written to the record */
    int value;

    WriteRecords(Record *record, int value) : record(record), value(value) {}


};


/**
 * Transaction, storing the Transaction ID and the set of record read/written by it
 * It also has a map to store all the records that has been changed by it
 *
 */

class Transaction {
private:
    /** The transaction id of the transaction */
    int TID;

    list<ReadRecords> read_set{};
    list<WriteRecords> write_set{};

    /**
     * The records have been changed will save a copy here
     * <record_index, new_value>
     */
    unordered_map<int, int> changed_records;

public:
    /**
     * Create a transaction
     * @param tid: transaction ID
     */
    explicit Transaction(int tid);

    /**
     * Add new ReadRecord into the List of WriteRecord
     * @param read_record
     */
    void addRead(ReadRecords read_record);

    /**
     * Add new WriteRecord into the List of WriteRecord
     * @param write_record
     */
    void addWrite(WriteRecords write_record);


    /**
     * Getter and Setter
     */

    int getTid() const;

    const list<ReadRecords> &getReadSet() const;

    const list<WriteRecords> &getWriteSet() const;

    unordered_map<int, int> &getChangedRecords();

};

/**
 * STATUS of the operation
 * If the operation is fail or successful
 */
enum class STATUS {
    FAIL, SUCCESS
};

#endif //MDBS_TRANSACTION_H
