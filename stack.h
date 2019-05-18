#pragma once
#include<iostream>

template<typename T>
class stack
{
	public:
		struct node
		{
			node(T n=T(),node* next=nullptr) : value(n) , next(next) { };
			T value;
			node *next;
			~node() { delete next; }
		};
		stack() : head(nullptr) , size_(0) { };
		void push(const T& n);
		void pop();
		T& top() { return head->value; }
		bool empty() const { return size_==0; }
		size_t size() const { return size_; }
		~stack() { delete head; }
	private:
		node *head;
		size_t size_;
};












//stack

template<typename T>
void stack<T>::push(const T& n)
{
	if(head==nullptr)
		head=new node(n);
	else
		head=new node(n,head);
	size_++;
}


template<typename T>
void stack<T>::pop()
{
    node* temp=head->next;
    head->next=nullptr;
	delete head;
	head=temp;
	size_--;
}
