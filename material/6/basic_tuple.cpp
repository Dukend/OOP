#include <cstdint>
#include <iostream>
#include <string>
#include <typeinfo>

// базовый шаблон, он сработает только для пустой коллекции типов
template <class... Ts> class tuple {
};

// сохраняем значения в tuple через иерархию наследования

template <class T, class... Ts>
class tuple<T, Ts...> : public tuple<Ts...> { // тип T который сохраняем в текущем классе, хвост рекурсии - родители класса
    public:
    // инициализируем родителей через вызов конструктора родителя и сохраняем значение в value
    tuple(T v, Ts... vs) : tuple<Ts...>(vs...), value(v) { 
    }
    // делаем ссылку на родителя, чтобы можно было достать значение без приведения типов
    tuple<Ts...> &next = static_cast<tuple<Ts...>&>(*this);
    T value;

    void print(){
        std::cout << value << std::endl;
    }
};

int main(int argc, char** argv) {

    tuple<double, double, uint64_t, const char*> t1(12.2,2.3, 42, "big");

    t1.print();
    t1.next.print();

    std::cout << t1.value << std::endl;
    std::cout << t1.next.value << std::endl;
    std::cout << t1.next.next.value << std::endl;
    
    return 0;
}
