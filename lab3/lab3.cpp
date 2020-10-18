//////////////////
// by Dukend    //
//////////////////
// 9
//Figures:Triangle Square Rectangle
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

class Point{
	double x;
	double y;

public:
	Point() : x{0}, y{0} {}
	Point(double a, double b) : x{a}, y{b} {}
	Point(const Point &other) : x{other.x}, y{other.y} {}
	double X() const{
		return x;
	}
	double Y() const{
		return y;
	}
	Point operator+(const Point &a) const{
		return {x + a.x, y + a.y};
	}
	Point operator-(const Point &a) const{
		return {x - a.x, y - a.y};
	}
	Point operator*(double a) const{
		return {x * a, y * a};
	}
	Point operator/(double a) const{
		return {x / a, y / a};
	}
	friend std::ostream &operator<<(std::ostream &out, const Point &a){
		out << "(" << a.x << "; " << a.y << ")";
		return out;
	}
	friend std::istream &operator>>(std::istream &in, Point &a){
		in >> a.x >> a.y;
		return in;
	}
};
//////////////////////////////////////////////////////////////////////////////////////

class Vector{
public:
	double x, y;
	Vector(double x_cord, double y_cord) : x{x_cord}, y{y_cord} {}
	Vector(Point &p1, Point &p2) : x{p2.X() - p1.X()}, y{p2.Y() - p1.Y()} {}
	double operator*(const Vector &a) const{
		return (x * a.x) + (y * a.y);
	}
	Vector &operator=(const Vector &a){
		x = a.x;
		y = a.y;
		return *this;
	}
};
double Length(const Point &a, const Point &b){
	return sqrt(pow((b.X() - a.X()), 2) + pow((b.Y() - a.Y()), 2));
}
double Length(const Vector &a){
	return sqrt(pow(a.x, 2) + pow(a.y, 2));
}
bool is_parallel(const Vector &a, const Vector &b){
	return (a.x * b.y) - (a.y * b.x) == 0;
}
//////////////////////////////////////////////////////////////////////////////////////

class Figure{
public:
	virtual Point Center() const = 0;
	virtual double Area() const = 0;
	virtual std::ostream &Print(std::ostream &out) const = 0;
	virtual std::istream &Scan(std::istream &in) = 0;
	virtual ~Figure() = default;
};

std::ostream &operator<<(std::ostream &out, const Figure &fig){
	fig.Print(out);
	return out;
}
std::istream &operator>>(std::istream &in, Figure &fig){
	fig.Scan(in);
	return in;
}
//////////////////////////////////////////////////////////////////////////////////////

class Triangle : public Figure{
public:
	Point A, B, C;
	Triangle() : A{Point{}}, B{Point{}}, C{Point{}} {}
	Triangle(Point a, Point b, Point c) : A{a}, B{b}, C{c}{
		double AB = Length(A, B), BC = Length(B, C), AC = Length(A, C);
		if (AB >= BC + AC || BC >= AB + AC || AC >= AB + BC){
			throw std::logic_error("Points must not be on the same line.");
		}
	}
	Point Center() const override{
		Point mid_of_base{(A + C) / 2};

		return {(B + mid_of_base * 2) / 3};
	}
	double Area() const override{
		double AB = Length(A, B), BC = Length(B, C), AC = Length(A, C);
		double perim = AB + BC + AC;
		return sqrt((perim / 2) * (perim / 2 - AB) * (perim / 2 - BC) * (perim / 2 - AC));
	}
	std::ostream &Print(std::ostream &out) const override{
		out << "Triangle: p1 = " << A << ", p2 = " << B << ", p3 = " << C;
		return out;
	}
	std::istream &Scan(std::istream &in) override{
		in >> A >> B >> C;
		(*this) = Triangle(A, B, C);
		return in;
	}
};
//////////////////////////////////////////////////////////////////////////////////////

class Square : public Figure{
public:
	Point A, B, C, D;
	Square() : A{Point{}}, B{Point{}}, C{Point{}}, D{Point{}} {}
	Square(Point a, Point b, Point c, Point d) : A{a}, B{b}, C{c}, D{d}{
		Vector AB{A, B}, BC{B, C}, CD{C, D}, DA{D, A};
		if (!is_parallel(DA, BC)){
			std::swap(A, B);
			AB = {A, B};
			BC = {B, C};
			CD = {C, D};
			DA = {D, A};
		}
		if (!is_parallel(AB, CD)){
			std::swap(B, C);
			AB = {A, B};
			BC = {B, C};
			CD = {C, D};
			DA = {D, A};
		}
		if (AB * BC || BC * CD || CD * DA || DA * AB){
			throw std::logic_error("The sides should be perpendicular");
		}
		if (Length(AB) != Length(BC) || Length(BC) != Length(CD) || Length(CD) != Length(DA) || Length(DA) != Length(AB)){
			throw std::logic_error("The sides should be equal");
		}
		if (!Length(AB) || !Length(BC) || !Length(CD) || !Length(DA)){
			throw std::logic_error("The sides must be greater than zero");
		}
	}
	Point Center() const override{
		return Point{(B + D) / 2};
	}
	double Area() const override{
		return Length(A, B) * Length(A, B);
	}
	std::ostream &Print(std::ostream &out) const override{
		out << "Square: p1 = " << A << ", p2 = " << B << ", p3 = " << C << ", p4 = " << D;
		return out;
	}
	std::istream &Scan(std::istream &in) override{
		in >> A >> B >> C >> D;
		(*this) = Square(A, B, C, D);
		return in;
	}
};
//////////////////////////////////////////////////////////////////////////////////////

class Rectangle : public Figure{
public:
	Point A, B, C, D;
	Rectangle() : A{Point{}}, B{Point{}}, C{Point{}}, D{Point{}} {}
	Rectangle(Point a, Point b, Point c, Point d) : A{a}, B{b}, C{c}, D{d}{
		Vector AB{A, B}, BC{B, C}, CD{C, D}, DA{D, A};
		if (!is_parallel(DA, BC)){
			std::swap(A, B);
			AB = {A, B};
			BC = {B, C};
			CD = {C, D};
			DA = {D, A};
		}
		if (!is_parallel(AB, CD)){
			std::swap(B, C);
			AB = {A, B};
			BC = {B, C};
			CD = {C, D};
			DA = {D, A};
		}
		if (AB * BC || BC * CD || CD * DA || DA * AB){
			throw std::logic_error("The sides of the rectangle should be perpendicular");
		}
		if (!Length(AB) || !Length(BC) || !Length(CD) || !Length(DA)){
			throw std::logic_error("The sides of the rectangle must be greater than zero");
		}
	}
	Point Center() const override{
		return Point{(B + D) / 2};
	}
	double Area() const override{
		return Length(D, A) * Length(B, A);
	}
	std::ostream &Print(std::ostream &out) const override{
		out << "Rectangle: p1 = " << A << ", p2 = " << B << ", p3 = " << C << ", p4 = " << D;
		return out;
	}
	std::istream &Scan(std::istream &in) override{
		in >> A >> B >> C >> D;
		(*this) = Rectangle(A, B, C, D);
		return in;
	}
};

//////////////////////////////////////////////////////////////////////////////////////

int main(){
	std::vector<Figure *> figures;
	std::string command;
	std::cout << "Menu:\nAdd\nPrint\nArea\nCenter\nAllPrint\nDelete\nAllDelete\nQuit\n";
	std::cout << ".............................................................\n";
	while (std::cin >> command){
		if (command == "Add"){
			std::string fig_type;
			std::cout << "Figures:\nTriangle\nSquare\nRectangle" << std::endl;
			std::cin >> fig_type;
			Figure *new_fig;
			if (fig_type == "Triangle"){
				new_fig = new Triangle;
			}
			else if (fig_type == "Square"){
				new_fig = new Square;
			}
			else if (fig_type == "Rectangle"){
				new_fig = new Rectangle;
			}
			else{
				std::cout << "Invalid figure type" << std::endl;
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << ".............................................................\n";
				continue;
			}
			try{
				std::cout << "Points: ";
				std::cin >> (*new_fig);
				std::cout << "\n.............................................................\n";
			}
			catch (std::exception &x){
				std::cout << x.what() << std::endl;
				std::cout << ".............................................................\n";
				delete new_fig;
				continue;
			}
			figures.push_back(new_fig);
		}
		else if (command == "Print"){
			unsigned int index;
			std::cout << "Index: ";
			std::cin >> index;
			if (index < 0 || index >= figures.size()){
				std::cout << "No object at that index" << std::endl;
				std::cout << ".............................................................\n";
				continue;
			}
			std::cout << "Figure at index " << index << ": " << *figures[index] << std::endl;
			std::cout << ".............................................................\n";
		}
		else if (command == "Area"){
			unsigned int index;
			std::cout << "Index: ";
			std::cin >> index;
			if (index < 0 || index >= figures.size()){
				std::cout << "No object at that index" << std::endl;
				std::cout << ".............................................................\n";
				continue;
			}
			std::cout << *figures[index] << std::endl
					  << "-> Area: " << figures[index]->Area() << std::endl;
			std::cout << ".............................................................\n";
		}
		else if (command == "Center"){
			unsigned int index;
			std::cout << "Index: ";
			std::cin >> index;
			if (index < 0 || index >= figures.size()){
				std::cout << "No object at that index" << std::endl;
				std::cout << ".............................................................\n";
				continue;
			}
			std::cout << *figures[index] << std::endl
					  << "-> Center: " << figures[index]->Center() << std::endl;
			std::cout << ".............................................................\n";
		}
		else if (command == "AllPrint"){
			for (unsigned int i = 0; i < figures.size(); i++){
				std::cout << i << ". " << *figures[i] << std::endl;
			}
			std::cout << ".............................................................\n";
		}
		else if (command == "Delete"){
			unsigned int index;
			std::cout << "Index: ";
			std::cin >> index;
			if (index < 0 || index >= figures.size()){
				std::cout << "Bad index" << std::endl;
				std::cout << ".............................................................\n";
				continue;
			}
			delete figures[index];
			figures.erase(figures.begin() + index);
			std::cout << ".............................................................\n";
		}
		else if (command == "AllDelete"){
			for (std::vector<Figure *>::iterator i = figures.begin(); i != figures.end(); i++){
				delete *i;
			}
			figures.clear();
			std::cout << ".............................................................\n";
		}
		else if (command == "Quit"){
			for (unsigned int i = 0; i < figures.size(); i++){
				delete figures[i];
			}
			std::cout << ".............................................................\n";
			return 0;
		}
		else{
			std::cout << "khe.. khe..\nMenu:\nAdd\nPrint\nArea\nCenter\nAllPrint\nDelete\nAllDelete\nQuit\n";
			std::cout << ".............................................................\n";
		}
	}
	return 0;
}
