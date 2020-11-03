#include <cstdlib>
#include <iostream>
#include <string>

#define UNUSED(variable) (void)variable

class Life
{
public:
    Life() { std::cout << "I'm alive" << std::endl; }
    Life(const char *n) : Life()
    {
        name = n;
        std::cout << "My name is " << name << std::endl;
    };
    ~Life() { std::cout << "Oh no! I'm dead:" << name << std::endl; }

private:
    std::string name;
};

int main(int argc, char **argv)
{

    Life a;


    {
        Life c("Nikodim");
    }
    
    Life b("Oleg");

    Life *d_ptr;

    d_ptr = new Life("Agafon");
    delete d_ptr;

    UNUSED(argc);
    UNUSED(argv);
    
    return 0;
}
