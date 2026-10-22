
#include <iostream>
using namespace std;

class DeliveryPartner {
public:
    void deliverOrder() {
        cout << "Order delivered!" << endl;
    }
};

class Customer {
public:
    void receiveOrder(DeliveryPartner& partner) {
        partner.deliverOrder();
    }
};

int main() {
    Customer customer;
    DeliveryPartner partner;

    customer.receiveOrder(partner);
}
