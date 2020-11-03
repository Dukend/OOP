#include <cstdint>
#include <iostream>
#include <string>
#include <typeinfo>

// сам шаблон (рассмотрели в примере basic_tuple)
template <class... Ts> class tuple {
};

template <class T, class... Ts>
class tuple<T, Ts...> : public tuple<Ts...> {
    public:
    tuple(T t, Ts... ts) : tuple<Ts...>(ts...), value(t) {
    }
    tuple<Ts...> &next = static_cast<tuple<Ts...>&>(*this);
    T value;
};


// специальная структура которая отсекает size_t первых типов в tuple и возвращает tuple от оставшегося хвоста
template <size_t index, class... Ts> struct elem_type_holder;

// специализация для первого параметра равного 0 - это тип базового класса
template <class T, class... Ts> struct elem_type_holder<0, T, Ts...> {//tuple<T, Ts...>
  using type =  T;
};

// рекурсивно задаем шаблон
template <size_t k, class T, class... Ts>  struct elem_type_holder<k, T, Ts...> {//tuple<T, Ts...>
  using type = typename elem_type_holder<k - 1, Ts...>::type;
};

// шаблон функции get для получения параметра (данная специализация работает только при index==0)
template <size_t index,class ...Ts>
typename std::enable_if<index == 0, typename elem_type_holder<0, Ts...>::type&>::type get(tuple<Ts...>& t){
    return t.value;
}

// шаблон функции get для получения параметра (данная специализация работает только при index!=0)
template <size_t index,class T,class ...Ts>
typename std::enable_if<index != 0, typename elem_type_holder<index, T,Ts...>::type&>::type get(tuple<T,Ts...>& t){
    tuple<Ts...> &base = t;
    return get<index-1>(base);
}

//*
// C++17
template<size_t index,class T,class ...Ts>
auto get_c(tuple<T,Ts...>& t){
    if constexpr (index ==0) return t.value;
     else {
         tuple<Ts...> &base = t;
         return get_c<index-1>(base);
     }
}
//*/

int main(int argc, char** argv) {
    tuple<double, uint64_t, const char*> t1(100.1, 1828, "some string");
    std::cout << t1.value << std::endl;
    std::cout << t1.next.value << std::endl;
    std::cout << t1.next.next.value << std::endl;

    std::cout << "0th elem is " << get<0>(t1) << ","<< typeid(decltype(get<0>(t1))).name()<< std::endl;
    std::cout << "1th elem is " << get<1>(t1) << ","<< typeid(decltype(get<1>(t1))).name()<<std::endl;
    std::cout << "2th elem is " << get<2>(t1) << ","<< typeid(decltype(get<2>(t1))).name()<<std::endl;

   std::cout << "error:" << get_c<2>(t1) << std::endl;
   
    return 0;
}
