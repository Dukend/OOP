#include <iostream>
#include <string>

#define UNUSED(value) (void)value

/*
struct Animal
{
    void jump()
    {
        std::cout << "i can jump like an animal!" << std::endl;
    }
};
//*/

struct Duck //: public Animal
{
    void swim()
    {
        std::cout << "i can swim like a duck!" << std::endl;
    }
};

struct Desman //: public Animal
{
    void cute()
    {
        std::cout << "i am cute like a desman!" << std::endl;
    }
};

struct Platypus : public Duck, Desman
{
};

int main(int argc, char *argv[])
{
    Platypus animal;

    animal.cute();
    animal.swim();
//    animal.jump();

    UNUSED(argc);
    UNUSED(argv);
    return 1;
}