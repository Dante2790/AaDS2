#ifndef QUEUEVECTOR_H
#define QUEUEVECTOR_H
#include "Queue.h"
#include <iostream>
#include <stdexcept>
#include <string>

template <class T>
class QueueVector : public Queue<T> {

///////
private:
	static const int initialSize = 10;
	static const int maxSize = 80;

	int first;
	int last;
	
	int currentSize;
	int counter;

	T* data;
	
	/// <summary>
	/// this method will double the queue size
	/// </summary>
	void resize();

	/// <summary>
	/// this method will check if the queue is empty
	/// </summary>
	/// <returns>queue == empty ? true : false</returns>
	bool isEmpty() override {
		return this->counter == 0;
	}

	QueueVector(const QueueVector& other) = delete;
	QueueVector(QueueVector& other) = delete;
	QueueVector& operator= (const QueueVector& other) = delete;
	QueueVector& operator= (QueueVector& other) = delete;

	//////////////////////////////////////////////////
	class QueueOverflow : public std::overflow_error {
	private:
		std::string message;
	public:
		explicit QueueOverflow(const std::string& msg) noexcept : std::overflow_error(msg), message(msg) {};
		const char* what() const noexcept override {
			return message.c_str();
		}
	};
	class QueueUnderflow : public std::underflow_error {
	private:
		std::string message;
	public:
		explicit QueueUnderflow(const std::string& msg) noexcept : std::underflow_error(msg), message(msg) {};
		const char* what() const noexcept override {
			return message.c_str();
		}
	};
	class UnexpectedError : public QueueUnderflow {
	private:
		std::string message;
	public:
		explicit UnexpectedError(std::string msg) noexcept : QueueUnderflow(msg), message(msg) {};
		const char* what() const noexcept override {
			return message.c_str();
		}
	};
	//////////////////////////////////////////////////
	
///////
public:
	QueueVector();
	~QueueVector() {
		delete[] data;
	};

	

	/// <summary>
	/// this method will output all the contents of the queue
	/// </summary>
	void print();
	
	/// <summary>
	/// this method adds a new element to the ueue
	/// </summary>
	/// <param name="data">- element to add</param>
	void enQueue(const T& data) override;

	/// <summary>
	/// this method will remove an element from the queue and return it's data
	/// </summary>
	/// <returns>element to delete and return</returns>
	T deQueue() override;
	
	
	
};



#endif;
