#include <iostream>

int counter(){
    static int i=0;
    return ++i;
}

struct A{
    static int value;
};

int A::value = 100;

int main(){

    for(int i=0;i<5;++i) std::cout << counter() << std::endl;

    std::cout << A::value << std::endl;

    A a;
    a.value++;

    A b;
    std::cout << b.value << std::endl;

    return 0;
}