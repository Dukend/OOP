#include <iostream>
#include <functional>

template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts)
{
    if constexpr (sizeof...(ts) > 0) {
        return [=](auto ...parameters) {
          return t(concat(ts...)(parameters...)); };
    } else  {
        return t;
    }
}

int plus(int a,int b){
    std::cout << " sum>";
    return a+b;
};

int main()
{
    auto twice  = [] (int i) { std::cout << " twice>" << i << ' ';return i * 2; };
    auto thrice = [] (int i) { std::cout << " thrice>" << i << ' '; return i * 3; };

    auto combined = concat(twice, thrice, plus);

    std::cout << combined(2, 3) << std::endl;
    // twice(thrice(plus(2,3)))
}
