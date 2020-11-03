#include <cstdlib>
#include <iostream>

class B;

class A {
    friend class B;
private:
    int value;
public:
    
    A(int v) : value(v) {};
};

class B {
public:

    B(A a[], int size) {
        int total = 0;
        for (int i = 0; i < size; i++) total += a[i].value;
        std::cout << "Total:" << total << std::endl;

    }
};

int main() {
    A array[3] = {A(1), A(2), A(3)};
    //array[0].value = 100;
    B sum(array, 3);
    return 0;
}

