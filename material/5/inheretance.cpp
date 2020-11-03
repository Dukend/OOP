#include <iostream>
#include <typeinfo>

// метафункция возвращающая тип
template <typename T>
struct type_is{
    using type = T;
};

// метафункция, возвращающая тип Т если C==true и тип F в противном случае
template <bool C, class T, class F>
struct conditional : type_is<T>{
};

// специализация для случая C==false
template <class T, class F>
struct conditional<false, T, F> : type_is<F>{
};

// специализация для случая C==true
template <class T, class F>
struct conditional<true, T, F> : type_is<T>{
};


int main(){

    conditional<true,int,double>::type value1{};
    conditional<false,int,double>::type value2{};

    std::cout << typeid(decltype(value1)).name() << std::endl;
    std::cout << typeid(decltype(value2)).name() << std::endl;

    return 1;
}