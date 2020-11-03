#include <cstdlib>
#include <iostream>

#define UNUSED(value) (void)value

class Rectangle {
private:
    int _width,_height;
public:
    Rectangle(int w,int h) : _width (w),_height(h) {}

    int&      operator[](int i){
        switch (i) {
            case 0: return _width;
            case 1: return _height;
            default:
                std::exit(-1);
                break;
            }
    }

    Rectangle operator++(){
        ++_width;
        ++_height;
        return *this;
    }

    Rectangle operator++(int){
        Rectangle result = *this;
        _width++;
        _height++;
        return result;
    }

    operator int(){
        return _width*_height;
    }

    virtual ~Rectangle(){}


};

int main(int argc, char** argv) {
    Rectangle rec(10,2);
    
   
    (++(++(((rec++)++)++))++);

    std::cout << "Width=" << rec[0] << " Height=" << rec[1] << std::endl;
    std::cout << "Square=" << rec << std::endl;
   // ++rec;
    std::cout << "Square=" << (rec++) << "," << rec <<std::endl;
    std::cout << "Width=" << rec[0] << " Height=" << rec[1] << std::endl;

    
    
    
    UNUSED(argc);
    UNUSED(argv);
    return 0;
}
