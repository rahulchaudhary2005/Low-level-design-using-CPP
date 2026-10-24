#include <iostream>
using namespace std;

class Logger {
private:
    Logger() {}

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(string message) {
        cout << "Log: " << message << '\n';
    }
};

int main() {
    Logger::getInstance().log("Order created");
    Logger::getInstance().log("Payment completed");

    return 0;
}