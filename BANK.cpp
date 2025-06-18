#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string details;

    Transaction(string type, double amount, string details)
        : type(type), amount(amount), details(details) {}
};

class Account {
private:
    string accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(string accNum, double initBalance = 0.0)
        : accountNumber(accNum), balance(initBalance) {}

    string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        history.emplace_back("Deposit", amount, "Self");
        cout << " Deposit successful. New Balance: " << balance << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << " Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        history.emplace_back("Withdrawal", amount, "Self");
        cout << " Withdrawal successful. New Balance: " << balance << endl;
        return true;
    }

    bool transfer(Account& toAccount, double amount) {
        if (amount > balance) {
            cout << " Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        toAccount.balance += amount;
        history.emplace_back("Transfer Out", amount, "To " + toAccount.getAccountNumber());
        toAccount.history.emplace_back("Transfer In", amount, "From " + accountNumber);
        cout << " Transfer successful!" << endl;
        return true;
    }

    void displayTransactions() const {
        cout << "\n Transaction History for Account " << accountNumber << ":\n";
        if (history.empty()) {
            cout << "No transactions yet.\n";
        } else {
            for (const auto& txn : history) {
                cout << txn.type << " of " << fixed << setprecision(2)
                     << txn.amount << " (" << txn.details << ")\n";
            }
        }
    }

    void displayAccountInfo() const {
        cout << "\n Account Number: " << accountNumber
             << "\n Balance: " << fixed << setprecision(2) << balance << endl;
        displayTransactions();
    }
};

class Customer {
private:
    string name;
    string customerId;
    Account account;

public:
    Customer(string name, string id, string accNum)
        : name(name), customerId(id), account(accNum) {}

    string getCustomerId() const {
        return customerId;
    }

    Account& getAccount() {
        return account;
    }

    void displayCustomerInfo() const {
        cout << "\n👤 Customer: " << name
             << "\n Customer ID: " << customerId << endl;
        account.displayAccountInfo();
    }
};

int findCustomerIndex(const vector<Customer>& customers, const string& id) {
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getCustomerId() == id) return i;
    }
    return -1;
}

int main() {
    vector<Customer> customers;
    int choice;

    while (true) {
        cout << "\n======= BANKING SYSTEM MENU =======\n";
        cout << "1. Create Customer & Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Account Information\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, id, accNum;
            cout << "Enter customer name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter customer ID: ";
            cin >> id;
            cout << "Enter account number: ";
            cin >> accNum;
            customers.emplace_back(name, id, accNum);
            cout << " Customer and Account created successfully.\n";
        } else if (choice >= 2 && choice <= 5) {
            string id;
            cout << "Enter your customer ID: ";
            cin >> id;
            int index = findCustomerIndex(customers, id);
            if (index == -1) {
                cout << " Customer not found.\n";
                continue;
            }

            Customer& cust = customers[index];
            Account& acc = cust.getAccount();

            if (choice == 2) {
                double amt;
                cout << "Enter amount to deposit: ";
                cin >> amt;
                acc.deposit(amt);
            } else if (choice == 3) {
                double amt;
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                acc.withdraw(amt);
            } else if (choice == 4) {
                string toId;
                double amt;
                cout << "Enter receiver's customer ID: ";
                cin >> toId;
                int toIndex = findCustomerIndex(customers, toId);
                if (toIndex == -1) {
                    cout << " Receiver not found.\n";
                    continue;
                }
                cout << "Enter amount to transfer: ";
                cin >> amt;
                acc.transfer(customers[toIndex].getAccount(), amt);
            } else if (choice == 5) {
                cust.displayCustomerInfo();
            }
        } else if (choice == 6) {
            cout << " Thank you for using the banking system!\n";
            break;
        } else {
            cout << " Invalid choice. Try again.\n";
        }
    }

    return 0;
}