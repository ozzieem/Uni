#pragma once

template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;

	Node() : next(nullptr)
	{
	}

	Node(T& _data) : data(_data), next(nullptr)
	{
	}

	T GetData()
	{
		return data;
	}

	Node<T>* GetNextPtr()
	{
		return next;
	}
};

