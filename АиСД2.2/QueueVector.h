#ifndef QUEUEVECTOR_H
#define QUEUEVECTOR_H
#include "Queue.h"
#include <iostream>
#include <stdexcept>
#include <string>

template <class T>
class QueueVector : public Queue<T> {
private:
	T data;
	T* first;
	T* last;
	int initialSize;
	int currentSize;
	int count;

	void resize();
	bool isEmpty() override;
public:
	QueueVector();
	~QueueVector();
	void enQueue(const T& data) override;
	T deQueue() override;
	

	
};

class QueueOverflow : public std::overflow_error {
private:
	std::string message;
public:
	QueueOverflow(std::string msg) : std::overflow_error(msg) {}
	const char* what() const override {
		return message.c_str();
	}
};
class QueueUnderflow : public std::underflow_error {
private:
	std::string message;
public:
	QueueUnderflow(std::string msg) : std::underflow_error(msg) {}
	const char* what() const override {
		return message.c_str();
	}
};
#endif;
