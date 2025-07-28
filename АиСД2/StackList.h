#ifndef STACKLIST_H
#define STACKLIST_H

#include "stack.h"
template <typename T>
class StackList : public Stack <T> {
private:
    struct Node {
        char data;
        Node* next;
        Node(const char& new_data) : data(new_data), next(nullptr) {}
        Node(char&& new_data) : data(move(new_data)), next(nullptr) {}
        Node(Node* node) : data(node->data), next(nullptr) { delete node; }

    };

    Node* top;
    

    
public:
	~StackList();
    StackList();
    StackList(const StackList &other) = delete;
    StackList(StackList& other) = delete;
    StackList& operator= (const StackList& other) = delete;
    StackList& operator= (StackList& other) = delete;
	void push(const T& data)override ;
	T pop()override;
	bool isEmpty() override;

    
    void print();

};



#endif;
