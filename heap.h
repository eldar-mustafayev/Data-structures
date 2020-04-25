#include<utility>
#include<cstddef>

//definition
template<typename T>
class heap
{
	public:
		heap(size_t n_childs = 2) : arr(nullptr), n_childs(n_childs), _size_(0), _max_size_(1) { }

		void push(const T& a);

		void pop();

		void replace(const T& a);
	
		void reserve(size_t n);
	
		size_t size() { return _size_; }

		T top() const { return arr[0]; }
	
		bool empty() { return _size_ == 0; }

		~heap() { delete[] arr; }

	private:
		void arrange() { reserve(_max_size_ << 1); };

		void shiftup(size_t i);

		void shiftdown(size_t i);

		T* arr;
		size_t n_childs, _size_, _max_size_;
};


//implementation
template<typename T>
void heap<T>::reserve(size_t n)
{
	_max_size_ = n;
	T* temp = new T[_max_size_];

	for (size_t i = 0; i < _size_; i++)
		temp[i] = arr[i];

	delete[] arr;
	arr = temp;
}

template<typename T>
void heap<T>::shiftup(size_t i)
{
	static size_t parent;
	while (true)
	{
		parent = (i - 1) / n_childs;
		if (i > 0 and arr[i] < arr[parent])
		{
			std::swap(arr[parent], arr[i]);
			i = parent;
		}
		else
			break;
	}
}

template<typename T>
void heap<T>::shiftdown(size_t i)
{
	static size_t index, child;
	index = i;
	while (true)
	{
		for (size_t k = 1; k <= n_childs; ++k)
		{
			child = i * n_childs + k;
			if (child < _size_ and arr[child] < arr[index])
				index = child;
		}

		if (i != index)
		{
			std::swap(arr[i], arr[index]);
			i = index;
		}
		else
			break;
	}
}

template<typename T>
void heap<T>::push(const T& a)
{
	if (_size_ + 1 >= _max_size_)
		arrange();

	arr[_size_++] = a;
	shiftup(_size_ - 1);
}

template<typename T>
void heap<T>::pop()
{
	std::swap(arr[0], arr[--_size_]);
	shiftdown(0);
}

template<typename T>
void heap<T>::replace(const T& a)
{
	arr[0] = a;
	shiftdown(0);
}

int main()
{
    heap<int> a;
}
