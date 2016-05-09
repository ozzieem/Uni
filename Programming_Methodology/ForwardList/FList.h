#pragma once
#include "Node.h"

template <typename T>
class forwardList
{
	typedef Node<T> node;
	node* head;
	node* tail;

public:
	forwardList() : head(nullptr), tail(nullptr)
	{
	}

	forwardList(T _node) : head(_node)
	{
	}

	forwardList(const forwardList& obj)
	{
		this->head = nullptr;

		node* check = obj.head;
		node* copy = nullptr;

		while (check != nullptr)
		{
			node* newnode = new node(check->data);

			if (head == nullptr)
			{
				head = newnode;
				copy = newnode;
			}
			else
			{
				copy->next = newnode;
				copy = newnode;
			}
			check = check->next;
		}
	}

	virtual ~forwardList()
	{
		clear();
	}

	node* GetHeadPtr()
	{
		return head;
	}

	bool empty()
	{
		return head == nullptr;
	}

	T& front()
	{
		return head->data;
	}

	T last()
	{
		node* n;
		n = this->head;
		for (auto it = begin(); it->next != nullptr; ++it)
		{
			n = it->next;
		}
		return n->data;
	}

	void push_front(T info)
	{
		if (head == nullptr)
		{
			head = tail = new node(info);
		}
		else
		{
			node* newNode = new node(info);
			newNode->next = head;
			head = newNode;
		}
	}

	void push_back(T info)
	{
		node* n = new node(info);
		if (head == nullptr)
			head = tail = n;
		else
			tail->next = n;
		tail = n;
	}

	void pop_front()
	{
		if (head == nullptr)
		{
			return;
		}
		else
		{
			node* d = head;
			head = head->next;
			delete d;
		}
	}

	void pop(const int index)
	{
		node* n = new node;
		iterator it(this->head);
		if (index > 0)
		{
			if ((it + index) != nullptr)
				n = (it + index);
			(it + (index - 1))->next = n->next;
			delete n;
		}
		else if (index == 0)
		{
			pop_front();
		}
	}

	/// Clears list
	void clear()
	{
		node* n = head;
		node* d;
		while (n != nullptr)
		{
			d = n;
			n = n->next;
			delete d;
		}
		head = nullptr;
	}

	/// Checks if a value is in list
	bool contains(T _data)
	{
		node* n = head;

		while (n != nullptr)
		{
			if (n->data == _data)
			{
				return true;
			}

			n = n->next;
		}

		return false;
	}

	/// Returns listsize
	int max_size() const
	{
		node* n = head;
		auto size = 0;

		while (n != nullptr)
		{
			++size;
			n = n->next;
		}

		return size;
	}

	/// Not needed
	void swap_data_position(int n1, int n2) const
	{
		node* n = head;
		node* pn1 = nullptr;
		node* pn2 = nullptr;
		auto count = 0;

		while (n != nullptr)
		{
			if (count == n1)
			{
				pn1 = n;
			}

			if (count == n2)
			{
				pn2 = n;
			}

			count++;
			n = n->next;
		}

		if (pn1 != nullptr && pn2 != nullptr)
		{
			std::swap(pn1->data, pn2->data);
		}
		else
		{
			std::cout << "Could not swap" << std::endl;
		}
	}

	class iterator
	{
	public:
		typedef iterator self_type;
		typedef node value_type;
		typedef node& reference;
		typedef node* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

		iterator(node* ptr) : ptr_(ptr)
		{
		} //Constructor
		self_type operator++()
		{
			self_type i = *this;
			ptr_ = ptr_->next;
			return i;
		}

		pointer operator+(int count)
		{
			auto ptr__ = ptr_;
			for (int i = 0; i < count; i++)
			{
				ptr__ = ptr__->next;
			}
			return ptr__;
		}

		self_type operator++(int junk)
		{
			ptr_ = ptr_->next;
			return *this;
		}

		reference operator*()
		{
			return *ptr_;
		}

		pointer operator->()
		{
			return ptr_;
		}

		bool operator==(const self_type& rhs)
		{
			return ptr_ == rhs.ptr_;
		}

		bool operator!=(const self_type& rhs)
		{
			return ptr_ != rhs.ptr_;
		}

	private:
		node* ptr_;
	};

	iterator begin() const
	{
		return iterator(head);
	}

	iterator end() const
	{
		return iterator(nullptr);
	}

	void insert_after(iterator pos, T v)
	{
		node* n = new node(v);
		n->next = pos->next;
		pos->next = n;
	}

	void insert_after(int position, T val)
	{
		node* n = new node(val);
		iterator it(this->head);
		n->next = (it + (position + 1));
		(it + position)->next = n;
	}

	void erase_after(iterator pos)
	{
		node* temp;
		temp = pos->next->next;
		delete pos->next;
		pos->next = temp;
	}

	void swap(forwardList<T>& fwl)
	{
		std::swap(fwl.head, head);
	}

	void erase(iterator pos)
	{
		node* n = head;
		if (n->value == pos->value)
		{
			node* d = head;
			head = pos->next;
			delete d;
		}
		else
		{
			while (n->next->value != pos->value)
			{
				++n;
			}
			erase_after(n);
		}
	}

	void operator=(const forwardList<T>& fl)
	{
		if (fl.head != nullptr)
		{
			head = new node(fl.head->data);
		}
		else
		{
			head = nullptr;
		}
	}

	node* mov_to_pos(int n)
	{
		node* movNode = head;
		for (int i = 0; i < n; i++)
		{
			if (movNode->next != nullptr)
				movNode = movNode->next;
		}
		return movNode;
	}

	T& operator[](const int pos)
	{
		iterator it(this->head);
		return (it + pos)->data;
	}

	void sortInt() const
	{
		node *i, *j, *t = new node;
		for (i = head; i->next != NULL; i = i->next)
		{
			for (j = head; j->next != NULL; j = j->next)
			{
				if (i->data < j->data)
				{
					t->data = i->data;
					i->data = j->data;
					j->data = t->data;
				}
			}
		}
	}
};

/*
Implementation of the single linked list:
+---------+   --->+---------+   --->+---------+   --->+---------+
| Data	  |   |   | Data    |   |   | Data    |   |   | Data    |
+---------+   |   +---------+   |   +---------+   |   +---------+
| next    |----   | next    |----   | next    |----   | next    |
+---------+       +---------+       +---------+       +---------+
*/

