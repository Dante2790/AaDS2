#include "StackList.h"
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
		switch (this->isEmpty()) {
		case false:
			
			new_node->next = this->top;
			this->top = new_node;
			break;
		case true:
			
			this->top = new_node;
			break;
		}
		//cout << data << "\n";
	}
	catch (out_of_range er) {
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
			throw out_of_range("stack is empty");
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
		cout << current << '\n';
		return current;
	}
	catch (out_of_range er) {
		cerr << "error: " << er.what() << "\n";
		T er_current = '~\n';
		return er_current;
	}
}
template <typename T>
void StackList<T>::print() {
	try {
		if (this->isEmpty()) {
			throw out_of_range("stack is empty");
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
	catch (out_of_range er) {
		cerr << "error: " << er.what() << "\n";
	}
}

template <typename T>
bool StackList<T>::isEmpty() {
	return this->top == nullptr;
}

template class StackList<char>;