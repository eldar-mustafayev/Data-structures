#include<cstdlib>
#include<algorithm>
#include<iostream>
template<typename T>
class heap
{
	public:
		heap() : arr(nullptr) , size(0) , maxsize(1) { }
		void insert(const T& a);
		void remove(size_t i);
		size_t parent(size_t i) const { return (i-1)/2; }
		size_t leftchild(size_t i) const { return 2*i+1; }
		size_t rightchild(size_t i) const { return 2*i+2; }
		void extractmax() { remove(0); }
		void shiftup(size_t i);
		static void shiftdown(T* arr,const size_t& size,size_t i);
		void changepriority(size_t i,const T& a);
		T getmax() const;
		~heap() { delete[] arr; }
	private:
		void arrange();

		T* arr;
		size_t size,maxsize;
};

template<typename T,size_t N>
T* heapsort(T (&a)[N],size_t k=N);











template<typename T>
void heap<T>::insert(const T& a)
{
	if(size+1>=maxsize)
		arrange();
	arr[size++]=a;
	shiftup(size-1);
}


template<typename T>
void heap<T>::shiftup(size_t i)
{
    size_t parent;
    while(true)
    {
        parent=(i-1)/2;
        if(i>0 and arr[i]<arr[parent])
        {
            std::swap(arr[parent],arr[i]);
            i=parent;
        }
        else
            break;
    }
}


template<typename T>
void heap<T>::shiftdown(T* arr,const size_t& size,size_t i)
{
	size_t index=i,child;
	while(true)
	{
		child=2*i+1;
		if(child<size and arr[child]>arr[index])
			index=child;
		child=2*i+2;
		if(child<size and arr[child]>arr[index])
			index=child;
		if(i!=index)
		{
			std::swap(arr[i],arr[index]);
			i=index;
		}
		else
			break;
	}
}


template<typename T>
T heap<T>::getmax() const
{
	if(!size)
		exit(-1);
	return arr[0];
}


template<typename T>
void heap<T>::remove(size_t i)
{
    if(!size)
        exit(-1);
    std::swap(arr[i],arr[--size]);
    shiftdown(arr,size,i);
}


template<typename T>
void heap<T>::changepriority(size_t i,const T& a)
{
    arr[i]=a;
    if(arr[parent(i)]<a)
        shiftup(i);
    else
        shiftdown(arr,size,i);
}


template<typename T>
void heap<T>::arrange()
{
	T* temp=new T[maxsize*=2];
	for(size_t i=0;i<size;i++)
		temp[i]=arr[i];
	delete[] arr;
	arr=temp;
}


template<typename T,size_t N>
T* heapsort(T (&a)[N],size_t k)
{
	size_t size=N;
	for(size_t i=size/2;i>0;--i)
		heap<T>::shiftdown(a,size,i-1);

	while(k--)
	{
		std::swap(a[0],a[--size]);
		heap<T>::shiftdown(a,size,0);
	}

	return a+size;
}
