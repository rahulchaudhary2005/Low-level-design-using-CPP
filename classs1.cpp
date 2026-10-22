
#include <iostream>
#include <string>
using namespace std;

class Car {
private:
    string owner;
    long long price;

public:
    // Public setter
    void setowner(string name) {
        this->owner = name;
    }

    // Public getter
    void getowner() {
        cout << "The name of the owner is " << owner << endl;
    }

    string brand;
    string model;
    int cc;

    void start() {
        cout << "Car is starting" << endl;
    }

    void accelerate(int speed) {
        speed += 10;
        cout << "Car is accelerating to "
             << speed << " mph" << endl;
    }
};

int main() {
    Car c1;
    c1.brand = "BMW";
    c1.model = "2025";
    c1.start();
    c1.accelerate(120);
    cout<<c1.brand<<endl;
    cout<<"<-------->"<<endl;
    

    Car c2;
    c2.brand = "BMW";
    c2.model = "2025";
    c2.start();
    c2.accelerate(120);

    c2.setowner("rahul chaudhary");
    c2.getowner();

    return 0;
}
