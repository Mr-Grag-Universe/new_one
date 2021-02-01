//#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>

static void error_brackets1() { std::cout << "Проверьте расстановку скобок."; } // error
static void error_chur1() { std::cout << "Некорректная запись выражения. Проверьте и попробуйте ещё раз."; }
static void error_number1() { std::cout << "Выражение не имеет смысла."; }
static void error_double_operators1() { std::cout << "Проверьте правильность расстановки операторов"; }
static std::string ch_str(char a) { std::string b = ""; b += a; return b; }
static bool checking_char(char a, std::multiset <std::string> operators) {
	if (a <= 'a' || a >= 'z') {
		if (a <= '0' || a >= '9') {
			if (operators.find(ch_str(a)) == operators.end()) {
				return false;
			}
		}
	}
	return true;
}

bool  number_exs() {
	std::string B;
	std::multiset <std::string> operators = { "*", "/", "-", "+", "!", "^" }; //list of operators that may be present
	std::multiset <std::string> functions = { "ln", "log", "lg", "sqrt", "sin" }; //list of functions that may be present

	//setlocale(LC_CTYPE, "rus");
	//std::cout << "Spaces do not affect the result. Case sensitive.";
	std::cout << "Symbols of logical operations:" << std::endl;
	//std::cout << "Операторы: '*', '/', '+', '-', '!', '^'.";
	std::cin.get();
	std::getline(std::cin, B);

	//checking the entered characters in an ordered list
	for (int i = 0, l = B.size(), space = 0, k = 0; i < l; i++) {
		char buf = B[i];
		if (buf >= '0' && buf <= '9') { k++; }
		if (checking_char(buf, operators) || buf == ')' || buf == '(' || buf == ',') {
			if (buf == '(') {
				if (i != l - 1) { if (B[i + 1] == ')') { error_brackets1(); return 0; } }
				else { error_brackets1(); return 0; }
				space++;
			}
			else if (buf == ')') {
				if (i != l - 1) { if (B[i + 1] == '(') { error_brackets1(); return 0; } }
				space--;
			}
			else if (operators.find(ch_str(buf)) != operators.end()) {//проверка расстановки операторов
				if (operators.find(ch_str(B[i + 1])) != operators.end()) {
					if (i != l - 1) {
						if (buf == B[i]) {
							if (buf != '!' && buf != '-' && buf != '+') { error_double_operators1(); return 0; }
						}
						else if ((buf == '-' || buf == '+') && (B[i + 1] != '-')) { error_double_operators1(); return 0; }
						//преобразование унарного минуса
						else if (buf == '-' && B[i + 1] == '-') { auto iter = B.cbegin(); B.erase(iter + i + 1); i--; l--; B[i] = '+'; continue; }
						else if (buf == '+' && B[i + 1] == '-') { auto iter = B.cbegin(); B.erase(iter + i); i--; l--; continue; }
					}
				}//можно дописать про случаи оператор - другое
			}
			continue;
		}
		if (space < 0) { error_brackets1(); return 0; }
		else if (buf == ' ') { auto iter = B.cbegin(); B.erase(iter + i); i--; l--; continue; }
		else { error_chur1(); return 0; }
		if (i == l - 1) {
			if (space) { error_brackets1(); return 0; }
			if (k == 0) { error_number1(); return 0; }
		}//checking the adequacy of parenthesis arrangements and is there number
	}
	for (int i = 0, l = B.size(); i < l; ++i) {//проверка допустимости сочетаний букв

	}

	std::vector <std::string> main;//главный массив из чисел, операторов и функций
	for (auto now : B) { main.push_back(ch_str(now)); }
	for (int i = 0; i < B.size(); i++) {
		if (operators.find(main[i]) != operators.end()) { continue; }
		if (main[i] >= "0" && main[i] <= "9" && i != B.size()-1) { //если это число, то объединить в одно
			for (int j = i + 1; main[j] >= "0" && main[j] <= "9" || main[j] == ","; j++) {//ERROR
				main[i] += main[j];
			}
			i++;
			while (main[i] >= "0" && main[i] <= "9") { auto iter = main.cbegin(); main.erase(iter + i); }
			i--; continue;
		}
	}
	for (auto now : main) { std::cout << now; }
	//проверка соответствия введенных сочетаний дозволенным (склеивание их) и перевод всего массива символов в string
	/*for (int i = 0, l = A.size()-3; i < l; i++) {
		int k = 0;
		char temp1 = A[i], temp2 = A[i + 1], temp3 = A[i + 2], temp4 = A[i + 3];
		if (checking_char(temp1, operators)) {

		}
		if (temp1 >= 'a' && temp1 <= 'z') {
			if (temp1 >= '0' && temp1 <= '9') {
				if (operators.find(ch_str(temp1)) != operators.end()) {
					k++;
				}
			}
		}
		if (temp1 >= 'a' && temp1 <= 'z') {
			if (temp1 >= '0' && temp1 <= '9') {
				if (operators.find(ch_str(temp1)) != operators.end()) {
					k++;
				}
			}
		}
		if (temp1 >= 'a' && temp1 <= 'z') {
			if (temp1 >= '0' && temp1 <= '9') {
				if (operators.find(ch_str(temp1)) != operators.end()) {
					k++;
				}
			}
		}
	}*/

	//if it's only one simbol
	//if (A.size() == 1) {
	//	if (A[0] == '0' || A[0] == '1') { std::cout << A[0] << std::endl; return 1; }
	//	else { error_chur(); return 0; }
	//}
	
	return 1;
}