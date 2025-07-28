#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

template <typename T>
class Stack {
public:
	virtual ~Stack() = default;
	virtual void push(const T& data) = 0;
	virtual T pop() = 0;
	virtual bool isEmpty() = 0;

};
#endif;
