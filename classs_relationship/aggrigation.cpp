
#include <iostream>
#include <string>
using namespace std;

class Teacher {
public:
    string name;

    Teacher(string n) {
        name = n;
    }

    void teach() {
        cout << name << " is teaching" << endl;
    }
};

class Department {
private:
    Teacher* teacher; // Non-owning pointer

public:
    Department(Teacher* t) {
        teacher = t;
    }

    void conductClass() {
        teacher->teach();
    }
};

int main() {
    Teacher t1("Rahul");
    Department d1(&t1);

    d1.conductClass();
}
