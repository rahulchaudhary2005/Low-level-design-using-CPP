
#include <iostream>
#include <memory>
using namespace std;

// Step 1: Common interface
class TravelStrategy {
public:
    virtual void travel() = 0;
    virtual ~TravelStrategy() = default;
};

// Step 2: Different strategies
class BusStrategy : public TravelStrategy {
public:
    void travel() override {
        cout << "Travelling by bus\n";
    }
};

class CarStrategy : public TravelStrategy {
public:
    void travel() override {
        cout << "Travelling by car\n";
    }
};

class BicycleStrategy : public TravelStrategy {
public:
    void travel() override {
        cout << "Travelling by bicycle\n";
    }
};
class BicycleStrategy : public TravelStrategy {
public:
    void travel() override {
        cout << "Travelling by bicycle\n";
    }
};

class TrainStrategy : public TravelStrategy {
public:
    void travel() override {
        cout << "Travelling by train\n";
    }
};
// Step 3: Class that uses a strategy and decide weather which travelling method we have to use in  the college
class Travel {
private:
    unique_ptr<TravelStrategy> strategy;

public:
    Travel(unique_ptr<TravelStrategy> s)
        : strategy(move(s)) {}

    void goToCollege() {
        strategy->travel();
    }
};

int main() {
    Travel byBus(make_unique<BusStrategy>());
    byBus.goToCollege();

    Travel byCar(make_unique<CarStrategy>());
    byCar.goToCollege();

    Travel byBicycle(make_unique<BicycleStrategy>());
    byBicycle.goToCollege(); 

    Travel byBusAgain(make_unique<BusStrategy>());
    byBusAgain.goToCollege();

    Travel byTrain(make_unique<TrainStrategy>());
    byTrain.goToCollege();

    return 0;
}
