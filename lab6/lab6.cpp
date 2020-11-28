///////////////
// by Dukend
///////////////
#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <queue>

template <class T>
class Vertex
{
public:
	T x, y;
};
template <class T>
std::istream &operator>>(std::istream &is, Vertex<T> &point)
{
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

template <class T>
double distance(const Vertex<T> &a, const Vertex<T> &b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

namespace allocators
{

	template <class T, size_t ALLOC_SIZE> //ALLOC_SIZE - размер, который требуется выделить
	struct my_allocator
	{

	private:
		char *pool_begin; //указатель на начало хранилища
		char *pool_end;	  //указатель на конец хранилища                    pool_begin       pool_tail                                pool_end
		char *pool_tail;  //указатель на конец заполненного пространства       |1000111010100101|----------------------------------------|
		std::queue<char *> free_blocks;

	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using is_always_equal = std::false_type;

		template <class U>
		struct rebind
		{
			using other = my_allocator<U, ALLOC_SIZE>;
		};

		my_allocator() : pool_begin(new char[ALLOC_SIZE]),
						 pool_end(pool_begin + ALLOC_SIZE),
						 pool_tail(pool_begin)
		{
		}

		my_allocator(const my_allocator &) = delete;
		my_allocator(my_allocator &&) = delete;

		~my_allocator()
		{
			delete[] pool_begin;
		}

		T *allocate(std::size_t n);
		void deallocate(T *ptr, std::size_t n);
	};

	template <class T, size_t ALLOC_SIZE>
	T *my_allocator<T, ALLOC_SIZE>::allocate(std::size_t n)
	{
		if (n != 1)
		{
			throw std::logic_error("can`t allocate arrays");
		}
		if (size_t(pool_end - pool_tail) < sizeof(T))
		{
			if (free_blocks.size())
			{ //ищем свободное место в райне отданном пространстве
				char *ptr = free_blocks.front();
				free_blocks.pop();
				return reinterpret_cast<T *>(ptr);
			}
			std::cout << "Bad Alloc" << std::endl;
			throw std::bad_alloc();
		}
		T *result = reinterpret_cast<T *>(pool_tail); //приведение к типу
		pool_tail += sizeof(T);
		return result;
	}

	template <class T, size_t ALLOC_SIZE>
	void my_allocator<T, ALLOC_SIZE>::deallocate(T *ptr, std::size_t n)
	{
		if (n != 1)
		{
			throw std::logic_error("can`t allocate arrays, thus can`t deallocate them too");
		}
		if (ptr == nullptr)
		{
			return;
		}
		free_blocks.push(reinterpret_cast<char *>(ptr));
	}

} // namespace allocators

namespace containers
{

	template <class T, class Allocator = std::allocator<T>>
	class list
	{
	private:
		struct element;	 //���������� ���� ����������� � list, ��� ����, ����� �� ��� ����� forward_iterator
		size_t size = 0; //������ ������
	public:
		list() = default; //���������� �� ���������

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
		using allocator_type = typename Allocator::template rebind<element>::other;

		struct deleter
		{
		private:
			allocator_type *allocator_;

		public:
			deleter(allocator_type *allocator) : allocator_(allocator) {}

			void operator()(element *ptr)
			{
				if (ptr != nullptr)
				{
					std::allocator_traits<allocator_type>::destroy(*allocator_, ptr);
					allocator_->deallocate(ptr, 1);
				}
			}
		};

		using unique_ptr = std::unique_ptr<element, deleter>;
		struct element
		{
			T value;
			unique_ptr next_element = {nullptr, deleter{nullptr}};
			element *prev_element = nullptr;
			element(const T &value_) : value(value_) {}
			forward_iterator next();
		};

		allocator_type allocator_{};
		unique_ptr first{nullptr, deleter{nullptr}};
		element *tail = nullptr;
	};

	template <class T, class Allocator>
	typename list<T, Allocator>::forward_iterator list<T, Allocator>::begin()
	{ //+
		return forward_iterator(first.get());
	}

	template <class T, class Allocator>
	typename list<T, Allocator>::forward_iterator list<T, Allocator>::end()
	{ //+
		return forward_iterator(nullptr);
	}
	template <class T, class Allocator>
	size_t list<T, Allocator>::length()
	{ //+
		return size;
	}
	template <class T, class Allocator>
	bool list<T, Allocator>::empty()
	{
		return length() == 0;
	}

	template <class T, class Allocator>
	void list<T, Allocator>::push_back(const T &value)
	{
		element *result = this->allocator_.allocate(1);
		std::allocator_traits<allocator_type>::construct(this->allocator_, result, value);
		if (!size)
		{
			first = unique_ptr(result, deleter{&this->allocator_});
			tail = first.get();
			size++;
			return;
		}
		tail->next_element = unique_ptr(result, deleter{&this->allocator_});
		element *temp = tail; //?
		tail = tail->next_element.get();
		tail->prev_element = temp; //?
		size++;
	}

	template <class T, class Allocator>
	void list<T, Allocator>::push_front(const T &value)
	{
		size++;
		element *result = this->allocator_.allocate(1);
		std::allocator_traits<allocator_type>::construct(this->allocator_, result, value);
		unique_ptr tmp = std::move(first);
		first = unique_ptr(result, deleter{&this->allocator_});
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

	template <class T, class Allocator>
	void list<T, Allocator>::pop_front()
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
		unique_ptr tmp = std::move(first->next_element);
		first = std::move(tmp);
		first->prev_element = nullptr;
		size--;
	}

	template <class T, class Allocator>
	void list<T, Allocator>::pop_back()
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

	template <class T, class Allocator>
	T &list<T, Allocator>::front()
	{
		if (size == 0)
		{
			throw std::logic_error("list is empty");
		}
		return first->value;
	}

	template <class T, class Allocator>
	T &list<T, Allocator>::back()
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
	template <class T, class Allocator>
	list<T, Allocator> &list<T, Allocator>::operator=(list<T, Allocator> &other)
	{
		size = other.size;
		first = std::move(other.first);
	}

	template <class T, class Allocator>
	void list<T, Allocator>::delete_by_it(containers::list<T, Allocator>::forward_iterator d_it)
	{
		forward_iterator i = this->begin(), end = this->end();
		if (d_it == end)
			throw std::logic_error("out of borders");
		if (d_it == this->begin())
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
		unique_ptr temp1 = std::move(d_it.it_ptr->next_element);
		d_it.it_ptr = d_it.it_ptr->prev_element;
		d_it.it_ptr->next_element = std::move(temp1);
		d_it.it_ptr->next_element->prev_element = temp;
		size--;
	}

	template <class T, class Allocator>
	void list<T, Allocator>::delete_by_number(size_t N)
	{
		forward_iterator it = this->begin();
		for (size_t i = 0; i < N; ++i)
		{
			++it;
		}
		this->delete_by_it(it);
	}

	template <class T, class Allocator>
	void list<T, Allocator>::insert_by_it(containers::list<T, Allocator>::forward_iterator ins_it, T &value)
	{

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
		element *tmp = this->allocator_.allocate(1);
		std::allocator_traits<allocator_type>::construct(this->allocator_, tmp, value);

		forward_iterator i = this->begin();

		tmp->prev_element = ins_it.it_ptr->prev_element;
		ins_it.it_ptr->prev_element = tmp;
		tmp->next_element = std::move(tmp->prev_element->next_element);
		tmp->prev_element->next_element = unique_ptr(tmp, deleter{&this->allocator_});

		size++;
	}

	template <class T, class Allocator>
	void list<T, Allocator>::insert_by_number(size_t N, T &value)
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
	template <class T, class Allocator>
	typename list<T, Allocator>::forward_iterator list<T, Allocator>::element::next()
	{
		return forward_iterator(this->next_element.get());
	}

	template <class T, class Allocator>
	list<T, Allocator>::forward_iterator::forward_iterator(containers::list<T, Allocator>::element *ptr)
	{
		it_ptr = ptr;
	}

	template <class T, class Allocator>
	T &list<T, Allocator>::forward_iterator::operator*()
	{
		return this->it_ptr->value;
	}
	template <class T, class Allocator>
	T &list<T, Allocator>::operator[](size_t index)
	{
		if (index < 0 || index >= size)
		{
			throw std::out_of_range("out of list's borders");
		}
		forward_iterator it = this->begin();
		for (size_t i = 0; i < index; i++)
		{
			it++;
		}
		return *it;
	}

	template <class T, class Allocator>
	typename list<T, Allocator>::forward_iterator &list<T, Allocator>::forward_iterator::operator++()
	{
		if (it_ptr == nullptr)
			throw std::logic_error("out of list borders");
		*this = it_ptr->next();
		return *this;
	}

	template <class T, class Allocator>
	typename list<T, Allocator>::forward_iterator list<T, Allocator>::forward_iterator::operator++(int)
	{
		forward_iterator old = *this;
		++*this;
		return old;
	}

	template <class T, class Allocator>
	bool list<T, Allocator>::forward_iterator::operator==(const forward_iterator &other) const
	{
		return it_ptr == other.it_ptr;
	}

	template <class T, class Allocator>
	bool list<T, Allocator>::forward_iterator::operator!=(const forward_iterator &other) const
	{
		return it_ptr != other.it_ptr;
	}
} // namespace containers

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
	std::cout << sizeof(Triangle<int>) << std::endl;
	containers::list<Triangle<int>, allocators::my_allocator<Triangle<int>, 500>> List;

	Triangle<int> TempTriangle;

	while (true)
	{
		Menu();
		int n, m, ind;
		double s;
		std::cin >> n;
		switch (n)
		{
		case 1:
			TempTriangle.read(std::cin);
			PushMenu();
			std::cin >> m;
			switch (m)
			{
			case 1:
				List.push_front(TempTriangle);
				break;
			case 2:
				List.push_back(TempTriangle);
				break;
			case 3:
				std::cin >> ind;
				List.insert_by_number(ind, TempTriangle);
			default:
				break;
			}
			break;
		case 2:
			DeleteMenu();
			std::cin >> m;
			switch (m)
			{
			case 1:
				List.pop_front();
				break;
			case 2:
				List.pop_back();
				break;
			case 3:
				std::cin >> ind;
				List.delete_by_number(ind);
				break;
			default:
				break;
			}
			break;
		case 3:
			PrintMenu();
			std::cin >> m;
			switch (m)
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
				std::cin >> ind;
				List[ind].print(std::cout);
				std::cout << std::endl;
				break;
			default:
				break;
			}
			break;
		case 4:
			std::for_each(List.begin(), List.end(), [](Triangle<int> &X) { X.print(std::cout); std::cout << std::endl; });
			break;
		case 5:
			std::cin >> s;
			std::cout << std::count_if(List.begin(), List.end(), [=](Triangle<int> &X) { return X.area() > s; }) << std::endl;
			break;
		case 6:
			exit(0);
		default:
			return 0;
		}
	}
	return 0;
}