#include <iostream>

class MyBool
{
public:
    char values = 0b00000000;

    // a[i] returns the i-th bit of a
    bool operator[] (int index)
    {
        if (index < 0 || index > 7)
        {
            std::cout << "Index out of range" << std::endl;
            throw "Index out of range";
        }
        return (values >> index) & 1;
    } 


};

int main()
{
    MyBool a;
    
    for(int i = 0; i < 8; i++)
    {
        std::cout << a[i] << std::endl;
    }

    return 0;
}