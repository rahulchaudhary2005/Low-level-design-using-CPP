
#include <iostream>
#include <memory>
#include <string>
#include <utility>
using namespace std;

// ==========================================
// 1. PAYMENT STRATEGY
// ==========================================

class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};

class UpiPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Payment of Rs. " << amount
             << " processed using UPI.\n";
    }
};

class CreditCardPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Payment of Rs. " << amount
             << " processed using Credit Card.\n";
    }
};

class CashOnDelivery : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Cash on Delivery selected. Collect Rs. "
             << amount << " at delivery.\n";
    }
};

// ==========================================
// 2. TRANSACTION
// ==========================================

class Transaction {
private:
    unique_ptr<PaymentStrategy> strategy;

public:
    Transaction(unique_ptr<PaymentStrategy> s)
        : strategy(move(s)) {}

    void processPayment(double amount) {
        if (strategy) {
            strategy->pay(amount);
        }
    }
};

// ==========================================
// 3. ORDER
// ==========================================

class Order {
private:
    int orderId;
    double amount;
    string status;

public:
    Order(int id, double total)
        : orderId(id), amount(total), status("Placed") {}

    void checkout(unique_ptr<PaymentStrategy> strategy) {
        Transaction transaction(move(strategy));

        cout << "\n--- Processing Order ---\n";
        cout << "Order ID: " << orderId << '\n';

        transaction.processPayment(amount);
        status = "Confirmed";
    }

    void showDetails() const {
        cout << "\n--- Order Details ---\n";
        cout << "Order ID: " << orderId << '\n';
        cout << "Amount: Rs. " << amount << '\n';
        cout << "Status: " << status << '\n';
    }

    int getOrderId() const {
        return orderId;
    }
};

// ==========================================
// 4. DELIVERY PARTNER
// ==========================================

class DeliveryPartner {
private:
    int partnerId;
    string name;
    string currentLocation;
    string deliveryStatus;

public:
    DeliveryPartner(int id, string partnerName)
        : partnerId(id),
          name(partnerName),
          currentLocation("Restaurant"),
          deliveryStatus("Order picked up") {}

    void updateLocation(const string& newLocation) {
        currentLocation = newLocation;
    }

    void updateDeliveryStatus(const string& newStatus) {
        deliveryStatus = newStatus;
    }

    int getPartnerId() const {
        return partnerId;
    }

    string getName() const {
        return name;
    }

    string getLocation() const {
        return currentLocation;
    }

    string getDeliveryStatus() const {
        return deliveryStatus;
    }
};

// ==========================================
// 5. DELIVERY TRACKING
// ==========================================

class DeliveryTracking {
public:
    void track(const DeliveryPartner& partner) const {
        cout << "\n--- Live Delivery Tracking ---\n";
        cout << "Partner ID: " << partner.getPartnerId() << '\n';
        cout << "Partner Name: " << partner.getName() << '\n';
        cout << "Current Location: "
             << partner.getLocation() << '\n';
        cout << "Delivery Status: "
             << partner.getDeliveryStatus() << '\n';
    }
};

// ==========================================
// 6. CUSTOMER
// ==========================================

class Customer {
private:
    int customerId;
    string name;

public:
    Customer(int id, string customerName)
        : customerId(id), name(customerName) {}

    void trackDelivery(
        const DeliveryTracking& tracker,
        const DeliveryPartner& partner
    ) const {
        cout << "\nCustomer " << name
             << " is tracking the delivery.\n";

        tracker.track(partner);
    }
};

// ==========================================
// 7. MAIN FUNCTION
// ==========================================

int main() {
    cout << "===== FOOD DELIVERY SYSTEM =====\n";

    // Create customer and order
    Customer customer(1, "Rahul");
    Order order(101, 850.00);

    // Select payment method
    order.checkout(make_unique<UpiPayment>());

    // Create delivery partner
    DeliveryPartner partner(501, "Amit");

    // Create tracking service
    DeliveryTracking tracker;

    // Customer checks the delivery location
    customer.trackDelivery(tracker, partner);

    // Delivery partner moves to another location
    partner.updateLocation("Sector 17, Chandigarh");
    partner.updateDeliveryStatus("On the way");

    // Customer checks the updated location
    customer.trackDelivery(tracker, partner);

    // Delivery partner reaches the customer
    partner.updateLocation("Customer's address");
    partner.updateDeliveryStatus("Delivered");

    // Customer checks the final status
    customer.trackDelivery(tracker, partner);

    // Display order information
    order.showDetails();

    return 0;
}
