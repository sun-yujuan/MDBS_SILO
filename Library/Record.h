//
// Created by Yujuan Sun on 2022/5/4.
//

#ifndef MDBS_RECORD_H
#define MDBS_RECORD_H

/**
 * The Records are the data in the database
 * Every record has its own value
 * which can be read/written by the transaction
 */
class Record {
private:
    /** The value of the record */
    int value;

    /** The latest transaction id of the record */
    int TID;

    /** If the record is locked by write operation */
    bool locked;

    /** which transaction lock this record */
    int lockedBy;

public:
    /**
     * The default value of record is 0
     * TID = -1
     * locked = false
     * lockedBy = -1
     */
    Record();

    /**
     * @param value: users can set the value of record themselves
     */
    Record(int value);

    /** Getter and Setter */
    int getLockedBy() const;

    void setLockedBy(int lockedBy);

    int getValue() const;

    void setValue(int value);

    int getTid() const;

    void setTid(int tid);

    bool isLocked() const;

    void setLocked(bool locked);
};

#endif //MDBS_RECORD_H
