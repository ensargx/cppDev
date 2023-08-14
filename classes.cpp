#include <iostream>

class Person
{
public:
    Person(const char* name, int age)
    {
        this->name = name;
        this->age = age;
    }

    ~Person()
    {
        std::cout << "Destructor called for " << name << std::endl;
    }

    void print()
    {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }

    void changeName(const char* name)
    {
        this->name = name;
    }

    operator int()
    {
        return age;
    }

    int operator + (const Person& other)
    {
        return age + other.age;
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

    {
        Person p2("Ali", 30);
        p2.print();
    }
    // destructor is called for p2
    //  p2.print(); // Error: p2 is not defined in this scope

    // Create a new scope and create a new Person object in heap
    // and access it out of the scope
    Person* p3 = nullptr;
    {
        p3 = new Person("Veli", 40);
        p3->print();
    }
    // destructor is not called for p3

    p3->print();

    std::cout << "Age of p3: " << (int)*p3 << std::endl;

    /*
    Person person3 = *p3;
    person3.print();
    
    std::cout << "Age of person3: " << (int)person3 << std::endl;
    std::cout << "Age of p3: " << int(person3) << std::endl;
    */

    delete p3; // destructor is called for p3

    Person p4("Ayse", 50);
    std::cout << "Age of p4: " << (int)p4 << std::endl;

    std::cout << "Sum of ages: " << p + p4 << std::endl;

    return 0;
}