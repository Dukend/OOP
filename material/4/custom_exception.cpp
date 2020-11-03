#include <cmath>
#include <iostream>
#include <exception>
#include <string>

struct WrongArgumentException : public std::exception {
    int a,b,c;
    WrongArgumentException(int aa,int bb, int cc): a(aa),b(bb),c(cc){
    
    }

    void foo(){
        
    }
    const char* what() const noexcept override{
       // throw int(1);
        std::string str("Wrong argument exception a=");
        str+=std::to_string(a);
        return str.c_str();
    }
};

class SquareEquation {
private:
    double a;
	double b;
	double c;
public:
	SquareEquation(double aa,double bb,double cc): a(aa),b(bb),c(cc){
         if((b*b-4*a*c)<0) throw WrongArgumentException(a,b,c);
	}

	double FindX1(){
		return (-b-sqrt(b*b-4*a*c))/(2*a);
	}

	double FindX2(){
		return (-b+sqrt(b*b-4*a*c))/(2*a);
	}
};

int main(){
	double a, b, c;

    std::cout << "Enter a:";
    std::cin >> a;

    std::cout << "Enter b:";
    std::cin >> b;

    std::cout << "Enter c:";
    std::cin >> c;

    try{
		SquareEquation se(a, b, c);
		
		std::cout << "X1=" << se.FindX1() << "\n";
		std::cout << "X2=" << se.FindX2() << "\n";
    
    }catch(WrongArgumentException &ex){

        //if(ex.a==1) std::cout << "Ooops!" << std::endl;
        //*
        try{
         std::cout << "Exception in runtime:" << ex.what() << std::endl;
        }catch(int){
            std::cout << "foo" << std::endl;
        }//*/
    }
    
    return 0;
}
