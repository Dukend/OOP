#include <cstdlib>
#include <iostream>
#include <math.h>

#define UNUSED(variable) (void)variable

class SquareEquation {
public:
	SquareEquation(double,double,double);
	double FindX1();
	double FindX2();
private:
    double a;
	double b;
	double c;
};

SquareEquation::SquareEquation(double a,double b ,double cc) 
{
	 this->a=a;
	 SquareEquation::b=b;
	 c =cc;
};

double SquareEquation::FindX1()
{
	return (-b-sqrt(b*b-4*a*c))/(2*a);
};

double SquareEquation::FindX2()
{
	return (-b+sqrt(b*b-4*a*c))/(2*a);
};


int main(int argc, char** argv) {
    double a, b, c;



    std::cout << "Enter a:";
    std::cin >> a;

    std::cout << "Enter b:";
    std::cin >> b;

    std::cout << "Enter c:";
    std::cin >> c;

    //SquareEquation se(a, b, c);
    SquareEquation *ptr_se = new SquareEquation(a, b, c);
    

    std::cout << "X1=" << ptr_se->FindX1() << "\n";
    std::cout << "X2=" << ptr_se->FindX2() << "\n";
    
    delete ptr_se;

    UNUSED(argc);
    UNUSED(argv);

    return 0;
}

