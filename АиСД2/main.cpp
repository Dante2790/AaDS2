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
	string source4 = "(9+(4-4)+3+4)";
	string source3 = "(9-((8*(7-(6/(5+4))))+(3*(2-1))))/((1+2)*(3-(4/(5+6))))";
	string source2 = "((3+7)*(5-(2/(6+1))))-(4*(9-(8/2)))";
	string source = "5 + (-7) + 4*(5+6*(5+4)+(-9))/(5*5-8*8)";
	//getline(cin, source);
	
	
	switch (checkWrongSymbols(source3)) {
	case true:


		cout << "-----------" << '\n' << source3 << '\n';
		try {
			eraseWrongSymbols(source3);
			if (checkBracketsCorrectness(source3)) {
				cout << "----------------------------------------------------------" << '\n';
			}
			const char* infix = source3.c_str();
			char* postfix = new char[(strlen(infix)*2) + 2];
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
	if (checkStr.empty()) {
		numberOfErrors++;
	}
	////////////////////////////////////////////
	/*
	for (int i = 0; i < (checkStr.size()); i++) {
		current = checkStr[i];
		if (current == '(') {
			numberOfErrors++;
		}
		else if (current == ')') {
			numberOfErrors--;
		}
	}
	*/
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
		if ((current == '+' || current == '-' ||
			current == '/' || current == '*') &&
			(checkStr[i + 1] == '+' || checkStr[i + 1] == '-' ||
				checkStr[i + 1] == '*' || checkStr[i + 1] == '/')) {
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
	cout << "your arithmetic expression is uncorrect";
	return false;
}

bool checkBracketsCorrectness(string strForCheck) {
	char current = strForCheck[0];
	static bool flag = false;
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
				if (j > i) {
					i = j;
				}
				i++;
				current = strForCheck[i];
				if (current == '(') {
					j = i;
					depthOfBrackets++;
					checkBracketsCorrectness(strForCheck);
					if (flag == false) {
						return false;
					}
				}
				else if (current == ')') {
					numberOfBrackets--;
					if (depthOfBrackets > 0) {
						strForCheck.erase(i, 1);
						depthOfBrackets--;
						j = i;
						flag = true;
						return true;
					}
				}
			}
		}
	}
	//j = strForCheck.size();
	return numberOfBrackets == 0 ? true : false;
}

void getPostfixFromInfix(const char* infix, char* postfix) {
	cout << "magic!" << '\n' << " - - ~" << '\n';
	StackList<char> stack;
	int numberOfBrackets = 0;
	string strPostfix;
	char current = infix[0];
	char temp = current;
	int counter = 0;
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
			current = stack.getTop();
			if (current == '*' || current == '/') {
				counter++;
			}
			current = infix[i];
			numberOfBrackets++;
			stack.push(current);
			i++;
			current = infix[i];
			while (numberOfBrackets != 0) {
				if (isdigit(current)) {
					strPostfix += current;
					strPostfix += ' ';
				}
				else if (current == '*' || current == '/') {
					stack.push(current);
					if (infix[i + 1] == '(') {
					}
					else {
						strPostfix += infix[i + 1];
						strPostfix += ' ';
						strPostfix += stack.pop();
						strPostfix += ' ';
						i++;
					}
				}
				else if (current == '+' || current == '-') {
					if (current == '-' && isdigit(infix[i + 1]) && infix[i + 2] == ')' && infix[i-1] == '(') {
						strPostfix += current;
						strPostfix += infix[i + 1];
						strPostfix += ' ';
						i += 2;
						
						numberOfBrackets--;
					}
					else {
						stack.push(current);
					}
				}
				else if (current == '(') {
					numberOfBrackets++;
					stack.push(current);
				}
				else if (current == ')') {
					numberOfBrackets--;
					stack.push(current);
					while (stack.getTop() != '\n') {
						current = stack.getTop();
						if (current == ')') {
							
							stack.pop();
						}
						else if (current == '(') {
							stack.pop();
							/*
							current = stack.getTop();
							
							if (current == '*' || current == '/' || current == '+' || current == '-') {
								strPostfix += stack.pop();
								strPostfix += ' ';
							}
							*/
							if (counter > 0 && stack.getTop() != '(') {
								strPostfix += stack.pop();
								strPostfix += ' ';
								counter--;
							}
							break;
						}
						/*
						else if (stack.getTop() == '-') {
							temp = stack.pop();
							if (stack.getTop() == '(') {
								stack.pop();
								if (stack.getTop() == '+') {
									strPostfix += '-';
									strPostfix += ' ';
									stack.pop();
								}
								else if (stack.getTop() == '-') {
									strPostfix += '+';
									strPostfix += ' ';
									stack.pop();
								}
								else {
									strPostfix += temp;
									strPostfix += ' ';
								}
						}
						*/
						//}
						else {
							strPostfix += stack.pop();
							strPostfix += ' ';
						}
					}
				}
				i++;
				current = infix[i];
			}			
			while (stack.getTop() != '\n') {
				current = stack.getTop();
				if (current == ')') {
					stack.pop();
				}
				else if (current == '(') {
					stack.pop();
					break;
				}
				else {
					strPostfix += stack.pop();
					strPostfix += ' ';
				}
				
			}
			if (counter > 0) {
				strPostfix += stack.pop();
				strPostfix += ' ';
				counter--;
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
					strPostfix += ' ';
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
			strPostfix += ' ';
			strPostfix += stack.pop();
			strPostfix += ' ';
			break;
		case '\n':
			;
			return;
		default:
			strPostfix += infix[i];
			strPostfix += ' ';
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
			strPostfix += ' ';
		}
	}
	strcpy_s(postfix, strlen(strPostfix.c_str())+1, strPostfix.c_str());
	postfix[strlen(postfix) + 1] = '\n';
	////////////////////////////////////////////////////////////////////
}
