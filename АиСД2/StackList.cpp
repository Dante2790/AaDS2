#include "StackList.h"
#include <iostream>
template <typename T>
StackList<T>::StackList() :
	top(nullptr)
{};

template <typename T>
StackList<T>::~StackList() {
	while (top) {
		this->pop();
	}
}

template <typename T>
void StackList<T>::push(const T& data) {
	try {
		Node* new_node = new Node(data);
		if (!new_node) { throw StackOverflow("stack is overflow"); }
		switch (this->isEmpty()) {
		case false:
			
			new_node->next = this->top;
			this->top = new_node;
			break;
		case true:
			
			this->top = new_node;
			break;
		}
	}
	catch (StackUnderflow er) {
		cerr << "error: " << er.what() << "\n";
		return;
	}
	catch (invalid_argument er) {
		cerr << "error: " << er.what() << "\n";
		return;
	}
}
template <typename T>
T StackList<T>::pop() {
	try {
		if (this->isEmpty()) {
			throw StackUnderflow("stack is empty");
		}
		T current = this->top->data;
		Node* current_next = this->top->next;
		delete this->top;
		if (current_next) {
			this->top = current_next;
		}
		else {
			this->top = nullptr;
		}
		return current;
	}
	catch (StackUnderflow er) {
		cerr << "error: " << er.what();
		T er_current = '\n';
		return er_current;
	}
}
template <typename T>
void StackList<T>::print() {
	try {
		if (this->isEmpty()) {
			throw StackUnderflow("stack is empty");
		}
		Node* current = this->top;
		while (current) {
			cout << current->data;
			if (current->next) {
				cout << " <- ";
			}
			else {
				cout << '\n';
			}
			current = current->next;
		}
	}
	catch (StackUnderflow er) {
		cerr << "error: " << er.what() << "\n";
	}
}

template <typename T>
bool StackList<T>::isEmpty() {
	return this->top == nullptr;
}
template <typename T>
T StackList<T>::getTop() {
	return this->isEmpty() ? '\n' : this->top->data;
}

template class StackList<char>;