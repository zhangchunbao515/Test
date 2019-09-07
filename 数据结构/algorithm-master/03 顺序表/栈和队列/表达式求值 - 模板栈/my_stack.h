/* ------------------------------------------
// ջ��ͷ�ļ�
//
// ��Ĺ�ϵͼ
//  list
//   |
//  stack
// 
// �ṩģ���� stack<type>
// ģ����Ķ����ʵ��һ��Ҫ��ͬһ���ļ�����
// �������ඨ�������� #include <��ʵ��.cpp>
--------------------------------------------- */

#pragma once
#include <stdlib.h>

// �������, �ṩ��ͬ�Ľӿ�
template <typename type>
class list
{
protected:
	virtual bool empty() = 0;
	virtual void push(type data) = 0;
	virtual void pop() = 0;
	virtual int  size() = 0;
};


// ջ������ []
template <typename type>
class node
{
public:
	type data;			// ������
	node<type> *next;	// ָ����
};


// ��ʽջ��, �����̳к�, �ٹ��л�
template <typename type>
class stack: protected list<type>
{
public:
	stack();
	~stack();
	virtual bool empty();
	virtual void push(type data);
	virtual void pop();
	virtual int  size();
	type top();		// ȡջ��
private:
	int _size;
	node<type> *_top;	// type���͵Ľ��ṹ��ַ
};

// -----------------ջʵ�ֲ���---------------------
// ����ʱ [top(����)]
// ʹ�ú� [top(����)] -> [] -> [] -> NULL

template <typename type>	// ����
stack<type>::stack()
{
	_top = new node<type>;
	_top->next = NULL;
	_size = 0;
}

template <typename type>	// ����
stack<type>::~stack()
{
	node<type> *cur;
	cur = _top;
	while (cur)
	{
		_top = cur->next;
		delete cur;
		cur = _top;
	}
}

template <typename type>	// ��ջ
void stack<type>::push(type data)
{
	node<type> *n;

	_top->data = data;		// ������ջ
	n = new node<type>;		// �����¿ռ�
	if (!n) abort();
	n->next = _top;
	_top = n;
	_size++;
}

template <typename type>	// ��ջ
void stack<type>::pop()
{
	node<type> *del;

	if (_size)
	{
		del = _top;		// �ͷ�һ�����
		_top = _top->next;
		delete del;
		_size--;
	}
}

template <typename type>	// ȡջ��
type stack<type>::top()
{
	return _top->next->data;
}

template <typename type>	// �п�
bool stack<type>::empty()
{
	if (_size) return false;
	else return true;
}

template <typename type>	// ���С
int stack<type>::size()
{  return _size; }
