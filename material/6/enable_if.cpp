#include <iostream>
#include <string>

/**
 * Шаблон который позволяет подставлять тип в зависимости от того, истино условие или нет
 */
template <bool condition,class T>
struct enable_if{
};

template <class T>
struct enable_if<true,T>{
    using value = T; // value only in specialization
};

/**
 * Какой-то шаблонный контейнер
 */
template <class T>
struct Container{
    using type = T;
    T payload;
    Container(const T& value) : payload(value) {};
};

/**
 * Шаблон, который возвращает истинное значение value, если контейнер хранит значение const char*
 */
template <class T>
struct is_str_type{
    static const bool value = false;
};

template <>
struct is_str_type<const char*>{
    static const bool value = true;
};

/**
 * Шаблон, котрый складывает два контейнера.
 * "По умолчанию" - производится сложение
 */
template <class T>
typename enable_if<!is_str_type<typename T::type>::value,T>::value
add(const T& lhv, const T& rhv){
    return T(lhv.payload+rhv.payload);
};

/**
 * Шаблон, котрый складывает два контейнера.
 * Для типа const char* - производится конкатенация
 */
template <class T>
typename enable_if<is_str_type<typename T::type>::value,T>::value add(const T& lhv, const T& rhv){
    std::string *tmp = new std::string(lhv.payload);
    *tmp+=rhv.payload;
    return T(tmp->c_str()); // memory leak, but for example - ok
};

int main(){

    typename enable_if<true,int>::value a=10; // typename optional, but sometimes needed
    std::cout << a << std::endl;
    
    //enable_if<false,int>::value b=10;

    Container<int> c1(10),c2(20);

    std::cout << "Is str type:" << is_str_type<decltype(c1)::type>::value << std::endl;

    std::cout << add(c1,c2).payload << std::endl;

    Container<const char*> d1("10"),d2("20");

    std::cout << "Is str type:" << is_str_type<decltype(d1)::type>::value << std::endl;

    std::cout << add(d1,d2).payload << std::endl;


    return 1;
}