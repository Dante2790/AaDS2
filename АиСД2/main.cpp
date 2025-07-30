#include "StackList.h"
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

void getPostfixFromInfix(const char* infix, char* postfix);
string eraseWrongSymbols(string& str);


int main() {
	char f = '6';
	char t = '8';
	StackList<char> a, b;
	a.push(f);
	a.push(t);
	a.push('a');
	a.push('2');
	a.print();
	a.pop();
	a.pop();
	a.print();
	b.print();
	string source;
	getline(cin, source);
	cout << '\n' << source << '\n';
	eraseWrongSymbols(source);
	cout << source << '\n';
	
	
	cout << "-----------" << '\n' << source << '\n';
	const char* infix = source.c_str();
	int sizeOfInfix = sizeof(infix);
	char* postfix = new char[(sizeOfInfix*3)];
	//strcpy_s(postfix, (sizeof(postfix)), infix);
	cout << postfix << '\n';
	getPostfixFromInfix(infix, postfix);
	cout << "-----------" << '\n' << infix << '\n' << postfix << '\n';
	delete[] postfix;
}
string eraseWrongSymbols(string &str) {
	char current = str[0];
	for (int i = 0; i < (str.size()); i++) {
		current = str[i];
		if (current == ' ') {
			str.erase(i, 1);
			i--;
		}
		else if (current == '=') {
			str.erase(i, (str.size() - i));
		}
	}
	return str;
}

// шляпа полная эта версия конвертера, переделать

void getPostfixFromInfix(const char* infix, char* postfix) {
	cout << "magic!" << '\n' << " - - ~" << '\n';
	StackList<char> stack;
	string strPostfix;
	char current = infix[0];
	int size = sizeof(infix);
	for (int i = 0; i < size*2; i++) {
		current = infix[i];
		if (!current) {
			strcpy_s(postfix, (size * 3), strPostfix.c_str());
			postfix[size + 1] = '\n';
			return;
		}
		switch (current) {
		case '(':
		case ')':
			stack.push(current);
			if (current == '(') {
				strPostfix += infix[i + 1];
				//strPostfix += " ";
				i++;
			}
			
			
			stack.pop();
			cout << " ";
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			stack.push(current);
			if (infix[i + 1] == '(') {
				stack.push(infix[i + 1]);
				stack.pop();
				cout << " ";
				i++;
			}
			
			strPostfix += infix[i + 1];
			//strPostfix += " ";
			i++;
			strPostfix += stack.pop();
			//strPostfix += " ";
			cout << " ";
			break;
		default:
			strPostfix += infix[i];
			//strPostfix += " ";
			break;
		}
		
	}
	
}
//						2+2+2+2+2+2