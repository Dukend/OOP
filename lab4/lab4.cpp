//////////////////
// by Dukend    //
//////////////////
// 9
//Figures:Triangle Square Rectangle
#include <iostream>
#include <cstring>
#include <exception>
#include <tuple>
#include <utility>
#include <type_traits>
#include <cmath>
template <typename T>
struct vertex
{
	using vertex_t = std::pair<T, T>;
};

template <typename T>
std::istream &operator>>(std::istream &is, std::pair<T, T> &v)
{
	is >> v.first >> v.second;

	return is;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::pair<T, T> &v)
{
	os << "[" << v.first << ", " << v.second << "]";

	return os;
}

template <typename T>
struct Vector
{
	using vertex_t = std::pair<T, T>;
	T p1, p2;

	Vector(T x_cord, T y_cord) : p1{x_cord}, p2{y_cord} {};
	Vector(vertex_t &p1, vertex_t &p2) : p1{p2.first - p1.first},
										 p2{p2.second - p1.second} {};
	double operator*(const Vector<T> &a) const
	{
		return (p1 * a.p1) + (p2 * a.p2);
	}
	Vector<T> &operator=(const Vector<T> &a)
	{
		p1 = a.p1;
		p2 = a.p2;
		return *this;
	}
};

template <typename T>
double Length(const Vector<T> &vector)
{
	return sqrt(vector.p1 * vector.p1 + vector.p2 * vector.p2);
}

template <typename T>
double Length(const std::pair<T, T> &A,
			  const std::pair<T, T> &B)
{
	return sqrt(pow((B.first - A.first), 2) +
				pow((B.second - A.second), 2));
}

template <typename T>
bool is_parallel(const Vector<T> &A, const Vector<T> &B)
{
	return (A.p1 * B.p2) - (A.p2 * B.p1) == 0;
}

/////////////////////////////////////
template <typename T>
struct Triangle
{
	using vertex_t = std::pair<T, T>;
	vertex_t vertices[3];
};
template <typename T>
typename Triangle<T>::vertex_t Center(const Triangle<T> &t)
{
	T x, y;
	x = (t.vertices[0].first + t.vertices[1].first + t.vertices[2].first) / 3;
	y = (t.vertices[0].second + t.vertices[1].second + t.vertices[2].second) / 3;

	return std::make_pair(x, y);
}

template <typename T>
double Area(const Triangle<T> &t)
{
	double res = 0;
	for (int i = 0; i <= 1; i++)
	{
		res += (t.vertices[i].first * t.vertices[i + 1].second -
				t.vertices[i + 1].first * t.vertices[i].second);
	}
	res += (t.vertices[2].first * t.vertices[0].second -
			t.vertices[0].first * t.vertices[2].second);
	res = 0.5 * std::abs(res);

	return res;
}

template <typename T>
std::ostream &Print(std::ostream &os, const Triangle<T> &t)
{
	for (int i = 0; i < 3; i++)
	{
		os << t.vertices[i];
		if (i != 2)
		{
			os << " ";
		}
	}

	return os;
}

template <typename T>
std::istream &Read(std::istream &is, Triangle<T> &t)
{
	for (int i = 0; i < 3; i++)
	{
		is >> t.vertices[i].first >> t.vertices[i].second;
	}
	double AB = Length(t.vertices[0], t.vertices[1]),
		   BC = Length(t.vertices[1], t.vertices[2]),
		   AC = Length(t.vertices[0], t.vertices[2]);
	if (AB >= BC + AC || BC >= AB + AC || AC >= AB + BC)
	{
		throw std::logic_error("Vertices must not be on the same line.");
	}

	return is;
}

template <typename T>
std::istream &operator>>(std::istream &is, Triangle<T> &t)
{
	return Read(is, t);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Triangle<T> &t)
{
	return Print(os, t);
}
/////////////////////////////////////
template <typename T>
struct Square
{
	using vertex_t = std::pair<T, T>;
	vertex_t vertices[4];
};

template <typename T>
typename Square<T>::vertex_t Center(const Square<T> &s)
{
	T cord;
	if (s.vertices[1].first - s.vertices[0].first != 0 && s.vertices[1].second - s.vertices[0].second != 0)
	{
		cord = (s.vertices[1].first - s.vertices[0].first) / 2;
		return std::make_pair(cord, cord);
	}
	else if (s.vertices[0].second - s.vertices[1].second == 0)
	{
		cord = (s.vertices[1].first - s.vertices[0].first) / 2;
		return std::make_pair(cord, s.vertices[0].second);
	}
	else
	{
		cord = (s.vertices[1].second - s.vertices[0].second) / 2;
		return std::make_pair(s.vertices[0].first, cord);
	}
}

template <typename T>
double Area(const Square<T> &s)
{
	return 0.5 * Length(s.vertices[0], s.vertices[1]) * Length(s.vertices[0], s.vertices[1]);
}

template <typename T>
std::ostream &Print(std::ostream &os, const Square<T> &s)
{
	if ((s.vertices[1].second - s.vertices[0].second != 0) && ((s.vertices[0].first - s.vertices[1].first) != 0))
	{
		os << s.vertices[0] << " " << std::make_pair(s.vertices[0].first, s.vertices[0].second + (s.vertices[1].second - s.vertices[0].second)) << " ";
		os << s.vertices[1] << " " << std::make_pair(s.vertices[1].first, s.vertices[1].second + (s.vertices[0].second - s.vertices[1].second));
	}
	else if (s.vertices[0].second - s.vertices[1].second == 0)
	{
		os << s.vertices[0] << " " << std::make_pair(s.vertices[0].first + (s.vertices[1].first - s.vertices[0].first) / 2, s.vertices[0].second + (s.vertices[1].first - s.vertices[0].first) / 2) << " ";
		os << s.vertices[1] << " " << std::make_pair(s.vertices[0].first + (s.vertices[1].first - s.vertices[0].first) / 2, s.vertices[0].second - (s.vertices[1].first - s.vertices[0].first) / 2) << " ";
	}
	else if ((s.vertices[0].first - s.vertices[1].first) == 0)
	{
		os << s.vertices[0] << " " << std::make_pair(s.vertices[0].first - (s.vertices[1].second - s.vertices[0].second) / 2, s.vertices[0].second + (s.vertices[1].second - s.vertices[0].second) / 2) << " ";
		os << s.vertices[1] << " " << std::make_pair(s.vertices[0].first + (s.vertices[1].second - s.vertices[0].second) / 2, s.vertices[0].second + (s.vertices[1].second - s.vertices[0].second) / 2) << " ";
	}

	return os;
}

template <typename T>
std::istream &Read(std::istream &is, Square<T> &s)
{
	for (int i = 0; i < 2; i++)
	{
		is >> s.vertices[i].first >> s.vertices[i].second;
	}
	if (s.vertices[0].first == s.vertices[1].first && s.vertices[0].second == s.vertices[1].second)
	{
		throw std::logic_error("Vertices must not match");
	}

	return is;
}

template <typename T>
std::istream &operator>>(std::istream &is, Square<T> &s)
{
	return Read(is, s);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Square<T> &s)
{
	return Print(os, s);
}
/////////////////////////////////////
template <typename T>
struct Rectangle
{
	using vertex_t = std::pair<T, T>;
	vertex_t vertices[4];
};
template <typename T>
typename Rectangle<T>::vertex_t Center(const Rectangle<T> &r)
{
	T x, y;
	x = (r.vertices[0].first + r.vertices[1].first + r.vertices[2].first + r.vertices[3].first) / 4;
	y = (r.vertices[0].second + r.vertices[1].second + r.vertices[2].second + r.vertices[3].second) / 4;

	return std::make_pair(x, y);
}
template <typename T>
double Area(const Rectangle<T> &r)
{
	double res = 0;
	for (int i = 0; i <= 2; i++)
	{
		res += (r.vertices[i].first * r.vertices[i + 1].second -
				r.vertices[i + 1].first * r.vertices[i].second);
	}
	res += (r.vertices[2].first * r.vertices[0].second -
			r.vertices[0].first * r.vertices[2].second);
	res = 0.5 * std::abs(res);
	return res;
}

template <typename T>
std::ostream &Print(std::ostream &os, const Rectangle<T> &r)
{
	for (int i = 0; i < 4; i++)
	{
		os << r.vertices[i];
		if (i != 3)
		{
			os << " ";
		}
	}
	return os;
}

template <typename T>
std::istream &Read(std::istream &is, Rectangle<T> &r)
{
	for (int i = 0; i < 4; i++)
	{
		is >> r.vertices[i].first >> r.vertices[i].second;
	}
	Vector<T> AB = {r.vertices[0], r.vertices[1]},
			  BC = {r.vertices[1], r.vertices[2]},
			  CD = {r.vertices[2], r.vertices[3]},
			  DA = {r.vertices[3], r.vertices[0]};
	if (!is_parallel(DA, BC))
	{
		std::swap(r.vertices[0], r.vertices[1]);
		AB = {r.vertices[0], r.vertices[1]};
		BC = {r.vertices[1], r.vertices[2]};
		CD = {r.vertices[2], r.vertices[3]};
		DA = {r.vertices[3], r.vertices[0]};
	}
	if (!is_parallel(AB, CD))
	{
		std::swap(r.vertices[1], r.vertices[2]);
		AB = {r.vertices[0], r.vertices[1]};
		BC = {r.vertices[1], r.vertices[2]};
		CD = {r.vertices[2], r.vertices[3]};
		DA = {r.vertices[3], r.vertices[0]};
	}
	if (AB * BC || BC * CD || CD * DA || DA * AB)
	{
		throw std::logic_error("The sides of the Rectangle should be perpendicular");
	}
	if (!Length(AB) || !Length(BC) || !Length(CD) || !Length(DA))
	{
		throw std::logic_error("The sides of the Rectangle must be greater than zero");
	}
	return is;
}

template <typename T>
std::istream &operator>>(std::istream &is, Rectangle<T> &r)
{
	return Read(is, r);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Rectangle<T> &r)
{
	return Print(os, r);
}
/////////////////////////////////////

template <typename T>
using vertex_t = std::pair<T, T>;

template <typename T>
struct is_vertex : std::false_type
{
};

template <typename T>
struct is_vertex<std::pair<T, T>> : std::true_type
{
};

template <class T>
struct is_figurelike_tuple : std::false_type
{
};

template <class Head, class... Tail>
struct is_figurelike_tuple<std::tuple<Head, Tail...>> : std::conjunction<is_vertex<Head>,
																		 std::is_same<Head, Tail>...>
{
};

template <typename T>
inline constexpr bool is_figurelike_tuple_v = is_figurelike_tuple<T>::value;

template <typename T, typename = void>
struct has_method_area : std::false_type
{
};

template <typename T>
struct has_method_area<T, decltype(std::declval<const T &>().Area())> : std::true_type
{
};

template <typename T>
inline constexpr bool has_method_area_v = has_method_area<T>::value;

template <typename T>
std::enable_if_t<has_method_area_v<T>, double>
Area(const T &object)
{
	return object.Area();
}

template <typename T, typename = void>
struct has_method_center : std::false_type
{
};

template <typename T>
struct has_method_center<T, decltype(std::declval<const T &>().Center())> : std::true_type
{
};

template <typename T>
inline constexpr bool has_method_center_v = has_method_center<T>::value;

template <typename T>
std::enable_if_t<has_method_center_v<T>, vertex_t<double>>
Center(const T &object)
{
	return object.Center();
}

template <typename T, typename = void>
struct has_method_print : std::false_type
{
};

template <typename T>
struct has_method_print<T, decltype(std::declval<const T &>().Print())> : std::true_type
{
};

template <typename T>
inline constexpr bool has_method_print_v = has_method_print<T>::value;

template <typename T>
std::enable_if_t<has_method_print_v<T>, std::ostream &>
Print(std::ostream &os, const T &object)
{
	return Print(os, object);
}

template <typename T, typename = void>
struct has_method_read : std::false_type
{
};

template <typename T>
struct has_method_read<T, decltype(std::declval<const T &>().Read())> : std::true_type
{
};

template <typename T>
inline constexpr bool has_method_read_v = has_method_read<T>::value;

template <typename T>
std::enable_if_t<has_method_read_v<T>, std::istream &>
Read(std::istream &is, T &object)
{
	return Read(is, object);
}

template <typename T>
double area_square(const T &tuple)
{
	return 0.5 * Length(std::get<0>(tuple), std::get<1>(tuple)) * Length(std::get<0>(tuple), std::get<1>(tuple));
}

template <size_t Id, typename T>
double compute_area(const T &tuple)
{
	if constexpr (Id >= std::tuple_size_v<T>)
	{
		return 0;
	}
	else
	{
		const auto dx1 = std::get<Id - 0>(tuple).first - std::get<0>(tuple).first;
		const auto dy1 = std::get<Id - 0>(tuple).second - std::get<0>(tuple).second;
		const auto dx2 = std::get<Id - 1>(tuple).first - std::get<0>(tuple).first;
		const auto dy2 = std::get<Id - 1>(tuple).second - std::get<0>(tuple).second;
		const double local_area = std::abs(dx1 * dy2 - dy1 * dx2) * 0.5;
		return local_area + compute_area<Id + 1>(tuple);
	}
}

template <typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, double>
Area(const T &object)
{
	if constexpr (std::tuple_size_v<T> == 2)
	{
		return area_square(object);
	}
	else
	{
		return compute_area<2>(object);
	}
}

template <typename T>
vertex_t<double> center_square(const T &object)
{
	decltype(std::get<0>(object).first) cord;
	if (std::get<1>(object).first - std::get<0>(object).first != 0 && std::get<1>(object).second - std::get<0>(object).second != 0)
	{
		cord = (std::get<1>(object).first - std::get<0>(object).first) / 2;
		return std::make_pair(cord, cord);
	}
	else if (std::get<0>(object).second - std::get<1>(object).second == 0)
	{
		cord = (std::get<1>(object).first - std::get<0>(object).first) / 2;
		return std::make_pair(cord, std::get<0>(object).second);
	}
	else
	{
		cord = (std::get<1>(object).second - std::get<0>(object).second) / 2;
		return std::make_pair(std::get<0>(object).first, cord);
	}
}

template <size_t Id, typename T>
double recursive_center_x(const T &tuple)
{
	if constexpr (Id >= std::tuple_size_v<T>)
	{
		return 0;
	}
	else
	{
		return (std::get<Id>(tuple).first / std::tuple_size_v<T>)+recursive_center_x<Id + 1>(tuple);
	}
}

template <size_t Id, typename T>
double recursive_center_y(const T &tuple)
{
	if constexpr (Id >= std::tuple_size_v<T>)
	{
		return 0;
	}
	else
	{
		return (std::get<Id>(tuple).second / std::tuple_size_v<T>)+recursive_center_y<Id + 1>(tuple);
	}
}

template <size_t Id, typename T>
vertex_t<double> compute_center(const T &tuple)
{
	return {recursive_center_x<Id>(tuple), recursive_center_y<Id>(tuple)};
}

template <typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, vertex_t<double>>
Center(const T &object)
{
	if constexpr (std::tuple_size_v<T> != 2)
	{
		return compute_center<0>(object);
	}
	else
	{
		return center_square(object);
	}
}

template <typename T>
void print_square(std::ostream &os, const T &tuple)
{
	if ((std::get<1>(tuple).second - std::get<0>(tuple).second != 0) && ((std::get<0>(tuple).first - std::get<1>(tuple).first) != 0))
	{
		os << std::get<0>(tuple) << " " << std::make_pair(std::get<0>(tuple).first, std::get<0>(tuple).second + (std::get<1>(tuple).second - std::get<0>(tuple).second)) << " ";
		os << std::get<1>(tuple) << " " << std::make_pair(std::get<1>(tuple).first, std::get<1>(tuple).second + (std::get<0>(tuple).second - std::get<1>(tuple).second));
	}
	else if (std::get<0>(tuple).second - std::get<1>(tuple).second == 0)
	{
		os << std::get<0>(tuple) << " " << std::make_pair(std::get<0>(tuple).first + (std::get<1>(tuple).first - std::get<0>(tuple).first) / 2, std::get<0>(tuple).second + (std::get<1>(tuple).first - std::get<0>(tuple).first) / 2) << " ";
		os << std::get<1>(tuple) << " " << std::make_pair(std::get<0>(tuple).first + (std::get<1>(tuple).first - std::get<0>(tuple).first) / 2, std::get<0>(tuple).second - (std::get<1>(tuple).first - std::get<0>(tuple).first) / 2) << " ";
	}
	else if ((std::get<0>(tuple).first - std::get<1>(tuple).first) == 0)
	{
		os << std::get<0>(tuple) << " " << std::make_pair(std::get<0>(tuple).first - (std::get<1>(tuple).second - std::get<0>(tuple).second) / 2, std::get<0>(tuple).second + (std::get<1>(tuple).second - std::get<0>(tuple).second) / 2) << " ";
		os << std::get<1>(tuple) << " " << std::make_pair(std::get<0>(tuple).first + (std::get<1>(tuple).second - std::get<0>(tuple).second) / 2, std::get<0>(tuple).second + (std::get<1>(tuple).second - std::get<0>(tuple).second) / 2) << " ";
	}
}

template <size_t Id, typename T>
void recursive_print(std::ostream &os, const T &tuple)
{
	if constexpr (Id >= std::tuple_size_v<T>)
	{
		return;
	}
	else
	{
		os << std::get<Id>(tuple) << " ";
		recursive_print<Id + 1>(os, tuple);
	}
}

template <typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
Print(std::ostream &os, const T &object)
{
	if constexpr (std::tuple_size_v<T> != 2)
	{
		recursive_print<0>(os, object);
	}
	else
	{
		print_square(os, object);
	}
}

template <typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
Check_triangle(T &object)
{
	double AB = Length(std::get<0>(object), std::get<1>(object)),
		   BC = Length(std::get<1>(object), std::get<2>(object)),
		   AC = Length(std::get<0>(object), std::get<2>(object));
	if (AB >= BC + AC || BC >= AB + AC || AC >= AB + BC)
	{
		throw std::logic_error("Vertices must not be on the same line.");
	}
}

template <typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
Check_rectangle(T &object)
{
	Vector<decltype(std::get<0>(object).first)> AB = {std::get<0>(object), std::get<1>(object)},
												BC = {std::get<1>(object), std::get<2>(object)},
												CD = {std::get<2>(object), std::get<3>(object)},
												DA = {std::get<3>(object), std::get<0>(object)};
	if (!is_parallel(DA, BC) || !is_parallel(AB, CD))
	{
		throw std::logic_error("Vertices must be entered clockwise or counterclockwise");
	}
	if (AB * BC || BC * CD || CD * DA || DA * AB)
	{
		throw std::logic_error("The sides should be perpendicular");
	}
	if (!Length(AB) || !Length(BC) || !Length(CD) || !Length(DA))
	{
		throw std::logic_error("The sides must be greater than zero");
	}
}

template <typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
Check_square(T &object)
{
	if (std::get<0>(object).first == std::get<1>(object).first && std::get<0>(object).second == std::get<1>(object).second)
	{
		throw std::logic_error("Vertices must not match");
	}
}

template <typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
Check(T &object)
{
	if constexpr (std::tuple_size_v<T> == 2)
	{
		Check_square(object);
	}
	else if constexpr (std::tuple_size_v<T> == 3)
	{
		Check_triangle(object);
	}
	else if (std::tuple_size_v<T> == 4)
	{
		Check_rectangle(object);
	}
}

template <size_t Id, typename T>
void recursive_read(std::istream &is, T &tuple)
{
	if constexpr (Id >= std::tuple_size_v<T>)
	{
		return;
	}
	else
	{
		is >> std::get<Id>(tuple);
		recursive_read<Id + 1>(is, tuple);
	}
}

template <typename T>
std::enable_if_t<is_figurelike_tuple_v<T>, void>
Read(std::istream &is, T &object)
{
	recursive_read<0>(is, object);
	Check(object);
}
/////////////////////////////////////
template <typename T>
void task()
{
	T object;
	std::cout << "Input points: ";
	try
	{
		Read(std::cin, object);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
	Print(std::cout, object);
	std::cout << std::endl
			  << Area(object) << std::endl;
	std::cout << Center(object) << std::endl;
}

int main()
{
	std::string com;
	std::cout << "Figure | Tuple" << std::endl;
	std::cout << "...................................." << std::endl;
	while (std::cin >> com)
	{
		std::string object_type;
		if (com == "Figure")
		{
			std::cout << "Triangle | Square | Rectangle" << std::endl;
			std::cin >> object_type;
			std::cout << "...................................." << std::endl;
			if (object_type == "Triangle")
			{
				task<Triangle<double>>();
			}
			else if (object_type == "Square")
			{
				task<Square<double>>();
			}
			else if (object_type == "Rectangle")
			{
				task<Rectangle<double>>();
			}
			else
			{
				std::cout << "Invalid figure" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "...................................." << std::endl;
				std::cout << "Figure | Tuple" << std::endl;
				continue;
			}
		}
		else if (com == "Tuple")
		{
			std::cout << "Triangle | Square | Rectangle" << std::endl;
			std::cout << "...................................." << std::endl;
			std::cin >> object_type;
			std::cout << "...................................." << std::endl;
			if (object_type == "Triangle")
			{
				task<std::tuple<vertex_t<double>, vertex_t<double>,
								vertex_t<double>>>();
			}
			else if (object_type == "Square")
			{
				task<std::tuple<vertex_t<double>, vertex_t<double>>>();
			}
			else if (object_type == "Rectangle")
			{
				task<std::tuple<vertex_t<double>, vertex_t<double>,
								vertex_t<double>, vertex_t<double>>>();
			}
			else
			{
				std::cout << "Invalid figure" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Figure | Tuple" << std::endl;
				std::cout << "...................................." << std::endl;
				continue;
			}
		}
		else
		{
			std::cout << "Invalid com" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "...................................." << std::endl;
			continue;
		}
		std::cout << "...................................." << std::endl;
		std::cout << "Figure | Tuple" << std::endl;
	}

	return 0;
}