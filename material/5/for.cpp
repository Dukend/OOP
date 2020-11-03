#include <array>
#include <iostream>
#include <vector>


int main() {
    int a[10];


    
    for(const auto& i : a)
    {
        std::cout << i << std::endl;
    }

    std::string s{"hello"};
    for(auto c: s)
    {
        std::cout << c << std::endl;
    }

    return 0;
}

