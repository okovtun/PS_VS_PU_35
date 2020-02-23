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

///////////////////////////////////// ELEMENT //////////////////////////////////////////////

template<typename T>int ForwardList<T>::Element::count = 0;

template<typename T>
const T ForwardList<T>::Element::getData()const
{
	return this->Data;
}

template<typename T>
typename const ForwardList<T>::Element* ForwardList<T>::Element::getNext()const
{
	return this->pNext;
}

template<typename T>
ForwardList<T>::Element::Element(T Data, Element* pNext)
{
	this->Data = Data;
	this->pNext = pNext;
	count++;
	std::cout << "EConstructor:\t" << this << std::endl;
}
template<typename T>
ForwardList<T>::Element::~Element()
{
	count--;
	std::cout << "EDestructor:\t" << this << std::endl;
}


////////////////////////////////////// ITERATOR ///////////////////////////////////////

template<typename T>
ForwardList<T>::Iterator::Iterator(Element* Temp)
{
	this->Temp = Temp;
#ifdef DEBUG_IT
	std::cout << "ItConstructor:\t" << this << std::endl;
#endif // DEBUG_IT
}
template<typename T>
ForwardList<T>::Iterator::Iterator(const Iterator& other)
{
	this->Temp = other.Temp;
#ifdef DEBUG_IT
	std::cout << "ItConstructor:\t" << this << std::endl;
#endif // DEBUG_IT
}
template<typename T>
ForwardList<T>::Iterator::~Iterator()
{
#ifdef DEBUG_IT
	std::cout << "ItDestructor:\t" << this << std::endl;
#endif // DEBUG_IT
}

template<typename T>
const T& ForwardList<T>::Iterator::operator*() const
{
	return Temp->Data;
}
template<typename T>
T& ForwardList<T>::Iterator::operator*()
{
	return Temp->Data;
}
template<typename T>
typename ForwardList<T>::Iterator& ForwardList<T>::Iterator::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::Iterator::operator++(int)
{
	Iterator old = *this;
	if (Temp)Temp = Temp->pNext;
	return old;
}
template<typename T>
bool ForwardList<T>::Iterator::operator==(const Iterator& other) const
{
	return this->Temp == other.Temp;
}
template<typename T>
bool ForwardList<T>::Iterator::operator!=(const Iterator& other) const
{
	return this->Temp != other.Temp;
}

///////////////////////////////////// FORWARD_LIST ////////////////////////////////////

template<typename T>
typename const ForwardList<T>::Iterator ForwardList<T>::begin() const
{
	return Head;
}

template<typename T>
typename const ForwardList<T>::Iterator ForwardList<T>::end() const
{
	return nullptr;
}

template<typename T>
int ForwardList<T>::get_size()const
{
	return size;
}

template<typename T>
ForwardList<T>::ForwardList()
{
	this->Head = nullptr;
	this->size = 0;
	std::cout << "LConstructor:\t" << this << std::endl;
}
template<typename T>
ForwardList<T>::ForwardList(int size) :ForwardList()
{
	while (size--)push_front(0);
	std::cout << "LConstructor:\t" << this << std::endl;
}
template<typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> il) :ForwardList()
{
	std::cout << typeid(il.begin()).name() << std::endl;
	for (T const *it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
	std::cout << "ILconstructor:\t" << this << std::endl;
}
template<typename T>
ForwardList<T>::ForwardList(const ForwardList& that) :ForwardList()
{
	/*Element* Temp = that.Head;
	while (Temp)
	{
		push_back(Temp->Data);
		Temp = Temp->pNext;
	}*/
	for (Element* Temp = that.Head; Temp != nullptr; Temp = Temp->pNext)push_back(Temp->Data);
	std::cout << "CopyConstructor:\t" << this << std::endl;
}
template<typename T>
ForwardList<T>::ForwardList(ForwardList&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	other.Head = nullptr;
	std::cout << "MoveConstructor:\t" << this << std::endl;
}
template<typename T>
ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();
	std::cout << "LDestructor:\t" << this << std::endl;
}

//				Operators:
template<typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	std::cout << "CopyAssignment:\t" << this << std::endl;
	return *this;
}
template<typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	other.Head = nullptr;
	std::cout << "MoveAssignment:\t" << this << std::endl;
	return *this;
}

template<typename T>
T& ForwardList<T>::operator[](int index)
{
	Element* Temp = Head;
	for (int i = 0; i < index; i++)Temp = Temp->pNext;
	return Temp->Data;
}

//				Methods:
template<typename T>
void ForwardList<T>::push_front(T Data)
{
	Element* New = new Element(Data);
	New->pNext = Head;
	Head = New;
	size++;
}
template<typename T>
void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr)
	{
		push_front(Data);
		return;
	}
	Element* Temp = Head;
	while (Temp->pNext != nullptr)
	{
		Temp = Temp->pNext;
	}
	Element* New = new Element(Data);
	Temp->pNext = New;
	size++;
}
template<typename T>
void ForwardList<T>::insert(int Index, T Data)
{
	if (Index == 0)
	{
		push_front(Data);
		return;
	}
	if (Index > size)
	{
		std::cout << "Error: Out of range" << std::endl;
		return;
	}
	//1) Создаем элемент:
	Element* New = new Element(Data);
	//2) Доходим до нужной позиции в списке:
	Element* Temp = Head;
	for (int i = 0; i < Index - 1; i++)
	{
		Temp = Temp->pNext;
	}
	//3) Вставляем новый элемент в список:
	New->pNext = Temp->pNext;
	Temp->pNext = New;
	size++;
}
template<typename T>
void ForwardList<T>::pop_front()
{
	Element* Temp = Head;
	Head = Head->pNext;
	delete Temp;
	size--;
}
template<typename T>
void ForwardList<T>::pop_back()
{
	//Удаление элемента с конца списка.
	Element* Temp = Head;
	while (Temp->pNext->pNext != nullptr)
	{
		Temp = Temp->pNext;
	}
	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}
template<typename T>
void ForwardList<T>::erase(int index)
{
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index >= size)
	{
		std::cout << "Error: Out of range" << std::endl;;
		return;
	}
	/*if (index == size - 1)
	{
		pop_back();
		return;
	}*/
	Element* Temp = Head;
	for (int i = 0; i < index - 1; i++)
	{
		Temp = Temp->pNext;
	}
	Element* buffer = Temp->pNext;
	Temp->pNext = Temp->pNext->pNext;
	delete buffer;
	size--;
}

//			methods:
template<typename T>
void ForwardList<T>::print()
{
	std::cout << "\n-------------------------------------\n";
	std::cout << "Head:\t" << Head << std::endl;
	//Element* Temp = Head;	//Temp - это итератор.
	//						//Итератор - это указатель, при помощи которого 
	//						//можно получить доступ к элементам структуры данных.
	//while (Temp != nullptr)
	//{
	//	std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	//	Temp = Temp->pNext;	//Переход на следующий элемент.
	//}

	for (Element* Temp = Head; Temp; Temp=Temp->pNext)
	{
		std::cout << Temp << "\t" << Temp->getData() << "\t" << Temp->pNext << std::endl;
	}
	/*for (Iterator it = Head;
		it != nullptr;
		++it)
	{
		std::cout << *it << "\t";
	}*/
	std::cout << std::endl;

	std::cout << "List size:\t" << size << std::endl;
	std::cout << "\n-------------------------------------\n";
}

template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;
	/*for (const ForwardList::Element* Temp = right.Head; Temp; Temp = Temp->getNext())
	{
		cat.push_back(Temp->getData());
	}*/
	std::cout << "Global operator +" << std::endl;
	return cat;
}

void print(int arr[])
{
	std::cout << sizeof(arr) << std::endl;
	std::cout << typeid(arr).name() << std::endl;
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;

	/*for (int i : arr)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;*/
}

//#define BASE_CHECK
//#define OPERATORS_AND_CONSTRUCTORS_CHECK
#define RANGE_BASED_FOR

void main()
{
	setlocale(LC_ALL, "");

	int n;
	//std::cout << "Input list size: "; std::cin >> n;
#ifdef BASE_CHECK
	ForwardList fl;
	for (int i = 0; i < n; i++)
	{
		fl.push_back(rand() % 100);
	}
	//fl.push_back(123);
	fl.print();

	int index;
	int data;

	/*std::cout << "Input index: "; std::cin >> index;
	std::cout << "Input value: "; std::cin >> data;
	fl.insert(index, data);
	fl.print();*/

	/*fl.pop_front();
	fl.pop_back();
	fl.print();*/

	/*std::cout << "Input index: "; std::cin >> index;
	fl.erase(index);
	fl.print();*/
#endif // BASE_CHECK

	/*int a = 2;
	double b = 3;
	ForwardList list1(5);
	for (int i = 0; i < n; i++)
	{
		list1[i] = rand() % 100;
	}
	for (int i = 0; i < n; i++)
	{
		std::cout << list1[i] << "\t";
	}
	std::cout << std::endl;*/

#ifdef OPERATORS_AND_CONSTRUCTORS_CHECK
	ForwardList list1 = { 3, 5, 8, 13, 21 };
	list1.print();

	ForwardList list2 = { 34, 55, 89 };
	list2.print();

	std::cout << "\n---------------------------------------------\n";
	ForwardList list3;
	list3 = list1 + list2;
	std::cout << "\n---------------------------------------------\n";
	for (int i = 0; i < list3.get_size(); i++)std::cout << list3[i] << "\t";
	std::cout << std::endl;

	/*ForwardList list2;
	list2 = list1;
	list2.print();*/
#endif // OPERATORS_AND_CONSTRUCTORS_CHECK

	/*int arr[] = { 3, 5, 8, 13, 21 };
	std::cout << sizeof(arr) << std::endl;
	std::cout << typeid(arr).name() << std::endl;
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;

	for (int i : arr)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;

	print(arr);*/

#ifdef RANGE_BASED_FOR
	//ForwardList<int> list = { 3, 5, 8, 13, 21 };
	ForwardList<double> list = { 2.7, 3.14, 5.4, 8.3 };
	//list.print();
	for (ForwardList<double>::Iterator it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
	for (double i : list)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;
	list.print();
#endif
}