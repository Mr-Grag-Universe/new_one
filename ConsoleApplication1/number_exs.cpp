#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "error.h"

std::string ch_str(char a) { std::string b = ""; b += a; return b; }
bool checking_char(char a, std::multiset <std::string> operators) {
	if (a <= 'a' || a >= 'z') {
		if (a <= '0' || a >= '9') {
			if (operators.find(ch_str(a)) == operators.end()) {
				return false;
			}
		}
	}
	return true;
}

bool number_exs() {
	std::string A;
	std::multiset <std::string> operators = { "*", "/", "-", "+", "!", "^" }; //list of operators that may be present
	std::multiset <std::string> functions = { "ln", "log", "lg", "sqrt", "sin" }; //list of functions that may be present

	setlocale(LC_CTYPE, "rus");
	std::cout << "Spaces do not affect the result. Case sensitive.";
	std::cout << "Symbols of logical operations:" << std::endl;
	std::cout << "Операторы: '*', '/', '+', '-', '!', '^'.";
	std::cin.get();
	std::getline(std::cin, A);

	//checking the entered characters in an ordered list
	for (int i = 0, l = A.size(), space = 0, k = 0; i < l; i++) {
		char buf = A[i];
		if (buf >= '0' && buf <= '9') { k++; }
		if (checking_char(buf, operators) || buf == ')' || buf == '(' || buf == ',') {
			if (buf == '(') {
				if (i != l - 1) { if (A[i + 1] == ')') { error_brackets(); return 0; } }
				else { error_brackets(); return 0; }
				space++;
			}
			else if (buf == ')') {
				if (i != l - 1) { if (A[i + 1] == '(') { error_brackets(); return 0; } }
				space--;
			}
			else if (operators.find(ch_str(buf)) != operators.end()) {//проверка расстановки операторов
				if (operators.find(ch_str(A[i + 1])) != operators.end()) {
					if (i != l - 1) {
						if (buf == A[i]) {
							if (buf != '!' && buf != '-' && buf != '+') { error_double_operators(); return 0; }
						}
						else if ((buf == '-' || buf == '+') && (A[i + 1] != '-')) { error_double_operators(); return 0; }
						//преобразование унарного минуса
						else if (buf == '-' && A[i + 1] == '-') { auto iter = A.cbegin(); A.erase(iter + i + 1); i--; l--; A[i] = '+'; continue; }
						else if (buf == '+' && A[i + 1] == '-') { auto iter = A.cbegin(); A.erase(iter + i); i--; l--; continue; }
					}
				}//можно дописать про случаи оператор - другое
			}
			continue;
		}
		if (space < 0) { error_brackets(); return 0; }
		else if (buf == ' ') { auto iter = A.cbegin(); A.erase(iter + i); i--; l--; continue; }
		else { error_chur(); return 0; }
		if (i == l - 1) {
			if (space) { error_brackets(); return 0; }
			if (k == 0) { error_number(); return 0; }
		}//checking the adequacy of parenthesis arrangements and is there number
	}
	for (int i = 0, l = A.size(); i < l; ++i) {//проверка допустимости сочетаний букв

	}

	std::vector <std::string> main;//главный массив из чисел, операторов и функций
	for (auto now : A) { main.push_back(ch_str(now)); }
	for (int i = 0, l = A.size(); i < l; i++) {
		if (operators.find(main[i]) != operators.end()) { continue; }
		if (main[i] >= "0" && main[i] <= "9") { //если это число, то объединить в одно
			for (int j = i + 1; main[j] >= "0" && main[j] <= "9" || main[j] == ","; j++) {
				main[i] += main[j];
			}
			i++;
			while (main[i] >= "0" && main[i] <= "9") { auto iter = main.cbegin(); main.erase(iter + i); l--; }
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