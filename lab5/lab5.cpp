///////////////
// by Dukend
///////////////
#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <cmath>

template <class T>
class Vertex
{
public:
	T x, y;
};

template <class T>
std::istream &operator>>(std::istream &is, Vertex<T> &point)
{
	std::cout << "Points:" << std::endl;
	is >> point.x >> point.y;
	return is;
}

template <class T>
std::ostream &operator<<(std::ostream &os, Vertex<T> point)
{
	os << '[' << point.x << ",  " << point.y << ']';
	return os;
}

template <class T>
Vertex<T> operator+(const Vertex<T> &a, const Vertex<T> &b)
{
	Vertex<T> res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}

template <class T>
Vertex<T> operator+=(Vertex<T> &a, const Vertex<T> &b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

/////////////////////////////

namespace container
{

	template <class T>
	class list
	{
	private:
		struct element;
		size_t size = 0;

	public:
		list() = default;
		class forward_iterator
		{
		public:
			using value_type = T;
			using reference = value_type &;
			using pointer = value_type *;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;
			explicit forward_iterator(element *ptr);
			T &operator*();
			forward_iterator &operator++();
			forward_iterator operator++(int);
			bool operator==(const forward_iterator &other) const;
			bool operator!=(const forward_iterator &other) const;

		private:
			element *it_ptr;
			friend list;
		};

		forward_iterator begin();
		forward_iterator end();
		void push_back(const T &value);
		void push_front(const T &value);
		T &front();
		T &back();
		void pop_back();
		void pop_front();
		size_t length();
		bool empty();
		void delete_by_it(forward_iterator d_it);
		void delete_by_number(size_t N);
		void insert_by_it(forward_iterator ins_it, T &value);
		void insert_by_number(size_t N, T &value);
		list &operator=(list &other);
		T &operator[](size_t index);

	private:
		struct element
		{
			T value;
			std::unique_ptr<element> next_element;
			element *prev_element = nullptr;
			element(const T &value_) : value(value_) {}
			forward_iterator next();
		};
		std::unique_ptr<element> first;
		element *tail = nullptr;
	};

	template <class T>
	size_t list<T>::length()
	{
		return size;
	}
	template <class T>
	bool list<T>::empty()
	{
		return length() == 0;
	}
	template <class T>
	typename list<T>::forward_iterator list<T>::begin()
	{
		return forward_iterator(first.get());
	}

	template <class T>
	typename list<T>::forward_iterator list<T>::end()
	{
		return forward_iterator(nullptr);
	}
	template <class T>
	void list<T>::push_front(const T &value)
	{
		size++;
		std::unique_ptr<element> tmp = std::move(first);
		first = std::make_unique<element>(value);
		first->next_element = std::move(tmp);
		if (first->next_element != nullptr)
			first->next_element->prev_element = first.get();
		if (size == 1)
		{
			tail = first.get();
		}
		if (size == 2)
		{
			tail = first->next_element.get();
		}
	}
	template <class T>
	void list<T>::push_back(const T &value)
	{
		if (!size)
		{
			first = std::make_unique<element>(value);
			tail = first.get();
			size++;
			return;
		}
		tail->next_element = std::make_unique<element>(value);
		element *temp = tail;
		tail = tail->next_element.get();
		tail->prev_element = temp;
		size++;
	}

	template <class T>
	void list<T>::pop_front()
	{
		if (size == 0)
		{
			throw std::logic_error("can`t pop from empty list");
		}
		if (size == 1)
		{
			first = nullptr;
			tail = nullptr;
			size--;
			return;
		}
		std::unique_ptr<element> tmp = std::move(first->next_element);
		first = std::move(tmp);
		first->prev_element = nullptr;
		size--;
	}

	template <class T>
	void list<T>::pop_back()
	{
		if (size == 0)
		{
			throw std::logic_error("can`t pop from empty list");
		}
		if (tail->prev_element)
		{
			element *tmp = tail->prev_element;
			tail->prev_element->next_element = nullptr;
			tail = tmp;
		}
		else
		{
			first = nullptr;
			tail = nullptr;
		}
		size--;
	}

	template <class T>
	T &list<T>::front()
	{
		if (size == 0)
		{
			throw std::logic_error("list is empty");
		}
		return first->value;
	}

	template <class T>
	T &list<T>::back()
	{
		if (size == 0)
		{
			throw std::logic_error("list is empty");
		}
		forward_iterator i = this->begin();
		while (i.it_ptr->next() != this->end())
		{
			i++;
		}
		return *i;
	}
	template <class T>
	list<T> &list<T>::operator=(list<T> &other)
	{
		size = other.size;
		first = std::move(other.first);
	}

	template <class T>
	void list<T>::delete_by_it(container::list<T>::forward_iterator d_it)
	{
		forward_iterator begin = this->begin(), end = this->end();
		if (d_it == end)
			throw std::logic_error("out of borders");
		if (d_it == begin)
		{
			this->pop_front();
			return;
		}
		if (d_it.it_ptr == tail)
		{
			this->pop_back();
			return;
		}
		if (d_it.it_ptr == nullptr)
			throw std::logic_error("out of broders");
		auto temp = d_it.it_ptr->prev_element;
		std::unique_ptr<element> temp1 = std::move(d_it.it_ptr->next_element);
		d_it.it_ptr = d_it.it_ptr->prev_element;
		d_it.it_ptr->next_element = std::move(temp1);
		d_it.it_ptr->next_element->prev_element = temp;
		size--;
	}

	template <class T>
	void list<T>::delete_by_number(size_t N)
	{
		forward_iterator it = this->begin();
		for (size_t i = 0; i < N; ++i)
		{
			++it;
		}
		this->delete_by_it(it);
	}

	template <class T>
	void list<T>::insert_by_it(container::list<T>::forward_iterator ins_it, T &value)
	{
		std::unique_ptr<element> tmp = std::make_unique<element>(value);
		if (ins_it == this->begin())
		{
			this->push_front(value);
			return;
		}
		if (ins_it.it_ptr == nullptr)
		{
			this->push_back(value);
			return;
		}

		tmp->prev_element = ins_it.it_ptr->prev_element;
		ins_it.it_ptr->prev_element = tmp.get();
		tmp->next_element = std::move(tmp->prev_element->next_element);
		tmp->prev_element->next_element = std::move(tmp);

		size++;
	}

	template <class T>
	void list<T>::insert_by_number(size_t N, T &value)
	{
		forward_iterator it = this->begin();
		if (N >= this->length())
			it = this->end();
		else
			for (size_t i = 0; i < N; ++i)
			{
				++it;
			}
		this->insert_by_it(it, value);
	}
	template <class T>
	typename list<T>::forward_iterator list<T>::element::next()
	{
		return forward_iterator(this->next_element.get());
	}

	template <class T>
	list<T>::forward_iterator::forward_iterator(container::list<T>::element *ptr)
	{
		it_ptr = ptr;
	}

	template <class T>
	T &list<T>::forward_iterator::operator*()
	{
		return this->it_ptr->value;
	}
	template <class T>
	T &list<T>::operator[](size_t index)
	{
		if (index < 0 || index >= size)
		{
			throw std::out_of_range("out of list");
		}
		forward_iterator it = this->begin();
		for (size_t i = 0; i < index; i++)
		{
			it++;
		}
		return *it;
	}

	template <class T>
	typename list<T>::forward_iterator &list<T>::forward_iterator::operator++()
	{
		if (it_ptr == nullptr)
			throw std::logic_error("out of list");
		*this = it_ptr->next();
		return *this;
	}

	template <class T>
	typename list<T>::forward_iterator list<T>::forward_iterator::operator++(int)
	{
		forward_iterator old = *this;
		++*this;
		return old;
	}

	template <class T>
	bool list<T>::forward_iterator::operator==(const forward_iterator &other) const
	{
		return it_ptr == other.it_ptr;
	}

	template <class T>
	bool list<T>::forward_iterator::operator!=(const forward_iterator &other) const
	{
		return it_ptr != other.it_ptr;
	}
} // namespace container

/////////////////////////////
template <class T>
class Triangle
{
private:
	Vertex<T> Vertexs[4];

public:
	using vertex_type = Vertex<T>;
	Triangle() = default;
	Triangle(std::istream &in);
	void read(std::istream &in);
	double area() const;
	void print(std::ostream &os) const;
	friend std::ostream &operator<<(std::ostream &out, Triangle<T> &point);
	friend std::istream &operator>>(std::istream &in, Triangle<T> &point);
};

template <class T>
Triangle<T>::Triangle(std::istream &in)
{
	for (int i = 0; i < 3; i++)
		in >> Vertexs[i];
}
template <class T>
double Triangle<T>::area() const
{
	double res = 0;
	for (int i = 0; i <= 1; i++)
		res += (Vertexs[i].x * Vertexs[i + 1].y - Vertexs[i + 1].x * Vertexs[i].y);
	res += (Vertexs[2].x * Vertexs[0].y - Vertexs[0].x * Vertexs[2].y);
	res = 0.5 * std::abs(res);

	return res;
}

template <class T>
void Triangle<T>::print(std::ostream &os) const
{
	os << "Triangle: " << std::endl;
	for (int i = 0; i < 3; i++)
		os << Vertexs[i] << " ";
	os << "\nArea: " << area() << "\n";
}

template <class T>
void Triangle<T>::read(std::istream &in)
{
	Triangle<T> res = Triangle(in);
	*this = res;
}

////////////////////////////

void Menu()
{
	std::cout << "1. Add shape to list\n";
	std::cout << "2. Delete shape\n";
	std::cout << "3. Display shape\n";
	std::cout << "4. Display all shapes\n";
	std::cout << "5. Display the number of figures whose area is greater than ...\n";
	std::cout << "6. Exit\n\n";
}
void PrintMenu()
{
	std::cout << "1. Print the first figure in the list\n";
	std::cout << "2. Print the last figure in the list\n";
	std::cout << "3. Display the figure at index\n\n";
}

void PushMenu()
{
	std::cout << "1. Add shape to the beginning of the list\n";
	std::cout << "2. Add shape to the end of the list\n";
	std::cout << "3. Add shape by index\n\n";
}

void DeleteMenu()
{
	std::cout << "1. Remove shape at the top of the list\n";
	std::cout << "2. Remove shape at the end of the list\n";
	std::cout << "3. Delete shape by index\n\n";
}

int main()
{
	Triangle<int> TmpShape;
	container::list<Triangle<int>> List;
	while (true)
	{
		Menu();
		int com, index;
		double area;
		std::cin >> com;
		switch (com)
		{
		case 1:
			TmpShape.read(std::cin);
			PushMenu();
			std::cin >> com;
			switch (com)
			{
			case 1:
				List.push_front(TmpShape);
				break;
			case 2:
				List.push_back(TmpShape);
				break;
			case 3:
				std::cin >> index;
				List.insert_by_number(index, TmpShape);
			default:
				break;
			}
			break;
		case 2:
			DeleteMenu();
			std::cin >> com;
			switch (com)
			{
			case 1:
				List.pop_front();
				break;
			case 2:
				List.pop_back();
				break;
			case 3:
				std::cin >> index;
				List.delete_by_number(index);
				break;
			default:
				break;
			}
			break;
		case 3:
			PrintMenu();
			std::cin >> com;
			switch (com)
			{
			case 1:
				List.front().print(std::cout);
				std::cout << std::endl;
				break;
			case 2:
				List.back().print(std::cout);
				std::cout << std::endl;
				break;
			case 3:
				std::cin >> index;
				List[index].print(std::cout);
				std::cout << std::endl;
				break;
			default:
				break;
			}
			break;
		case 4:
			std::cout << List.length() << std::endl;
			std::for_each(List.begin(), List.end(), [](Triangle<int> &Shape) { Shape.print(std::cout); std::cout << std::endl; });
			break;
		case 5:
			std::cin >> area;
			std::cout << std::count_if(List.begin(), List.end(), [=](Triangle<int> &Shape) { return Shape.area() > area; }) << std::endl;
			break;
		case 6:
			exit(0);
		default:
			std::cout << "Unidentified command.\n"
					  << std::endl;
			break;
		}
	}
	return 0;
}
