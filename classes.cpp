#include <iostream>

class Person
{
public:
    Person(const char* name, int age)
    {
        this->name = name;
        this->age = age;
    }

    void print()
    {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }

    void changeName(const char* name)
    {
        this->name = name;
    }

private:
    const char* name;
    int age;
};


int main()
{
    Person p("Ensar", 20);
    p.print();
    p.changeName("Mehmet");
    p.print();
    return 0;
}