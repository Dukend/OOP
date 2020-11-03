#include <cstdlib>
#include <iostream>
#include <string>

class Rectangle
{
public:
    unsigned long width, height;
    Rectangle(int w, int h) : width(w), height(h){};
};

Rectangle operator"" _rect(unsigned long long w)
{
    return Rectangle(w, w);
}

class Massa
{
public:
    std::string number;
    Massa(const char *str) : number(str) { number += "kg"; };
};
Massa operator"" _kg(const char *str)
{
    return Massa(str);
}

std::string operator""_zzz(const char *str, size_t)
{
    return std::string(str);
}

unsigned int operator""_binary(const char *str)
{
    unsigned int result{};
    for (int i = 0;i <strlen(str) ; ++i)
    {
        result = result * 2 + str[i] - '0';
    }
    return result;
}

int main(int argc, char **argv)
{
    Rectangle a = 12_rect;
    Massa b = 123_kg;

    std::cout << "Width=" << (10_rect).width << std::endl;
    std::cout << (3_kg).number << std::endl;
    std::cout << "12,13"_zzz << std::endl;
    std::cout << (11111111_binary - 10000000_binary) << std::endl;
    return 0;
}
