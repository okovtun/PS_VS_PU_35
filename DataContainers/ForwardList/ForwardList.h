#pragma once
#include<iostream>

template<typename T>class ForwardList
{
	class Element
	{
		T Data;
		Element* pNext;
		static int count;
	public:
		const T getData()const;
		const Element* getNext()const;
		Element(T Data, Element* pNext = nullptr);
		~Element();
		friend class ForwardList;
	};

	Element* Head;
	int size;
public:

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp);
		Iterator(const Iterator& other);
		~Iterator();

		const T& operator*() const;
		T& operator*();

		Iterator& operator++();
		Iterator operator++(int);

		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
	};

	const Iterator begin()const;
	const Iterator end()const;

	int get_size()const;

	ForwardList();
	explicit ForwardList(int size);
	ForwardList(std::initializer_list<T> il);
	ForwardList(const ForwardList& that);
	ForwardList(ForwardList&& other);
	~ForwardList();

	//				Operators:

	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator=(ForwardList<T>&& other);

	T& operator[](int index);

	//				Methods:
	void push_front(T Data);
	void push_back(T Data);
	void insert(int Index, T Data);

	void pop_front();
	void pop_back();
	void erase(int index);

	//			methods:
	void print();

	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};