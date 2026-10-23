
#include <iostream>
#include <memory>
using namespace std;

// Abstract strategy
class TransactionStrategy {
public:
    virtual void transaction() = 0;
    virtual ~TransactionStrategy() = default;
};

// Concrete strategies
class CreditCardTransaction : public TransactionStrategy {
public:
    void transaction() override {
        cout << "Transaction done by credit card\n";
    }
};

class DebitCardTransaction : public TransactionStrategy {
public:
    void transaction() override {
        cout << "Transaction done by debit card\n";
    }
};

class UpiTransaction : public TransactionStrategy {
public:
    void transaction() override {
        cout << "Transaction done by UPI\n";
    }
};

class CashTransaction : public TransactionStrategy {
public:
    void transaction() override {
        cout << "Transaction done by cash\n";
    }
};

class WalletTransaction : public TransactionStrategy {
public:
    void transaction() override {
        cout << "Transaction done by wallet\n";
    }
};

// Context class
class Transaction {
private:
    unique_ptr<TransactionStrategy> strategy;

public:
    Transaction(unique_ptr<TransactionStrategy> s)
        : strategy(move(s)) {}

    void doTransaction() {
        strategy->transaction();
    }
};

int main() {
    Transaction byCreditCard(
        make_unique<CreditCardTransaction>()
    );
    byCreditCard.doTransaction();

    Transaction byDebitCard(
        make_unique<DebitCardTransaction>()
    );
    byDebitCard.doTransaction();

    Transaction byUpi(
        make_unique<UpiTransaction>()
    );
    byUpi.doTransaction();

    Transaction byCash(
        make_unique<CashTransaction>()
    );
    byCash.doTransaction();

    Transaction byWallet(
        make_unique<WalletTransaction>()
    );
    byWallet.doTransaction();

    return 0;
}
