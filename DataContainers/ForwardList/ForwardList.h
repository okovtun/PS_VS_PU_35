#pragma once
#include<iostream>

//				Class Declaration

class ForwardList
{
	class Element
	{
		int Data;
		Element* pNext;
		static int count;
	public:
		const int getData()const;
		const Element* getNext()const;
		Element(int Data, Element* pNext = nullptr);
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
		~Iterator();

		const int& operator*() const;
		int& operator*();

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
	ForwardList(std::initializer_list<int> il);
	ForwardList(const ForwardList& that);
	ForwardList(ForwardList&& other);
	~ForwardList();

	//				Operators:

	ForwardList& operator=(const ForwardList& other);
	ForwardList& operator=(ForwardList&& other);

	int& operator[](int index);

	//				Methods:
	void push_front(int Data);
	void push_back(int Data);
	void insert(int Index, int Data);

	void pop_front();
	void pop_back();
	void erase(int index);

	//			methods:
	void print();

	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};