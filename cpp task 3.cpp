#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Transaction {
private:
    string type;
    double amount;
public:
    Transaction(string t, double a) {
        type = t;
        amount = a;
    }
    void display() const {
        cout << type << " : Rs. " << amount << endl;
    }
};

class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> history;
public:
    Account(int accNo, double bal = 0) {
        accountNumber = accNo;
        balance = bal;
    }
    int getAccountNumber() const {
        return accountNumber;
    }
    double getBalance() const {
        return balance;
    }
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            history.push_back(Transaction("Deposit", amount));
            cout << "Deposit Successful!\n";
        }
    }
    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            history.push_back(Transaction("Withdrawal", amount));
            cout << "Withdrawal Successful!\n";
        } else {
            cout << "Insufficient Balance!\n";
        }
    }
    bool transfer(Account &receiver, double amount) {
        if (amount <= balance) {
            balance -= amount;
            receiver.balance += amount;

            history.push_back(Transaction(
                "Transfer Sent", amount));

            receiver.history.push_back(Transaction(
                "Transfer Received", amount));

            cout << "Transfer Successful!\n";
            return true;
        }

        cout << "Transfer Failed! Insufficient Balance.\n";
        return false;
    }

    void showTransactions() const {
        cout << "\nTransaction History\n";
        cout << "-------------------\n";

        if (history.empty()) {
            cout << "No Transactions Found.\n";
            return;
        }

        for (const auto &t : history) {
            t.display();
        }
    }

    void displayAccountInfo() const {
        cout << "\nAccount Number : "
             << accountNumber << endl;

        cout << "Current Balance : Rs. "
             << balance << endl;
    }
};
class Customer {
private:
    int customerID;
    string name;
    Account account;

public:
    Customer(int id, string n, int accNo)
        : customerID(id),
          name(n),
          account(accNo) {}

    int getCustomerID() const {
        return customerID;
    }

    string getName() const {
        return name;
    }

    Account& getAccount() {
        return account;
    }

    void displayCustomer() const {
        cout << "\nCustomer ID : "
             << customerID << endl;

        cout << "Name : "
             << name << endl;

        account.displayAccountInfo();
    }
};

int main() {

    vector<Customer> customers;

    int choice;

    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Customer\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Fund Transfer\n";
        cout << "5. View Account Information\n";
        cout << "6. View Transaction History\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {

            int id, accNo;
            string name;

            cout << "Enter Customer ID: ";
            cin >> id;

            cin.ignore();

            cout << "Enter Customer Name: ";
            getline(cin, name);

            cout << "Enter Account Number: ";
            cin >> accNo;

            customers.push_back(
                Customer(id, name, accNo));

            cout << "Customer Created Successfully!\n";
        }

        else if (choice == 2) {

            int id;
            double amount;

            cout << "Enter Customer ID: ";
            cin >> id;

            cout << "Enter Amount: ";
            cin >> amount;

            for (auto &c : customers) {
                if (c.getCustomerID() == id) {
                    c.getAccount().deposit(amount);
                }
            }
        }

        else if (choice == 3) {

            int id;
            double amount;

            cout << "Enter Customer ID: ";
            cin >> id;

            cout << "Enter Amount: ";
            cin >> amount;

            for (auto &c : customers) {
                if (c.getCustomerID() == id) {
                    c.getAccount().withdraw(amount);
                }
            }
        }

        else if (choice == 4) {

            int senderID, receiverID;
            double amount;

            cout << "Enter Sender ID: ";
            cin >> senderID;

            cout << "Enter Receiver ID: ";
            cin >> receiverID;

            cout << "Enter Amount: ";
            cin >> amount;

            Customer *sender = nullptr;
            Customer *receiver = nullptr;

            for (auto &c : customers) {
                if (c.getCustomerID() == senderID)
                    sender = &c;

                if (c.getCustomerID() == receiverID)
                    receiver = &c;
            }

            if (sender && receiver) {
                sender->getAccount().transfer(
                    receiver->getAccount(),
                    amount
                );
            } else {
                cout << "Customer Not Found!\n";
            }
        }

        else if (choice == 5) {

            int id;

            cout << "Enter Customer ID: ";
            cin >> id;

            for (const auto &c : customers) {
                if (c.getCustomerID() == id) {
                    c.displayCustomer();
                }
            }
        }

        else if (choice == 6) {

            int id;

            cout << "Enter Customer ID: ";
            cin >> id;

            for (auto &c : customers) {
                if (c.getCustomerID() == id) {
                    c.getAccount().showTransactions();
                }
            }
        }

    } while (choice != 7);

    cout << "\nThank You!\n";

    return 0;
}
