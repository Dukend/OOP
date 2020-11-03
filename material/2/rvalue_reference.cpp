#include <cstdlib>
#include <iostream>

#define UNUSED(value) (void)value

class Tracer
{
public:
    Tracer() { std::cout << "default constructor" << std::endl;}
    Tracer(const char* val) {
        std::cout << "constructor:" << val << std::endl;
        name=val; 
        }
    Tracer(const Tracer& other) { 
        std::cout << "copy constructor:" << other.name << std::endl;
        name=other.name; 
        }

    Tracer(Tracer&& other) { 
        std::cout << "move constructor:" << other.name << std::endl;
        name=other.name; 
        other.name = {};
        }

    Tracer& operator=(const Tracer& other){
        std::cout << "copy:" << other.name << std::endl;
        name = other.name;
        return *this;
    }
    
    Tracer& operator=(Tracer&& other) noexcept{
        std::cout << "move:" << other.name << std::endl;
        name = other.name;
        other.name = {};
        return *this;
    }

    ~Tracer() {
        std::cout << "destructor" << std::endl;;
    }
private:
    std::string name;
};

void foo(Tracer &&other){
    Tracer A(std::move(other));
}

int main() {
    Tracer trace{"my tracer"};
    std::cout << "copy:" << std::endl;
    Tracer other{trace};
    other = trace;

    std::cout << std::endl << "move:" << std::endl;
    //Tracer other2{Tracer{"my tracer 2"}};
    //other2 = std::move(other);
    foo(Tracer{"my tracer 2"});


    return 0;
}

