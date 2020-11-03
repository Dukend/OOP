#include <string>
#include <iostream>
#include <type_traits>

template <class T>
std::string my_to_string(T x)
{
    if constexpr (std::is_same<T, std::string>::value)
    {
        return x;
        // ERROR, if no conversion to string
    }
    else if constexpr (std::is_integral<T>::value)
    {
        return std::to_string(x); // ERROR, if x is not numeric
    }
    else
    {
        return std::string(x);
        // ERROR, if no conversion to string
    }
}

int main(){

    std::string str = my_to_string(1);
    str += my_to_string(std::string("2"));
    str += my_to_string("3");

    std::cout << str <<std::endl;

    return 1;
}