#include <iostream>
#include <string>

class Animal{
    public:
        virtual size_t get_size() =0;
        virtual ~Animal(){
            std::cout << " Animal destructor" << std::endl;
        }
};

class Moose : public Animal{
    public:
        size_t get_size() override{
            return 1000;
        }
        ~Moose(){
            std::cout << " Moose destructor" << std::endl;
        }
};

class Dog : public Animal{
    public:
        size_t get_size() override{
            return 50;
        }
        ~Dog(){
            std::cout << " Dog destructor" << std::endl;
        }
};

int main()
{

    //Simple Example
    Animal *ptr_dog = new Dog();
    Animal *ptr_moose = new Moose();

    std::cout << "Dog size:" << ptr_dog->get_size() << std::endl;
    std::cout << "Moose size:" << ptr_moose->get_size() << std::endl;

    delete ptr_moose;
    delete ptr_dog;

    //With array

    std::cout << std::endl << "Array:" << std::endl;
    Animal* animals[] {new Dog(),new Moose(),new Dog(),new Moose()};
    for(auto ptr: animals)
        std::cout << " Size:" << ptr->get_size() << std::endl;
 
    std::cout << std::endl << "Destructors:" << std::endl;
    for(auto ptr:animals) delete ptr;

    return 1;
}