#include<iostream>
using namespace std;

class Room{
    public:
    void showroom()
    {
        cout<<"This is showroom"<<endl;
    }
};
class House{
    private:
    Room r1;
    Room r2;

    public:
    void showhouseroom()
    {
        r1.showroom();
        r2.showroom();
    }
};

int main()
{
    House h1;
    h1.showhouseroom();

    return 0;

}