#pragma once

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <exception>

#include "slist.h"

// Custom execption thrown when attempting operation on empty queue.
struct QueueException : public std::exception
{
	const char* what() const throw() { return "Illegal operation on empty queue.\n"; }
};

template <typename T>
class Queue : public list<T>
{
public:
	// Add queue exception to list<T>::back() function.
	T back()
	{
		if (this->empty())
			throw QueueException();

		return this->list<T>::back();
	}
		
	// Adds new node to tail of queue.
	void enqueue(const T& e) { this->push_back(e); }

	// Deletes head node.
	void dequeue()
	{
		if (this->empty())
			throw QueueException();

		this->pop_front();
	}
};

#endif
