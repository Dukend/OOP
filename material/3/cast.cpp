#include <iostream>
#include <string>

#define UNUSED(value) (void)value

struct A{
    virtual void foo_a() {};
};

struct C : A{
    virtual void foo_c() {};
};

struct D : A{
    virtual void foo_d() {};
};

int main(int argc, char *argv[])
{
    // static_cast

    C* c = new C{};
    A* a = static_cast<A*>(c);
    if(a) {
        std::cout << "+ Static cast form C->A successful" << std::endl;
        D* d= static_cast<D*>(a);
        if(d) std::cout << "+ Static cast form C->A->D successful" << std::endl;
    }
    delete c;

    // dynamic_cast

    a = dynamic_cast<A*>(c);
    if(a) {
        std::cout << "+ Dynamic cast form C->A successful" << std::endl;
        D* d= dynamic_cast<D*>(a);
        if(d) std::cout << "+ Dynamic cast form C->A->D successful" << std::endl;
          else std::cout << "- Dynamic cast form C->A->D unsuccessful" << std::endl;
    }

    UNUSED(argc);
    UNUSED(argv);
    return 1;
}