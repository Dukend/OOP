#include <iostream>
#include <string>

class Animal
{
protected:
    std::string name;
public:
    Animal(const char *val) : name(val){};
    const char *get_name() { return name.c_str(); }
};

class Moose : public Animal
{
public:
    Moose() : Animal("Moose"){};
    void run()
    {
        std::cout << name << " running" << std::endl;
    }
};

class Dog : public Animal
{
public:
    Dog() : Animal("Dog"){};
    void bark()
    {
        std::cout << "woof woof!" << std::endl;
    }
};

int main(int argc, char *argv[])
{

    // Stack Moos
    Moose m;
    std::cout << m.get_name() << std::endl;
    m.run();

    // Stack Dog
    Dog d;
    std::cout << d.get_name() << std::endl;
    d.bark();

    std::cout << std::endl
              << "Heap objects" << std::endl;

    // Heap Moose
    Moose *ptr_moose = new Moose();
    std::cout << ptr_moose->get_name() << std::endl;
    ptr_moose->run();

    // Moose is a Animal
    Animal *ptr_animal = (Animal*)ptr_moose;
    std::cout << ptr_animal->get_name() << std::endl;
    
    delete ptr_moose;

    return 1;
}