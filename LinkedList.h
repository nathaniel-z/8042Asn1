#pragma once

#include<iterator>
#include<initializer_list>

// Individual item in the LinkedList
template <typename T>
struct ListItem
{
	ListItem(T data)
		: next(nullptr)
		, data(data)
	{
	}

	ListItem* next;
	T data;
};


// Iterator class for the LinkedList for ranged-based for loops
template <typename T>
class LinkedListIterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
	LinkedListIterator<T>(ListItem<T>* pointer)
		: pointer(pointer)
	{
	}

	LinkedListIterator& operator++()
	{
		pointer = pointer->next;
		return *this;
	}

	bool operator==(const LinkedListIterator& other)
	{
		return pointer == other.pointer;
	}

	bool operator!=(const LinkedListIterator& other)
	{
		return pointer != other.pointer;
	}

	T& operator*() const
	{
		return pointer->data;
	}

private:
	ListItem<T>* pointer;
};


// Base LinkedList class
template <typename T>
class LinkedList
{
public:
	// Initializer list constructor
	LinkedList(std::initializer_list<T> init)
	{
		head = new ListItem<T>(*init.begin());
		ListItem<T>* current = head;

		bool firstIteration = true;
		for (T data : init)
		{
			if (firstIteration)
			{
				firstIteration = false;
				continue;
			}

			ListItem<T>* item = new ListItem<T>(data);
			current->next = item;
			current = item;
		}

		tail = current;
	}

	// Iterator accessor for use by range-based for loops
	LinkedListIterator<T> begin() const
	{
		return LinkedListIterator<T>(head);
	}

	// Iterator accessor for use by range-based for loops
	LinkedListIterator<T> end() const
	{
		return LinkedListIterator<T>(nullptr);
	}

	// Destructor
	~LinkedList()
	{
		ListItem<T>* current = head;
		while (current != tail)
		{
			ListItem<T>* temp = current->next;
			delete current;
			current = temp;
		}

		delete tail;
	}

private:
	ListItem<T>* head;
	ListItem<T>* tail;
};
