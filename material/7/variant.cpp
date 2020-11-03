#include <variant>
#include <iostream>

class Circle {
protected:
    const double R;
public:
    Circle(double r) : R(r) {};
    double Square() {
        return 3.14 * R * R;
    };
    virtual ~Circle() {};
};

class Sphere {
protected:
    const double R;
public:
    Sphere(double r) : R(r) {};

    double Volume() {
       return 3.14 * R*R * R*4/3;
    };

    virtual ~Sphere() {};
};

struct FigureVisitor{
    void operator() ( Circle& value) const{
        std::cout << "square:" << value.Square() << std::endl;
    }
    void operator() ( Sphere& value) const{
        std::cout << "volume:" << value.Volume() << std::endl;
    }

};

int main(){
    std::variant<Circle, Sphere> array[]={Circle(1),Sphere(1),Circle(2)};

    for(auto& a:array){
        switch(a.index()){
            case 0: std::cout << "square:" << std::get<Circle>(a).Square() << std::endl;break;
            case 1: std::cout << "volume:" << std::get<Sphere>(a).Volume() << std::endl;break;
        }
    }

    for(auto& a:array) std::visit(FigureVisitor(),a);
    return 1;
}