// Basic singly-linked list.
// 7.19.2018 JME

#ifndef SL_LIST_H
#define SL_LIST_H

#include <iostream>
#include <iterator>

template <typename T>
class list
{
private:
	// Individual list node.
	template <typename T>
	struct Node
	{
		T element;     // Data.
		Node<T>* next; // Link to next node.
	};

	// list head and tail node pointers.
	Node<T>* head;
	Node<T>* tail;
	// Count of nodes in list.
	std::size_t count; 

	Node<T>* find(const T& e)  // Find and return node.
	{
		if (this->empty())
			return nullptr;

		Node<T> *node = this->head;

		do {
			if (node->element == e)
				return node;
			node = node->next;
		} while (node);

		return nullptr;
	}

public:
	list();	                       // Ctors.
	list(list<T>&);                // Copy ctor.
	list(list<T>&&);               // Move ctor.
	~list() { clear(); }           // Dtor.

	// Overloaded assignment copy and move operators.
	const list<T>& operator= (const list<T>&);
	list<T>& operator= (list<T>&&);

	list<T>& operator+ (list<T>&); // Append lists.
	T& front() const;              // Returns element of head node.
	T& back() const;               // Returns element at tail of list.
	bool empty() const;            // Returns true if list is empty.
	void push_front(const T&);     // Adds new node to head of list.
	void pop_front();              // Deletes head node.
	void push_back(const T& e);    // Adds new node to tail of list.
	std::size_t size();            // Returns count of elements in list.
	void clear();                  // Clears list of all elements.
	void sort();                   // Sorts list.
	void reverse();                // Reverses order of list.
	void merge(list<T>&);          // Merge lists.
	void insert(T);                // Insert element in ascending order.
	void remove(T e);              // Remove first occurance of element in list.

	bool operator== (list<T>& rhs) // List comparison operators (exact copy).
/*
	bool operator== (list<T>& rhs) // List comparison operator (same content).
	{
		if (this->size() != rhs.size())
			return false;

		Node<T> *node1 = this->head;

		while (node1)
		{
			if (!rhs->find(node1->element))
				return false;

			node1 = node1->next;
		}

		return true;
	}
*/

	{
		if (this->size() != rhs.size())
			return false;

		Node<T> *node1 = this->head, *node2 = rhs.head;

		//for (std::size_t i = 0; i < this->size(); i++)
		while (node1)
		{
			if (node1->element != node2->element)
				return false;

			node1 = node1->next;
			node2 = node2->next;
		}

		return true;
	}
	bool operator!= (list<T> rhs) { return !(this == rhs); }

	// Overloaded output operator to display list contets.
	friend std::ostream& operator<< (std::ostream& os, const list<T>& list)
	{
		for (const Node<T> *node = list.head; node; node = node->next)
			os << node->element << " ";
		return os << std::endl;
	}

	// Print all node elements in the list.
	std::ostream& print(std::ostream& os = std::cout) const
	{
		for (const Node<T> *node = this->head; node; node = node->next)
			os << node->element << " ";
		return os << std::endl;
	}

	//
	// Inner class iterator. Member typedefs provided through inheritance from std::iterator.
	class iterator : public std::iterator<std::forward_iterator_tag, T, ptrdiff_t, T*, T&>
	{
	private:
		Node<T> *plistNode;

		// Ctor is private, so only friends can create instances.
		iterator(Node<T> *newPtr) : plistNode(newPtr) { }

		friend class list;

	public:
		iterator() : plistNode(nullptr) { }

		// Overload comparison operators.
		bool operator== (const iterator& it) const { return plistNode == it.plistNode; }
		bool operator!= (const iterator& it) const { return plistNode != it.plistNode; }

		// Overload dereference and pointer operators.
		T& operator* () { return plistNode->next->data; }
		const T& operator* () const { return plistNode->next->data; }
		T* operator-> () { return &plistNode->data; }

		// Overload postfix increment operator.
		iterator operator++ (int)
		{
			iterator temp = *this;

			plistNode = plistNode->next;
			return temp;
		}

		// Overload prefix increment operator.
		iterator& operator++ ()
		{
			plistNode = plistNode->next;
			return *this;
		}
	}; // End iterator inner class.

	//
	// Inner class const_iterator.
	class const_iterator : public std::iterator<std::forward_iterator_tag, const T, ptrdiff_t, const T*, const T&>
	{
	private:
		const Node<T> *plistNode;

		// Constructor is private, so only friends can create instances.
		const_iterator(const Node<T> *newPtr) : plistNode(newPtr) { }

		friend class list;

	public:
		const_iterator() : plistNode(nullptr) { }

		// Conversion ctor.
		const_iterator(const iterator i) : plistNode(i.plistNode) { }

		// Overload comparison operators.
		bool operator== (const const_iterator& it) const { return plistNode == it.plistNode; }
		bool operator!= (const const_iterator& it) const { return plistNode != it.plistNode; }

	public:
		// Overload dereference operator.
		const T operator* () const { return plistNode->next->data; }
		const T* operator-> () const { return &plistNode->data; }

		// Overload prefix increment operator.
		const_iterator& operator++ ()
		{
			plistNode = plistNode->next;
			return *this;
		}
	}; // End const_iterator inner class.

	// Begin and end iterators.
	iterator begin() const { return iterator(head); }
	iterator end() const { return iterator(tail); }
	const_iterator cbegin() const { return const_iterator(head); }
	const_iterator cend() const { return const_iterator(tail); }
};

// List ctor.
template <typename T>
list<T>::list() : head(nullptr), tail(nullptr), count(0) { }

// List copy ctor.
template <typename T>
list<T>::list(list<T>& rhs) : head(nullptr), tail(nullptr), count(0)
{
	if (!rhs.empty())
	{
		Node<T> *node = rhs.head;

		//for (const Node<T> *node = rhs.head; node; node = node->next)
		for (std::size_t i = 0; i < rhs.size(); i++)
		{
			this->push_front(node->element);
			node = node->next;
		}

		reverse();
	}
}

// List move ctor.
template <typename T>
list<T>::list(list<T>&& rhs)
{
	this->clear();
	this->head = rhs.head;
	rhs.head = nullptr;
	this->tail = rhs.tail;
	rhs.tail = nullptr;
	this->count = rhs.count;
	rhs.count = 0;
}

// List assignment copy operator.
template<typename T>
const list<T>& list<T>::operator= (const list<T>& rhs)
{
	if (this != &rhs)
	{
		this->clear();

		for (const Node<T> *node = rhs.head; node; node = node->next)
			push_front(node->element);

		reverse();
	}

	return *this;
}

// List assignment move operator.
template <typename T>
list<T>& list<T>::operator= (list<T>&& rhs)
{
	if (this != &rhs)
	{
		this->clear();
		this->head = rhs.head;
		rhs.head = nullptr;
		this->tail = rhs.tail;
		rhs.tail = nullptr;
		this->count = rhs.count;
		rhs.count = 0;
	}

	return *this;
}

template <typename T>
void list<T>::clear()
{
	while (!this->empty())
		pop_front();

	this->head = this->tail = nullptr;
	this->count = 0;
}

template <typename T>
bool list<T>::empty() const { return this->count == 0; }

template <typename T>
std::size_t list<T>::size() { return this->count; }

template <typename T>
T& list<T>::front() const { return this->head->element; }

template <typename T>
T& list<T>::back() const { return this->tail->element; }

// Adds new node to head of list.
template <typename T>
void list<T>::push_front(const T& e)
{
	Node<T>* newNode = new Node<T>;

	newNode->element = e;
	newNode->next = head;
	this->head = newNode;

	if (this->tail == nullptr)
		this->tail = newNode;

	this->count++;
}

// Adds new node to tail of list.
template <typename T>
void list<T>::push_back(const T& e)
{
	Node<T>* newNode = new Node<T>;

	newNode->element = e;
	newNode->next = nullptr;

	if (this->tail)
		this->tail->next = newNode;
	this->tail = newNode;

	if (this->head == nullptr)
		this->head = newNode;

	this->count++;
}

// Removes node from head of list.
template <typename T>
void list<T>::pop_front()
{
	if (empty())
		return;

	Node<T>* temp = head;
	head = head->next;

	if (tail == temp)
		tail = nullptr;

	delete temp;
	count--;
}

template <typename T>
list<T>& list<T>::operator+ (list<T>& rhs)
{
	if (!rhs.empty())
	{
		Node<T>* node = rhs.head;

		for (std::size_t i = 0; i < rhs.size(); i++)
		{
			this->push_front(node->element);
			node = node->next;
		}
	}

	return *this;
}

template <typename T>
void list<T>::sort()
{
	Node<T>* index1 = head, *index2;

	for (; index1->next; index1 = index1->next)
	{
		for (index2 = index1->next; index2; index2 = index2->next)
		{
			if (index1->element > index2->element)
			{
				// Exchange data.
				T temp = index1->element;
				index1->element = index2->element;
				index2->element = temp;
			}
		}
	}
}

template <typename T>
void list<T>::reverse()
{
	Node<T>* node = this->head, *nextNode;
	head = nullptr;

	while (node)
	{
		nextNode = node->next;
		node->next = this->head;
		this->head = node;
		node = nextNode;
	}

	this->tail = node;
}

// Merge 2 lists.
template <typename T>
void list<T>::merge(list<T>& rhs)
{
	if (rhs.empty())
		return;
	else if (this->empty())
	{
		this->head = rhs.head;
		this->tail = rhs.tail;
		this->count = rhs.count;
	}
	else
	{
		reverse();

		Node<T>* node = rhs.head;

		for (std::size_t i = 0; i < rhs.size(); i++)
		{
			this->push_front(node->element);
			node = node->next;
		}
	}
}

// Insert new node in ascending order.
template <typename T>
void list<T>::insert(T e)
{
	// Create new node. 
	Node<T>* newNode = new Node<T>;
	newNode->element = e;
	newNode->next = nullptr;
	count++;

	// Only node in list?
	if (empty())
	{
		head = newNode;
		tail = newNode;
	}

	// Is value less than the value of first node?
	else if (e < head->element)
	{
		newNode->next = head;
		head = newNode;
	}
	else
	{
		Node<T>* previous = head;
		Node<T>* node = head->next;

		// Iterate to position where node is to be inserted.
		while (node != nullptr && e > node->element)
		{
			previous = node;
			node = node->next;
		}

		// Insert node at position.
		if (node == nullptr)
			previous->next = newNode;
		else
		{
			newNode->next = node;
			previous->next = newNode;
		}

		// Update tail?
		if (node == tail)
			tail = newNode;
	}
}

template <typename T>
void list<T>::remove(T e)
{
	if (this->empty())
		return;

	Node<T> *node = this->head, *prev = node;

	do {
		if (node->element == e)
		{
			while (!count--)
			{
				delete node;
				this->head = this->tail = nullptr;
				return;
			}

			if (node == this->head)
			{
				this->head = node->next;
				delete node;
				break;
			}
			else if (node == this->tail)
			{
				this->tail = prev;
				prev->next = nullptr;
				delete node;
				break;
			}
			else
			{
				prev->next = node->next;
				delete node;
				break;
			}
		}

		prev = node;
		node = node->next;

	} while (node);
}

#endif
