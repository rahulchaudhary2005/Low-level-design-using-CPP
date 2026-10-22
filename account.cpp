
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountHolder;
    string accountNumber;
    double balance;

public:
    void setDetails(string holder, string number, double initialBalance) {
        if (initialBalance < 0) {
            cout << "Invalid initial balance!" << endl;
            return;
        }

        accountHolder = holder;
        accountNumber = number;
        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!" << endl;
            return;
        }

        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!" << endl;
            return;
        }

        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
            return;
        }

        balance -= amount;
    }

    void displayDetails() {
        cout << "Account holder: " << accountHolder << endl;
        cout << "Account number: " << accountNumber << endl;
        cout << "Current balance: " << balance << endl;
    }
};

int main() {
    BankAccount b1;
    BankAccount b2;

    b1.setDetails("Rahul Chaudhary", "123456789", 10000);
    b1.deposit(5000);
    b1.withdraw(2000);
    b1.displayDetails();

    cout << "--------" << endl;

    b2.setDetails("John Doe", "987654321", 15000);
    b2.deposit(3000);
    b2.withdraw(1000);
    b2.displayDetails();

    return 0;
}
