#include <bits/stdc++.h>

class Long
{
private:
	uint32_t first, second;
	uint64_t glue() const
	{ // склейка чисел
		uint64_t result;
		result = ((uint64_t)first << 32u) + (uint64_t)second;
		return result;
	}
	void split(uint64_t n)
	{ // расклейка чисел
		first = n >> 32u;
		second = n & (0u - 1u);
	}

public:
	void read()
	{
		std::cin >> first >> second;
	}
	void write() const
	{
		if (first != 0)
		{
			std::cout << first << " ";
		}
		std::cout << second;
	}

	Long add(const Long &next) const;  // сложение
	Long sub(const Long &next) const;  // модуль разности
	Long mult(const Long &next) const; // умножение
	Long div(const Long &next) const;  // деление

	bool more(const Long &next) const;	// больше
	bool less(const Long &next) const;	// меньше
	bool equal(const Long &next) const; // равно
};

Long Long::add(const Long &next) const
{
	Long result;
	result.second = this->second + next.second;
	result.first = this->first + next.first;
	if (std::numeric_limits<uint32_t>::max() - this->second < next.second)
	{
		result.first += 1;
	}
	return result;
}

Long Long::sub(const Long &next) const
{
	Long result;
	result.first = this->first - next.first;
	result.second = this->second - next.second;
	if (this->second < next.second)
	{
		result.first -= 1;
	}
	return result;
}

Long Long::mult(const Long &next) const
{
	Long result;
	uint64_t a = glue();
	uint64_t b = next.glue();
	uint64_t c = a * b;
	result.split(c);
	return result;
}

Long Long::div(const Long &next) const
{
	Long result;
	uint64_t a = glue();
	uint64_t b = next.glue();
	uint64_t c = a / b;
	result.split(c);
	return result;
}

bool Long::more(const Long &next) const
{
	return (this->first > next.first || (this->first == next.first && this->second > next.second));
}

bool Long::less(const Long &next) const
{
	return (this->first < next.first || (this->first == next.first && this->second < next.second));
}

bool Long::equal(const Long &next) const
{
	return (this->first == next.first && this->second == next.second);
}

int main()
{
	Long a, b;

	std::cout << "Введите первое число: ";
	a.read();
	std::cout << '\n';
	std::cout << "Введите второе число: ";
	b.read();
	std::cout << '\n';
	std::cout << '\n';

	std::cout << "Первое число: ";
	a.write();
	std::cout << '\n';
	std::cout << "Второе число: ";
	b.write();
	std::cout << '\n';
	std::cout << '\n';

	Long ans;

	ans = a.add(b);
	std::cout << "Сумма чисел: ";
	ans.write();
	std::cout << '\n';

	ans = a.sub(b);
	std::cout << "Разность чисел: ";
	ans.write();
	std::cout << '\n';

	ans = a.mult(b);
	std::cout << "Произведение чисел: ";
	ans.write();
	std::cout << '\n';

	ans = a.div(b);
	std::cout << "Частное чисел: ";
	ans.write();
	std::cout << '\n';
	std::cout << '\n';

	if (a.more(b))
		std::cout << "Первое число больше второго" << std::endl;

	if (a.less(b))
		std::cout << "Первое число меньше второго" << std::endl;

	if (a.equal(b))
		std::cout << "Числа равны" << std::endl;

	return 0;
}