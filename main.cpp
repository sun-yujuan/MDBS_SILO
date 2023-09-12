#include <iostream>
#include <sstream>
#include "Library/Database.h"

using namespace std;

// help method
void printStatus(STATUS status) {
    if (status == STATUS::SUCCESS) {
        cout << "SUCCESS\n";
    } else {
        cout << "FAIL\n";
    }
}


int main() {
    Database database;
    cout<<"The database has been successfully initialized, please enter your command:\n";
    while (true) {
        string command;
        STATUS status{STATUS::FAIL};
        getline(cin, command);
        if (!command.compare("exit")) {
            break;
        }
        istringstream stream(command);
        if (!command.compare(0, 5, "begin")) {
            string command_part;
            int TID;
            stream >> command_part >> TID;
            status = database.begin(TID);

        } else if (!command.compare(0, 4, "read")) {
            string command_part;
            int TID;
            int data_index;
            stream >> command_part >> TID >> data_index;
            status = database.read(TID, data_index);
        } else if (!command.compare(0, 5, "write")) {
            string command_part;
            int TID;
            int data_index;
            int value;
            stream >> command_part >> TID >> data_index >> value;
            status = database.write(TID, data_index, value);
        } else if (!command.compare(0, 6, "commit")) {
            string command_part;
            int TID;
            stream >> command_part >> TID;
            status = database.commit(TID);
            if (status == STATUS::FAIL) {
                auto search = database.getTransactionPool().find(TID);

                // If there is no such transaction, read fail
                if (search != database.getTransactionPool().end()) {
                    database.deleteTransaction(TID);
                }
            } else {
                database.incrementEpoch();
                database.deleteTransaction(TID);
            }
        } else {
            cout << "Unknown Command!\n";
        }
        printStatus(status);


    }

    return 0;
}





