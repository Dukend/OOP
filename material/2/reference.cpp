#include <cstdlib>
#include <iostream>

void swap(int &a, int &b)
{
    a = a+b;
    b = a-b;
    a = a-b;
}

struct A {
    A(){std::cout << "Created" << std::endl;}
    A(int a) : value(a){ std::cout << "Created with value" << std::endl;}  
    A(const A &a) :A() { value= a.value;std::cout << "Вот оно что!" << std::endl;}
    int value;

};

void over(A &a) {    std::cout << "LValue:" << a.value << std::endl;}
void over(A &&a) {   std::cout << "RValue:" << a.value << std::endl;}
void cross(A a) {   std::cout << "Copy:" << a.value << std::endl;}

int main(int argc, char** argv) {
   /* int a1=10,b1=20;
    swap(a1,b1);

    std::cout << "a1=" << a1 << " ,b1=" << b1 << std::endl;
*/

    A a(5);
    over(a);
    over(A(7));
    cross(a);
    cross(A(10)); // Внезапно!

    return 0;
}