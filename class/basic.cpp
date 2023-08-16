#include <iostream>

class Person
{
public:
    const int x;
    const char* name;

    Person()
        : name("Unknown"), x(10), yas(0)
    {
        std::cout << "Default constructor for Person\n";
    }

    Person(int yas)
        : name("Unknown"), x(20), yas(yas)
    {
        std::cout << "Constructor for Person with yas: " << yas << "\n";
    }

    Person(const char* n_name, int n_yas)
        : name(n_name), x(30), yas(n_yas)
    {
        std::cout << "Constructor for Person with name: " << name << " and yas: " << yas << "\n";
    }

    void print()
    {
        std::cout << "Name: " << name  << ", x: " << x  << ", yas: " << yas << "\n";
    }

    void changeX(int newX)
    {
        *(int*)&x = newX;
    }

    ~Person()
    {
        std::cout << "Destructor for Person\n";
    }

private:
    const int yas;
};

int main()
{
    Person person;
    person.print();

    std::cout << "---------------------" << "\n";

    Person person20(20);
    person20.print();
    // person20.x = 30;    // Error: x is const
    person20.changeX(30);  // No error, x is 30
    std::cout << "person20.x: " << person20.x << "\n";

    std::cout << "---------------------" << "\n";

    Person personA("Ali", 25);
    personA.name = "Veli"; // Ne kadar mantıklı?, name const olmalı
    // personA.yas = 30;   // Error: yas is private
    personA.print();

    std::cout << "---------------------" << "\n";

    return 0;
}