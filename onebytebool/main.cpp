#include <iostream>

class MyBool
{
public:
    char values = 0b00000000;

    class Proxy
    {
    public:
        MyBool& myBool;
        int index;

        Proxy(MyBool& mb, int idx)
            : myBool(mb), index(idx)
        {
        }

        // Use of myBool[i] will return the value of the bit at index i
        // Use of myBool[i] = true will set the bit at index i to true
        operator bool() const
        {
            return (myBool.values >> index) & 1;
        }

        Proxy& operator=(bool value)
        {
            if(value)
            {
                myBool.values |= (1 << index);
            }
            else
            {
                myBool.values &= ~(1 << index);
            }

            return *this;
        }
        
    };

    // Use of myBool[i] will return the value of the bit at index i
    // Use of myBool[i] = true will set the bit at index i to true
    const bool operator[](int index) const
    {
        return (values >> index) & 1;
    }

    Proxy operator[](int index)
    {
        return Proxy(*this, index);
    }

};

int main()
{
    MyBool a;
    
    a[6] = true;

    a[1] = true;

    for(int i = 0; i < 8; i++)
    {
        std::cout << a[i] << std::endl;
    }

    // Print the size of MyBool and a
    std::cout << "Size of MyBool: " << sizeof(MyBool) << std::endl;               // Should be "1"
    std::cout << "Size of a: " << sizeof(a) << std::endl;                         // Should be "1"

    // Print the size of MyBool::Proxy
    std::cout << "Size of MyBool::Proxy: " << sizeof(MyBool::Proxy) << std::endl; // Should be "16"

    // Print the type of a, a[i], and MyBool::Proxy
    std::cout << "Type of a: " << typeid(a).name() << std::endl;                  // returns "6MyBool"
    std::cout << "Type of a[i]: " << typeid(a[0]).name() << std::endl;            // returns "N6MyBool5ProxyE"

    return 0;
}