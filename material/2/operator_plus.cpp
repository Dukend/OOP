#include <cstdlib>
#include <iostream>

#define UNUSED(value) (void)value

class Rectangle {
private:
    int _width,_height;
    friend Rectangle operator+(const Rectangle& lhv,const Rectangle& rhv);
    friend std::ostream &operator<<(std::ostream &os,const Rectangle& rec);
public:
    Rectangle(int w,int h) : _width (w),_height(h) {}   
    virtual ~Rectangle(){}
};

std::ostream &operator<<(std::ostream &os,const Rectangle& rec){
    os << "{" << std::endl << "\twidth: " << rec._width << std::endl << "\theight: " << rec._height << "}" << std::endl;
    return os;
}

Rectangle operator+(const Rectangle& lhv,const Rectangle& rhv){
    return Rectangle(lhv._width+rhv._width,lhv._height+rhv._height);
}

int main(int argc, char** argv) {
    Rectangle rec1(10,1);
    Rectangle rec2(1,10);

    std::cout << "rec1 " << rec1;
    std::cout << "rec2 " << rec1;
    std::cout << "sum " << (rec1+rec2);

    
    UNUSED(argc);
    UNUSED(argv);
    return 0;
}