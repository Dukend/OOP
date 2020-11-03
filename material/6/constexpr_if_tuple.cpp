#include <tuple>
#include <type_traits>
#include <iostream>

template <class T,size_t index=0>
void print_tuple(T value){
    if constexpr(index < std::tuple_size<T>::value){
        std::cout << std::get<index>(value) << " ";
        print_tuple<T,index+1>(value);
    } else {
        std::cout << std::endl;
    }
}

int main(){
    std::tuple t= std::make_tuple(1,2,"hello world",0.001);
    print_tuple(t);
    return 1;
}