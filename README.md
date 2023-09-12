# Speedy Transactions in Multicore In-Memory Databases

## Description
Silo is a new in-memory database that achieves excellent performance and scalability on modern multicore machines. In this Project, the commit protocol of Silo is briefly implemented.
Silo is kind of complicated, especially when it comes to concurrency. So in this project everything runs in a single thread and the "database" is a simple array of integers of size 1000 (every value is initially zero).

## Instruction
### The following instructions are implemented:

1. **begin [TransactionId]**   _# Starts a transaction with the given id_.
2. **commit [TransactionId]**   _# Ends a transaction with the given id, the application should return whether a transaction can commit based on SILO's commit protocol._
3. **read [TransactionId]** [Index] [Value]   _# A transaction reads a value at index, the application should return the current value (and it should internally add the index and the returned value to the transaction's read set)._
4. **write [TransactionId]** [Index] [Value]   _# A transaction writes a value (and it should internally add the index to the transaction's write set)._
5. **incrementEpoch**   _# The epoch number is incremented.(This instruction will be done automatically after commit successfully)_

Before using any transaction, we should firstly use begin[Transaction] to initialize it. Then this transaction will be added into transaction pool.
After initialize the transaction, we can use it to read and write to the transaction. The read and write instruction are given above.

***Attention!*** There is one different implementation from real Silo, namely the transaction can see its own updates.  
For example: The initial value of record 1 is 0, transaction 1 uses following instructions  
write 1 1 1   
read 1 1   
commit 1   
In real Silo, the value being read should be 0, but in this implementation the value being read should be 1.

### The usage of this Project:
Enter the instructions above from the command line