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

void test01();
void test02();
void test03();
void test04();
void test05();

//////////////

int main() {
	test01();
	test02();
	test03();
	test04();
	test05();
	return 0;
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
	
	return false;
}

bool checkBracketsCorrectness(string strForCheck) {
	char current = strForCheck[0];
	static bool flag = false;
	static int numberOfBrackets;
	static int j;
	static int depthOfBrackets;
	for (int i = 0; i < strForCheck.size(); i++) {
		if (i == j && j == 0) {
			numberOfBrackets = 0;
			flag = false;
			depthOfBrackets = 0;
		}
		if (j > i) {
			i = j;
		}
		current = strForCheck[i];
		if (current == ')' && numberOfBrackets == 0) {
			return false;
		}
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
	j = 0;
	
	return numberOfBrackets == 0 ? true : false;
}

void getPostfixFromInfix(const char* infix, char* postfix) {

	try {
		StackList<char> stack;
		int numberOfBrackets = 0;
		string tempStr = infix;
		if (!(checkWrongSymbols(tempStr))) {
			throw invalid_argument("your arithmetic expression is uncorrect");
		}
		string strPostfix;
		char current = infix[0];
		char tempChr = current;
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
						if (current == '-' && isdigit(infix[i + 1]) && infix[i + 2] == ')' && infix[i - 1] == '(') {
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
								if (counter > 0 && stack.getTop() != '(') {
									strPostfix += stack.pop();
									strPostfix += ' ';
									counter--;
								}
								break;
							}
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
		strcpy_s(postfix, strlen(strPostfix.c_str()) + 1, strPostfix.c_str());
		postfix[strlen(postfix) + 1] = '\n';
	}
	////////////////////////////////////
	catch (invalid_argument er) {
		cerr << er.what() << '\n';
	}
	////////////////////////////////////////////////////////////////////
}

void test01() {
	try {
		cout << '\n' << '\n' << '\n';
		cout << "			" << " ######## " << "	" << "   ##   " << '\n';
		cout << "			" << "##      ##" << "	" << "  ###   " << '\n';
		cout << "			" << "##      ##" << "	" << " # ##   " << '\n';
		cout << "			" << "##      ##" << "	" << "   ##   " << '\n';
		cout << "			" << "##      ##" << "	" << "   ##   " << '\n';
		cout << "			" << " ######## " << "	" << "  ####  " << '\n';
		cout << '\n' << '\n' << '\n';

		////////////////////////////////////////////////////////////////////

		string source = "5+(-7)+4*(5+6*(5+4)+(-9))/(5*5-8*8)";
		string source2 = "((3+7)*(5-(2/(6+1))))-(4*(9-(8/2)))";
		string source3 = "(9-((8*(7-(6/(5+4))))+(3*(2-1))))/((1+2)*(3-(4/(5+6))))";
		string source4 = "(9+(4-4)+3+4)";

		eraseWrongSymbols(source);
		eraseWrongSymbols(source2);
		eraseWrongSymbols(source3);
		eraseWrongSymbols(source4);

		const char* infix = source.c_str();
		char* postfix = new char[(strlen(infix) * 2) + 2];
		const char* infix2 = source2.c_str();
		char* postfix2 = new char[(strlen(infix) * 2) + 2];
		const char* infix3 = source3.c_str();
		char* postfix3 = new char[(strlen(infix) * 2) + 2];
		const char* infix4 = source4.c_str();
		char* postfix4 = new char[(strlen(infix) * 2) + 2];

		getPostfixFromInfix(infix, postfix);
		getPostfixFromInfix(infix2, postfix2);
		getPostfixFromInfix(infix3, postfix3);
		getPostfixFromInfix(infix4, postfix4);

		cout << "1) " << infix << " -> " << postfix << '\n';
		cout << "2) " << infix2 << " -> " << postfix2 << '\n';
		cout << "3) " << infix3 << " -> " << postfix3 << '\n';
		cout << "4) " << infix4 << " -> " << postfix4 << '\n';

		delete[] postfix;
		delete[] postfix2;
		delete[] postfix3;
		delete[] postfix4;

		////////////////////////////////////////////////////////////////////

		cout << "----------------------------------------------" << '\n';
	}
	catch (bad_alloc er) {
		cerr << '\n' << er.what() << '\n';
		return;
	}
}

void test02() {
	cout << '\n' << '\n' << '\n';
	cout << "			" << " ######## " << "	" << "########" << '\n';
	cout << "			" << "##      ##" << "	" << "      ##" << '\n';
	cout << "			" << "##      ##" << "	" << "    ##  " << '\n';
	cout << "			" << "##      ##" << "	" << "  ##    " << '\n';
	cout << "			" << "##      ##" << "	" << "##      " << '\n';
	cout << "			" << " ######## " << "	" << "########" << '\n';
	cout << '\n' << '\n' << '\n';

	////////////////////////////////////////////////////////////////////

	string source = "5+(-7)+4*(5+6**4";
	string source2 = ")(3+7)*(5-(2/(6+1))))-(4*(9-(8/2)))";
	string source3 = "9-8*7-6/5+4))))+(3*(2-1))))/((1+2)*(3-(4/(5+6))))";
	string source4 = "(943+(4-4)+3+4)";

	eraseWrongSymbols(source);
	eraseWrongSymbols(source2);
	eraseWrongSymbols(source3);
	eraseWrongSymbols(source4);

	const char* infix = source.c_str();
	char* postfix = new char[(strlen(infix) * 2) + 2];
	const char* infix2 = source2.c_str();
	char* postfix2 = new char[(strlen(infix) * 2) + 2];
	const char* infix3 = source3.c_str();
	char* postfix3 = new char[(strlen(infix) * 2) + 2];
	const char* infix4 = source4.c_str();
	char* postfix4 = new char[(strlen(infix) * 2) + 2];

	cout << "1) " << infix << " -> ";
	getPostfixFromInfix(infix, postfix);
	cout << "2) " << infix2 << " -> ";
	getPostfixFromInfix(infix2, postfix2);
	cout << "3) " << infix3 << " -> ";
	getPostfixFromInfix(infix3, postfix3);
	cout << "4) " << infix4 << " -> ";
	getPostfixFromInfix(infix4, postfix4);

	delete[] postfix;
	delete[] postfix2;
	delete[] postfix3;
	delete[] postfix4;

	////////////////////////////////////////////////////////////////////

	cout << "----------------------------------------------" << '\n';
}

void test03() {
	cout << '\n' << '\n' << '\n';
	cout << "			" << " ######## " << "	" << " ###### " << '\n';
	cout << "			" << "##      ##" << "	" << "#     ##" << '\n';
	cout << "			" << "##      ##" << "	" << "   #####" << '\n';
	cout << "			" << "##      ##" << "	" << "      ##" << '\n';
	cout << "			" << "##      ##" << "	" << "#     ##" << '\n';
	cout << "			" << " ######## " << "	" << " ###### " << '\n';
	cout << '\n' << '\n' << '\n';

	////////////////////////////////////////////////////////////////////

	string source = "5+(-7)+4*(5+6*   (5   +4)+(-   9))/(5*5-8*8)";
	string source2 = "((3+7)*(5sd-(2/(6+1)))fd)-(4*(9a-(8/2)))";
	string source3 = "(9-((8*@@(7-(6/(5+//4))))+(3*(2-1))))/((1+2)*(3-(4/(5+6))))";
	string source4 = "(9+(4-4)+3+4) = 43";

	eraseWrongSymbols(source2);
	eraseWrongSymbols(source3);

	const char* infix = source.c_str();
	char* postfix = new char[(strlen(infix) * 2) + 2];
	const char* infix2 = source2.c_str();
	char* postfix2 = new char[(strlen(infix) * 2) + 2];
	const char* infix3 = source3.c_str();
	char* postfix3 = new char[(strlen(infix) * 2) + 2];
	const char* infix4 = source4.c_str();
	char* postfix4 = new char[(strlen(infix) * 2) + 2];

	cout << "1) " << source << " -> ";
	eraseWrongSymbols(source);
	getPostfixFromInfix(infix, postfix);
	cout << postfix << '\n';
	cout << "2) " << infix2 << " -> ";
	getPostfixFromInfix(infix2, postfix2);
	cout << "3) " << infix3 << " -> ";
	getPostfixFromInfix(infix3, postfix3);
	cout << "4) " << source4 << " -> ";
	eraseWrongSymbols(source4);
	getPostfixFromInfix(infix4, postfix4);
	cout << postfix4 << '\n';

	delete[] postfix;
	delete[] postfix2;
	delete[] postfix3;
	delete[] postfix4;

	////////////////////////////////////////////////////////////////////

	cout << "----------------------------------------------" << '\n';
}

void test04() {
	cout << '\n' << '\n' << '\n';
	cout << "			" << " ######## " << "	" << "##    ##" << '\n';
	cout << "			" << "##      ##" << "	" << "##    ##" << '\n';
	cout << "			" << "##      ##" << "	" << "########" << '\n';
	cout << "			" << "##      ##" << "	" << "      ##" << '\n';
	cout << "			" << "##      ##" << "	" << "      ##" << '\n';
	cout << "			" << " ######## " << "	" << "      ##" << '\n';
	cout << '\n' << '\n' << '\n';

	////////////////////////////////////////////////////////////////////
	StackList<char> stack;
	char char1 = '3';
	char char2 = '4';
	char char3 = 'd';
	char char4 = '=';

	stack.print();
	stack.push(char1);
	stack.print();
	stack.push(char2);
	stack.print();
	stack.push(char3);
	stack.print();
	stack.push(char4);
	stack.print();;
	cout << stack.pop() << '\n';
	stack.print();
	cout << stack.pop() << '\n';
	stack.print();
	cout << stack.pop() << '\n';
	stack.print();
	cout << stack.pop() << '\n';
	stack.print();
	cout << stack.pop();

	////////////////////////////////////////////////////////////////////

	cout << "----------------------------------------------" << '\n';

}

void test05() {
	cout << '\n' << '\n' << '\n';
	cout << "			" << " ######## " << "	" << "########" << '\n';
	cout << "			" << "##      ##" << "	" << "##      " << '\n';
	cout << "			" << "##      ##" << "	" << "####### " << '\n';
	cout << "			" << "##      ##" << "	" << "      ##" << '\n';
	cout << "			" << "##      ##" << "	" << "      ##" << '\n';
	cout << "			" << " ######## " << "	" << "####### " << '\n';
	cout << '\n' << '\n' << '\n';

	////////////////////////////////////////////////////////////////////
	string source;
	getline(cin, source);

	eraseWrongSymbols(source);
	const char* infix = source.c_str();
	char* postfix = new char[(strlen(infix) * 2) + 2];
	if (checkWrongSymbols(source)) {
		getPostfixFromInfix(infix, postfix);
		cout << "1) " << infix << " -> " << postfix << '\n';
	}
	else {
		cerr << "your arithmetic expression is uncorrect" << '\n';
	}
	delete[] postfix;
	////////////////////////////////////////////////////////////////////

	cout << "----------------------------------------------" << '\n';
}