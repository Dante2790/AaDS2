#include "StackList.h"
#include <cstring>
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

void getPostfixFromInfix(const char* infix, char* postfix);
void eraseWrongSymbols(string& str);
bool checkWrongSymbols(const string& checkStr);
bool checkBracketsCorrectness(string strForCheck);

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
	string source = "4*(5+6*(5+4)+(-9))/(5*5-8*8)";
	//getline(cin, source);
	cout << '\n' << source << '\n';
	eraseWrongSymbols(source);
	switch (checkWrongSymbols(source)) {
	case true:
		cout << source << '\n';


		cout << "-----------" << '\n' << source << '\n';
		try {
			const char* infix = source.c_str();
			char* postfix = new char[strlen(infix) + 2];
			//strcpy_s(postfix, (sizeof(postfix)), infix);
			cout << postfix << '\n';
			getPostfixFromInfix(infix, postfix);
			cout << "-----------" << '\n' << infix << '\n' << postfix << '\n';
			delete[] postfix;
			return 0;
		}
		catch (out_of_range er) {
			cerr << "error: " << er.what() << "\n";
			return 1;
		}
		catch (invalid_argument er) {
			cerr << "error: " << er.what() << "\n";
			return 1;
		}
	case false:
		cout << "no";

	}
}

/////////////////////////////////////////////////////////////////////////////////

void eraseWrongSymbols(string &str) {
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
	return;
}





bool checkWrongSymbols(const string& checkStr) {
	char current = checkStr[0];
	int numberOfErrors = 0;
	int numberOfBrackets = 0;
	////////////////////////////////////////////
	for (int i = 0; i < (checkStr.size()); i++) {
		current = checkStr[i];
		if (current == '(') {
			numberOfErrors++;
		}
		else if (current == ')') {
			numberOfErrors--;
		}
	}
	////////////////////////////////////////////
	/*for (int i = 0; i < (checkStr.size()); i++) {
		current = checkStr[i];
		if (current == '(') {
			numberOfBrackets++;
			int j = i;
			numberOfErrors++;
			while ((current != ')') && (i < checkStr.size()) && (numberOfBrackets != 0)) {
				i++;
				current = checkStr[i];
			}
			if (current == ')') {
				numberOfErrors--;
			}
		}
	}*/

	if (!checkBracketsCorrectness(checkStr)) {
		numberOfErrors++;
	}
	////////////////////////////////////////////
	for (int i = 0; i < (checkStr.size()); i++) {
		current = checkStr[i];
		if (!(isdigit(current)) && current != '+' &&
			current != '-' && current != '*' &&
			current != '/' && current != '(' &&
			current != ')') {
			numberOfErrors++;
		}
	}
	////////////////////////////////////////////
	for (int i = 0; i < (checkStr.size()); i++) {
		current = checkStr[i];
		if ((current == '+' && checkStr[i + 1] == '+') ||
			(current == '-' && checkStr[i + 1] == '-') ||
			(current == '*' && checkStr[i + 1] == '*') ||
			(current == '/' && checkStr[i + 1] == '/')) {
			numberOfErrors++;
		}
	}
	////////////////////////////////////////////
	for (int i = 0; i < (checkStr.size()); i++) {
		current = checkStr[i];
		if (isdigit(current) && isdigit(checkStr[i + 1])) {
			numberOfErrors++;
		}
	}
	////////////////////////////////////////////
	if (!(isdigit(checkStr[0])) && checkStr[0] != '(') {
		numberOfErrors++;
	}
	////////////////////////////////////////////

	if (numberOfErrors == 0) {
		return true;
	}
	return false;
}

bool checkBracketsCorrectness(string strForCheck) {
	char current = strForCheck[0];
	static int numberOfBrackets;
	static int j;
	static int depthOfBrackets;
	for (int i = 0; i < strForCheck.size(); i++) {
		if (j > i) {
			i = j;
		}
		current = strForCheck[i];
		if (current == '(') {
			numberOfBrackets++;
			while ((numberOfBrackets != 0) && (i < strForCheck.size())) {
				i++;
				current = strForCheck[i];
				if (current == '(') {
					j = i;
					depthOfBrackets++;
					checkBracketsCorrectness(strForCheck);
				}
				else if (current == ')') {
					numberOfBrackets--;
					if (depthOfBrackets > 0) {
						strForCheck.erase(i, 1);
						depthOfBrackets--;
					}
				}
			}
		}
	}
	return numberOfBrackets == 0 ? true : false;
}

void getPostfixFromInfix(const char* infix, char* postfix) {
	cout << "magic!" << '\n' << " - - ~" << '\n';
	StackList<char> stack;
	int numberOfBrackets = 0;
	string strPostfix;
	char current = infix[0];
	char temp = current;
	////////////////////////////////////////////////////////
	for (int i = 0; i < strlen(infix); i++) {
		current = infix[i];
		if (current == '\n') {
			break;
		}
		else if (!current) {
			break;
		}
		switch (current) {
		//////////////////
		case '(':
			numberOfBrackets++;
			stack.push(current);
			i++;
			current = infix[i];
			while (numberOfBrackets != 0) {
				if (isdigit(current)) {
					strPostfix += current;
				}
				else if (current == '*' || current == '/') {
					stack.push(current);
					if (infix[i + 1] == '(') {
					}
					else {
						strPostfix += infix[i + 1];
						strPostfix += stack.pop();
						i++;
					}
				}
				else if (current == '+' || current == '-') {
					
					stack.push(current);
				}
				else if (current == '(') {
					numberOfBrackets++;
					stack.push(current);
				}
				else if (current == ')') {
					numberOfBrackets--;
					stack.push(current);
					while (stack.getTop() != '\n') {
						if (stack.getTop() == ')') {
							stack.pop();
						}
						else if (stack.getTop() == '(') {
							stack.pop();
							if (stack.getTop() == '*' || stack.getTop() == '/') {
								strPostfix += stack.pop();
							}
							break;
						}
						else if (stack.getTop() == '-') {
							temp = stack.pop();
							if (stack.getTop() == '(') {
								stack.pop();
								if (stack.getTop() == '+') {
									strPostfix += '-';
									stack.pop();
								}
								else if (stack.getTop() == '-') {
									strPostfix += '+';
									stack.pop();
								}
								else {
									strPostfix += temp;
								}
						}
						}
						else {
							strPostfix += stack.pop();
						}
					}
				}
				i++;
				current = infix[i];
			}			
			while (stack.getTop() != '\n') {
				if (stack.getTop() == '(' || stack.getTop() == ')') {
					stack.pop();
				}
				else {
					strPostfix += stack.pop();
				}
			}
			i--;
			break;
		//////////////////
		case ')':
			while (stack.getTop() != '\n') {
				if (stack.getTop() == '(') {
					stack.pop();
				}
				else {
					strPostfix += stack.pop();
				}
			}
			break;
		//////////////////
		case '+':
		case '-':
			stack.push(current);
			break;
		//////////////////
		case '*':
		case '/':
			stack.push(current);
			if (infix[i + 1] == '(') {
				break;
			}
			i++;
			current = infix[i];
			strPostfix += current;
			strPostfix += stack.pop();
			break;
		case '\n':
			;
			return;
		default:
			strPostfix += infix[i];
			break;
		}
		
	}
	////////////////////////////////
	while (stack.getTop() != '\n') {
		if (stack.getTop() == '(') {
			stack.pop();
		}
		else {
			strPostfix += stack.pop();
		}
	}
	strcpy_s(postfix, strlen(strPostfix.c_str())+1, strPostfix.c_str());
	postfix[strlen(infix) + 1] = '\n';
	////////////////////////////////////////////////////////////////////
}
