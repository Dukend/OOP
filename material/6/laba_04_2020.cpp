#include <iostream>
#include <string>
#include <utility>

/*
Разработать шаблоны классов согласно варианту задания.  
Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат. 
Классы должны иметь только публичные поля. В классах не должно быть методов, только поля. Ф
игуры являются фигурами вращения (равнобедренными), за исключением трапеции и прямоугольника. 
Для хранения координат фигур необходимо использовать шаблон  std::pair.
Например:
template <class T>
struct Square{
    using vertex_t = std::pair<T,T>;
    vertex_t a,b,c,d;
};


Необходимо реализовать две шаблонных функции:
1.	Функция print печати фигур на экран std::cout  (печататься должны координаты вершин фигур). 
    Функция должна принимать на вход std::tuple с фигурами, согласно варианту задания (минимум по одной каждого класса).
2.	Функция square вычисления суммарной площади фигур.
    Функция должна принимать на вход std::tuple с фигурами, согласно варианту задания (минимум по одной каждого класса).

Создать программу, которая позволяет:
•	Создает набор фигур согласно варианту задания (как минимум по одной фигуре каждого типа с координатами типа int и координатоми типа double).
•	Сохраняет фигуры в std::tuple
•	Печатает на экран содержимое std::tuple с помощью шаблонной функции print.
•	Вычисляет суммарную площадь фигур в std::tuple и выводит значение на экран.

При реализации шаблонных функций допускается использование вспомогательных шаблонов std::enable_if, std::tuple_size, std::is_same.
	
*/
// примеры классов фигур
template <class T, size_t SIZE> struct Path {
    using type = T;
    std::pair<T,T> array[SIZE];
    std::pair<T,T>* begin(){
        return &array[0];
    }
    std::pair<T,T>* end(){
        return &array[SIZE];
    }

    T get_square(){
        return 0;
    }
};

template <class T> struct Circle {
    using type = T;
    std::pair<T,T> center;
    T radius;
};


// печать на экран tuple
template <class T,size_t index> typename std::enable_if<index>=std::tuple_size<T>::value,void>::type print_tuple(T&){
    std::cout << std::endl;
}

template <class T,size_t index> typename std::enable_if<index<std::tuple_size<T>::value,void>::type print_tuple(T& tuple){
    auto figure = std::get<index>(tuple);
    print(figure);
    print_tuple<T,index+1>(tuple);
}

// печать на экран Path
template <class T> typename std::enable_if<(sizeof(T::array)>0),void>::type  print(T& path){
    for(auto vertex : path)
        std::cout << "(" << vertex.first << "," << vertex.second << ") ";
    std::cout << std::endl;
}
// печать на экран Circle
template <class T> typename std::enable_if<(sizeof(T::radius)>0),void>::type  print(T& path){
    std::cout << "Circle with center in (" << path.center.first << "," << path.center.second << ") and radius=" << path.radius;
    std::cout << std::endl;
}

// вычисление площади Circle
template <class T> typename std::enable_if<(sizeof(T::radius)>0),typename T::type>::type  square(T& path){
    return static_cast<typename T::type>(path.radius*path.radius*3.14159);
}

// вычисление площади Path
template <class T> typename std::enable_if<(sizeof(T::array)>0),typename T::type>::type  square(T& ){
    return static_cast<typename T::type>(0);
}

// считаем площадь tuple c использованием if constexpr

template <class T,size_t index>  double square_tuple(T& tuple){
    auto item = std::get<index>(tuple);
    double value = square(item);
    
    if constexpr ((index+1) < std::tuple_size<T>::value) {
        return value + square_tuple<T,index+1>(tuple);
    }

    return value;
}

auto main() -> int
{
    Path<int,5> p1;
    p1.array[0] = {0,0};
    p1.array[1] = {1,2};
    p1.array[2] = {2,4};
    p1.array[3] = {3,6};
    p1.array[4] = {4,8};
    

    Circle<int> circle1;
    circle1.center = {10,10};
    circle1.radius = 100;

    Circle<double> circle2;
    circle2.center = {20,20};
    circle2.radius = 10;




    std::tuple <decltype(p1),decltype(circle1),decltype(circle2)> tuple {p1,circle1,circle2};
    print_tuple<decltype(tuple),0>(tuple);

    std::cout << "square: " << square_tuple<decltype(tuple),0>(tuple) << std::endl;
    return 1;
}