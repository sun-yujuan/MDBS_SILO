//
// Created by Yujuan Sun on 2022/5/4.
//

#include "Record.h"

using namespace std;

int Record::getValue() const {
    return value;
}

void Record::setValue(int value) {
    Record::value = value;
}

int Record::getTid() const {
    return TID;
}

void Record::setTid(int tid) {
    TID = tid;
}

bool Record::isLocked() const {
    return locked;
}

void Record::setLocked(bool locked) {
    Record::locked = locked;
}

int Record::getLockedBy() const {
    return lockedBy;
}

void Record::setLockedBy(int TID) {
    Record::lockedBy = TID;
}

Record::Record() : value(0), TID(-1), locked(false), lockedBy(-1) {}

Record::Record(int value) : value(value), TID(-1), locked(false), lockedBy(-1) {}