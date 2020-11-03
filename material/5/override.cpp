#include <iostream>

void foo(){
    std::cout << "foo()" << std::endl;
}

void foo(int a){
    std::cout << "foo(int)" << std::endl;
}

void foo(double a){
    std::cout << "foo(double)" << std::endl;
}

int main(void){
    foo();
    foo(1);
    foo(2.0);
}