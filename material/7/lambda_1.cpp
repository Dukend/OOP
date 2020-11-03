#include <vector>
#include <iostream>

class MyLambda
{
public:
    void operator()(int i) const
    {
        std::cout << i << " ";
    }
};

int main(int argc, char *argv[])
{
    std::vector<int> elements;

    for (int i = 0; i < 10; i++)
        elements.push_back(i);

    // lambda
    auto lambda = [](auto i) {
        std::cout << i << " ";
        return 10;
    };


    std::cout << "sizeof lambda:" << sizeof(lambda) << std::endl;
    int a = lambda(7);
    for (int i : elements)
        [](int a) { std::cout << a << " "; }(i);
    std::cout << std::endl;

    // without lambda
    MyLambda functor;
    std::cout << "sizeof functor:" << sizeof(functor) << std::endl;
    for (int i : elements)
        functor(i);
    std::cout << std::endl;

    return 0;
}