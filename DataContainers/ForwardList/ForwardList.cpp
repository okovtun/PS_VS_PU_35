#include"ForwardList.h"

//				Class Definition

//////////////////////ELEMENT//////////////////////////////////////

int ForwardList::Element::count = 0;

const int ForwardList::Element::getData()const
{
	return this->Data;
}
const ForwardList::Element* ForwardList::Element::getNext()const
{
	return this->pNext;
}
ForwardList::Element::Element(int Data, Element* pNext)
{
	this->Data = Data;
	this->pNext = pNext;
	count++;
#ifdef DEBUG
	std::cout << "EConstructor:\t" << this << std::endl;
#endif // DEBUG

}
ForwardList::Element::~Element()
{
	count--;
#ifdef DEBUG
	std::cout << "EDestructor:\t" << this << std::endl;
#endif // DEBUG

}

/////////////////////////////ITERATOR//////////////////////////////////////


ForwardList::Iterator::Iterator(Element* Temp)
{
	this->Temp = Temp;
#ifdef DEBUG_IT
	std::cout << "ItConstructor:\t" << this << std::endl;
#endif // DEBUG_IT

}

ForwardList::Iterator::~Iterator()
{
#ifdef DEBUG_IT
	std::cout << "ItDestructor:\t" << this << std::endl;
#endif // DEBUG_IT
}

const int& ForwardList::Iterator::operator*() const
{
	return Temp->Data;
}
int& ForwardList::Iterator::operator*()
{
	return Temp->Data;
}

ForwardList::Iterator& ForwardList::Iterator::operator++()
{
	Temp = Temp->pNext;
	return *this;
}

ForwardList::Iterator ForwardList::Iterator::operator++(int)
{
	Iterator old = *this;
	if (Temp)Temp = Temp->pNext;
	return old;
}

bool ForwardList::Iterator::operator==(const Iterator& other) const
{
	return this->Temp == other.Temp;
}
bool ForwardList::Iterator::operator!=(const Iterator& other) const
{
	return this->Temp != other.Temp;
}

/////////////////////////////////////FORWARD_LIST//////////////////////////////////////////

const ForwardList::Iterator ForwardList::begin()const
{
	//Возвращает итератор на начало контейнера
	return Head;
}
const ForwardList::Iterator ForwardList::end()const
{
	//Возвращает итератор на конец контейнера
	return nullptr;
}

int ForwardList::get_size()const
{
	return size;
}
ForwardList::ForwardList()
{
	this->Head = nullptr;
	this->size = 0;
	std::cout << "LConstructor:\t" << this << std::endl;
}
ForwardList::ForwardList(int size) :ForwardList()
{
	while (size--)push_front(0);
	std::cout << "LConstructor:\t" << this << std::endl;
}
ForwardList::ForwardList(std::initializer_list<int> il) : ForwardList()
{
	std::cout << typeid(il.begin()).name() << std::endl;
	for (int const *it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
	std::cout << "ILconstructor:\t" << this << std::endl;
}
ForwardList::ForwardList(const ForwardList& that) :ForwardList()
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
ForwardList::ForwardList(ForwardList&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	other.Head = nullptr;
	std::cout << "MoveConstructor:\t" << this << std::endl;
}
ForwardList::~ForwardList()
{
	while (Head)pop_front();
	std::cout << "LDestructor:\t" << this << std::endl;
}

//				Operators:

ForwardList& ForwardList::operator=(const ForwardList& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	std::cout << "CopyAssignment:\t" << this << std::endl;
	return *this;
}
ForwardList& ForwardList::operator=(ForwardList&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	other.Head = nullptr;
	std::cout << "MoveAssignment:\t" << this << std::endl;
	return *this;
}

int& ForwardList::operator[](int index)
{
	Element* Temp = Head;
	for (int i = 0; i < index; i++)Temp = Temp->pNext;
	return Temp->Data;
}

//				Methods:
void ForwardList::push_front(int Data)
{
	Element* New = new Element(Data);
	New->pNext = Head;
	Head = New;
	size++;
}
void ForwardList::push_back(int Data)
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
void ForwardList::insert(int Index, int Data)
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

void ForwardList::pop_front()
{
	Element* Temp = Head;
	Head = Head->pNext;
	delete Temp;
	size--;
}

void ForwardList::pop_back()
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

void ForwardList::erase(int index)
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
void ForwardList::print()
{
	std::cout << "\n-------------------------------------\n";
	std::cout << "Head:\t" << Head << std::endl;

	for (Iterator it = Head;
		it != nullptr;
		++it)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;

	std::cout << "List size:\t" << size << std::endl;
	std::cout << "\n-------------------------------------\n";
}

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	for (const ForwardList::Element* Temp = right.Head; Temp; Temp = Temp->getNext())
	{
		cat.push_back(Temp->getData());
	}
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