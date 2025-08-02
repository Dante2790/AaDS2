#ifndef STACKLIST_H
#define STACKLIST_H

#include "stack.h"
template <typename T>
class StackList : public Stack <T> {
private:
    struct Node {
        char data;
        Node* next;
        Node(const T& new_data) : data(new_data), next(nullptr) {}
    };

    Node* top;

public:
	~StackList();
    StackList();

    StackList(const StackList &other) = delete;
    StackList(StackList& other) = delete;
    StackList& operator= (const StackList& other) = delete;
    StackList& operator= (StackList& other) = delete;
	void push(const T& data)override;

	T pop()override;
	bool isEmpty() override;
    
    void print();
    T getTop();
};

#endif;
