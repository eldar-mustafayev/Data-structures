#pragma once
#include<iostream>

template<typename T>
class list
{
	public:
		struct node
		{
			node(T n=T(),node* prev=nullptr,node* next=nullptr) : value(n) , prev(prev) , next(next) { };
			T value;
			node *prev,*next;
		};
		class iterator
		{
			public:
				iterator(const iterator& a) : i(a.i) { };
				iterator(node* a=nullptr) : i(a) { };
				iterator& operator++();
				iterator operator++(int);
				iterator& operator--();
				iterator operator--(int);
				iterator operator+(int b) const;
				iterator operator-(int b) const;
				iterator& operator=(const iterator& a);
				T& operator*() { return i->value; }
				node*operator->() { return i; }
				node* _ptr() const { return i; }
				friend bool operator!=(iterator const &a,iterator const &b) { return a.i!=b.i; }
				friend bool operator==(iterator const &a,iterator const &b) { return a.i==b.i; }

			private:
				node* i;
		};
		list() : head(nullptr) , tail(nullptr) , size_(0) { };
		list(const list& a);
		list(const std::initializer_list<T>& a);
		void insert(const T& n,iterator prev);
		void push_back(const T& n);
		void push_front(const T& n);
		void erase(iterator cur);
		void pop_back();
		void pop_front();
		T& operator[](size_t n);
		bool empty() const { return size_==0; }
		size_t size() const { return size_; }
		iterator begin() const { return head; }
		iterator end() const { return nullptr; }
		iterator position(size_t n) const;
		~list();
	private:
		node *head,*tail;
		size_t size_;
};


template<typename T>
std::ostream& operator<<(std::ostream &a,const list<T> &b);










//iterator
template<typename T>
typename list<T>::iterator& list<T>::iterator::operator++()
{
	i=i->next;
	return *this;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator++(int)
{
	i=i->next;
	return i->prev;
}

template<typename T>
typename list<T>::iterator& list<T>::iterator::operator--()
{
	i=i->prev;
	return *this;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator--(int)
{
	i=i->prev;
	return i->next;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator+(int b) const
{
	iterator temp=*this;
	while(b--)
	{
		if(temp->next==nullptr)
		{
			std::cout<<"Iterator out of border\n";
			return nullptr;
		}
		temp=temp->next;
	}
	return temp;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator-(int b) const
{
	iterator temp=*this;
	while(b--)
	{
		if(temp->prev==nullptr)
		{
			std::cout<<"Iterator out of border\n";
			return nullptr;
		}
		temp=temp->prev;
	}
	return temp;
}

template<typename T>
typename list<T>::iterator& list<T>::iterator::operator=(const list<T>::iterator& a)
{
	i=a.i;
	return *this;
}


//list
template<typename T>
list<T>::list(const list<T>& a) : head(nullptr) , tail(nullptr) , size_(0)
{
    for(iterator i=a.begin();i!=a.end();++i)
        this->push_back(i->value);
}

template<typename T>
list<T>::list(const std::initializer_list<T>& a) : head(nullptr) , tail(nullptr) , size_(0)
{
    for(auto i=a.begin();i!=a.end();++i)
        this->push_back(*i);
}

template<typename T>
void list<T>::push_back(const T& n)
{
	if(tail==nullptr)
		tail=head=new node(n);
	else
		tail=tail->next=new node(n,tail);
	size_++;
}

template<typename T>
void list<T>::push_front(const T& n)
{
	if(head==nullptr)
		tail=head=new node(n);
	else
		head=head->prev=new node(n,nullptr,head);
	size_++;
}

template<typename T>
void list<T>::insert(const T& n,iterator pre)
{
	if(pre->next==nullptr)
	{
		push_back(n);
		return;
	}
	pre->next=pre->next->prev=new node(n,pre._ptr(),pre->next);
	size_++;
}

template<typename T>
void list<T>::pop_back()
{
	tail=tail->prev;
	delete tail->next;
	tail->next=nullptr;
	size_--;
}

template<typename T>
void list<T>::pop_front()
{
	head=head->next;
	delete head->prev;
	head->prev=nullptr;
	size_--;
}

template<typename T>
void list<T>::erase(iterator cur)
{
	if(cur==tail)
		pop_back();
	else if(cur==head)
		pop_front();
	else
	{
		cur->prev->next=cur->next;
		cur->next->prev=cur->prev;
		delete cur._ptr();
		size_--;
	}
}

template<typename T>
typename list<T>::iterator list<T>::position(size_t n) const
{
	return size_/2<=n ? iterator(tail)-(size_-n-1) : iterator(head)+n;
}

template<typename T>
T& list<T>::operator[](size_t n)
{
	return position(n)->value;
}

template<typename T>
list<T>::~list()
{
	node *next=head,*cur;
	while(next!=nullptr)
	{
		cur=next;
		next=cur->next;
		delete cur;
	}
}

template<typename T>
std::ostream& operator<<(std::ostream &a,const list<T>& b)
{
	a<<"[ "<<b.begin()->value;
	for(typename list<T>::iterator i=b.begin()+1;i!=b.end();++i)
		a<<", "<<i->value;
	a<<" ]";
	return a;
}
