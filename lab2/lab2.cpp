// By Dukend
// https://github.com/Dukend
// Лаба 2 ООП

// Комплексное число в тригонометрической форме представляются 
// парой действительных чисел (r, j), где r – радиус (модуль), j  – угол. 
// Реализовать класс Complex для работы с комплексными числами. 
// Обязательно должны быть присутствовать операции
// -    сложения add, (r1, j1) + (r2, j2);
// -    вычитания sub, (r1, j1) – (r2, j2);
// -    умножения mul, (r1, j1) ´ (r2, j2);
// -    деления div, (r1, j1) / (r2, j2) ;
// -    сравнение equ, (r1, j1) = (r2, j2), если (r1 = r2) и (j1 = j2); 
// -   	сопряженное число conj, conj(r, j) = (r, –j).
// Реализовать операции сравнения по действительной части.
// Операции сложения, вычитания, умножения, деления, сравнения на равенство должны быть выполнены в виде перегрузки операторов.

#include <iostream>
#include <cmath>

class complex
{

public:
	complex();
	complex(double a, double b);
	complex conj() const;

	friend complex operator+(const complex &, const complex &);
	friend complex operator-(const complex &, const complex &);
	friend complex operator*(const complex &, const complex &);
	friend complex operator/(const complex &, const complex &);
	friend std::ostream &operator<<(std::ostream &out, const complex &complex);
	friend void operator>>(std::istream &in, complex &complex);
	friend bool operator==(const complex &, const complex &);

private:
	double r;
	double fi;
};

complex::complex()
{
	r = 0;
	fi = 0;
}

complex::complex(double a, double b)
{
	if (b >= 2)
	{
		b = fmod(b, 2);
	}
	else if (b < 0)
	{
		b = fmod(b, 2) + 2;
	}
	r = a;
	fi = b;
}

// функция сопряжение
complex complex::conj() const
{
	complex result;
	result.r = r;
	result.fi = -fi;
	return result;
}

// оператор вывода
std::ostream &operator<<(std::ostream &out, const complex &complex)
{
	return out << complex.r << " " << complex.fi << "p";
}

// оператор ввода
void operator>>(std::istream &in, complex &complex)
{
	in >> complex.r >> complex.fi;

	if (complex.fi >= 2)
	{
		complex.fi = fmod(complex.fi, 2);
	}
	else if (complex.fi < 0)
	{
		complex.fi = fmod(complex.fi, 2) + 2;
	}
}

// оператор присваивания
bool operator==(const complex &a, const complex &b)
{
	if (a.r == b.r and a.fi == b.fi)
	{
		return true;
	}
	return false;
}

// оператор сложения
complex operator+(const complex &a, const complex &b)
{
	complex result;
	double cos_1 = cos(a.fi * M_PI);
	double cos_2 = cos(b.fi * M_PI);
	double sin_1 = sin(a.fi * M_PI);
	double sin_2 = sin(b.fi * M_PI);
	double a_1 = a.r * cos_1;
	double a_2 = b.r * cos_2;
	double b_1 = a.r * sin_1;
	double b_2 = b.r * sin_2;
	double a_r = a_1 + a_2;
	double b_r = b_1 + b_2;
	result.r = sqrt(a_r * a_r + b_r * b_r);
	//1
	if (a_r / result.r > 0 and b_r / result.r >= 0)
	{
		result.fi = (acos(a_r / result.r)) / M_PI;
	}
	//2
	if (a_r / result.r <= 0 and b_r / result.r > 0)
	{
		result.fi = (acos(a_r / result.r)) / M_PI;
	}
	//3
	if (a_r / result.r >= 0 and b_r / result.r < 0)
	{
		result.fi = (asin(b_r / result.r)) / M_PI;
	}
	//4
	if (a_r / result.r < 0 and b_r / result.r <= 0)
	{
		result.fi = -(acos(a_r / result.r)) / M_PI;
	}
	return result;
}

// оператор вычитания
complex operator-(const complex &a, const complex &b)
{
	complex result;
	double cos_1 = cos(a.fi * M_PI);
	double cos_2 = cos((b.fi - 1) * M_PI);
	double sin_1 = sin(a.fi * M_PI);
	double sin_2 = sin((b.fi - 1) * M_PI);
	double a_1 = a.r * cos_1;
	double a_2 = b.r * cos_2;
	double b_1 = a.r * sin_1;
	double b_2 = b.r * sin_2;
	double a_r = a_1 + a_2;
	double b_r = b_1 + b_2;
	result.r = sqrt(a_r * a_r + b_r * b_r);
	//1
	if (a_r / result.r > 0 and b_r / result.r >= 0)
	{
		result.fi = (acos(a_r / result.r)) / M_PI;
	}
	//2
	if (a_r / result.r <= 0 and b_r / result.r > 0)
	{
		result.fi = (acos(a_r / result.r)) / M_PI;
	}
	//3
	if (a_r / result.r >= 0 and b_r / result.r < 0)
	{
		result.fi = (asin(b_r / result.r)) / M_PI;
	}
	//4
	if (a_r / result.r < 0 and b_r / result.r <= 0)
	{
		result.fi = -(acos(a_r / result.r)) / M_PI;
	}

	return result;
}

// оператор умножения
complex operator*(const complex &a, const complex &b)
{
	complex result;
	result.r = a.r * b.r;
	result.fi = a.fi + b.fi;
	return result;
}

// оператор деления
complex operator/(const complex &a, const complex &b)
{
	complex result;
	result.r = a.r / b.r;
	result.fi = a.fi - b.fi;
	return result;
}

// пользовательский литерал
complex operator"" _f(long double x)
{
	complex p(x, 0.0);
	return p;
}
complex operator"" _s(long double x)
{
	complex p(0.0, x);
	return p;
}

int main()
{
	complex a, b, ans;
	std::cin >> a;
	std::cin >> b;
	std::cout << "First number : " << a << "\n";
	std::cout << "Second number : " << b << "\n";
	std::cout << " +    =  " << a + b << "\n";
	std::cout << " -    =  " << a - b << "\n";
	std::cout << " *    =  " << a * b << "\n";
	std::cout << " /    =  " << a / b << "\n";
	ans = a.conj();
	std::cout << "conj  =  " << ans << "\n";
	ans = b.conj();
	std::cout << "conj  =  " << ans << "\n";
	if (a == b)
		std::cout << "a == b\n";
	else
		std::cout << "a != b\n";
	std::cout << "--------------------------\nLiterals\n";
	complex c = 2.24_f;
	complex d = 2.14_s;
	// std::cout << c << std::endl;
	// std::cout << d << std::endl;
	std::cout << "c = 2.24_f : " << c << "\n";
	std::cout << "d = 2.14_s : " << d << "\n";

	return 0;
}
