#include "StackList.h"
using namespace std;

void getPostfixFromInfix(const char* infix, char* postfix);

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
}