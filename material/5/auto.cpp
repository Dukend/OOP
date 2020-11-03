#include <iostream>
#include <string>

auto sum(int a, int b) -> double
{
	if(a%2) return 0.5;
	 else
	return a + b;
};

namespace MyLongNamespace
{
	template <class T>
	struct MyStruct
	{
		T value;
		MyStruct(const T &vl) : value(vl)
		{
		}
	};
} // namespace MyLongNamespace

auto main() -> int
{
	MyLongNamespace::MyStruct<MyLongNamespace::MyStruct<int>> ms(MyLongNamespace::MyStruct<int>(10));

	MyLongNamespace::MyStruct<MyLongNamespace::MyStruct<int>> ms2 = ms;
	auto ms3 = ms;

	auto a = 10 + 20;

	decltype(a) b;
	b = 40;

	auto c = sum(10, 20);

	return 0;
}
