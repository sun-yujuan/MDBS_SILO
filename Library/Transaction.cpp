//
// Created by Yujuan Sun on 2022/5/4.
//

#include "Transaction.h"

Transaction::Transaction(int tid) : TID(tid) {}

int Transaction::getTid() const {
    return TID;
}

void Transaction::addRead(ReadRecords read_record) {
    read_set.push_back(read_record);
}

void Transaction::addWrite(WriteRecords write_record) {
    write_set.push_back(write_record);
}

const list<ReadRecords> &Transaction::getReadSet() const {
    return read_set;
}

const list<WriteRecords> &Transaction::getWriteSet() const {
    return write_set;
}

unordered_map<int, int> &Transaction::getChangedRecords() {
    return changed_records;
}


