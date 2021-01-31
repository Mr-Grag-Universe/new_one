//#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include "error.h"

int resalt(std::string a, std::string b, std::string oper) {
	bool A, B;
	if (a == "1") { A = true; }
	else { A = false; }
	if (b == "1") { B = true; }
	else { B = false; }
	bool res;
	if (oper == "|") { res = A || B; }
	else if (oper == "&") { res = A && B; }
	else if (oper == "~") { res = (!A || B) && (A || !B); }
	else if (oper == "->") { res = !A || B; }
	if (res) { return 1; }
	else { return 0; }
}
void podschet(std::string a, std::string b, std::string oper, std::vector <std::string> & Temp_main, int k) {
	int buf;
	buf = resalt(a, oper, b);//resaut of the logic operation in the number
	auto iter = Temp_main.cbegin();
	Temp_main[k + 1] = std::to_string(buf);
	Temp_main.erase(iter + k + 2);
	Temp_main.erase(iter + k);
}

bool logic_exs() {
	std::string A;
	//setlocale(LC_CTYPE, "rus");
	std::cout << "Enter your boolean expression." << std::endl;
	std::cout << "Spaces do not affect the result. Case sensitive.";
	std::cout << "Symbols of logical operations:" << std::endl;
	std::cout << "|, &, _, ~, ->";
	std::cin.get();
	std::getline(std::cin, A);

	//checking the entered characters in an ordered list
	int space = 0;
	for (int i = 0, l = A.size(); i < l; i++) {
		char buf = A[i];
		if (space < 0) { error_brackets(); return 0; }
		if (buf == '1' || buf == '0' || buf == '&' || buf == '_' || buf == '~' || buf == '>' || buf == '-' || buf == ')' || buf == '(' || buf == '|') {
			if (buf == '(') { space++; }
			if (buf == ')') { space--; }
			continue;
		}
		else if (buf == ' ') { auto iter = A.cbegin(); A.erase(iter + i); i--; l--; }
		else { error_chur(); return 0; }
	}
	if (space) { error_brackets(); return 0; } //checking the adequacy of parenthesis arrangements

	//if it's only one simbol
	if (A.size() == 1) {
		if (A[0] == '0' || A[0] == '1') { std::cout << A[0] << std::endl; return 1; }
		else { error_chur(); return 0; }
	}

	//for (auto now : A) { cout << now << " "; } //checking

	std::multiset <std::string> operators; //list of operators that may be present
	operators = { "&", "_", "->", "~", "|" };
	std::vector <char> Main_temp; //symbols of the expression, it is not yet clear why
	std::vector <std::string> Main; //a vector consisting of operators, variables, and parentheses
	//filling in previous arrays and sets
	for (int i = 0, l = A.size(); i < l; i++) {
		char buf = A[i];
		Main.push_back(""); Main[i] += buf;
		Main_temp.push_back(' '); Main_temp[i] = buf; //?
	}
	//for (auto now : Main) { cout << now << " "; } //checking

	//checking the unpaired characters of operators and variables + character pairing - and > in a single statement
	for (int i = 0, l = Main.size() - 1; i < l; i++) {
		std::string temp1 = "", temp2 = "";
		temp1 += Main[i];
		temp2 += Main[i + 1];
		if (temp1 == temp2 && temp1 == "_") { //if you meet 2 in a row standing minus
			auto iter = Main.cbegin();
			Main.erase(iter + i + 1);
			Main.erase(iter + i);
			if (Main.size() > 1) { temp1 += Main[i]; temp2 += Main[i + 1]; }
			l -= 2; i--; continue;
		}
		//if 00 or 11 or 01 or 10
		if ((Main_temp[i] == '1' || Main_temp[i] == '0')  && (Main_temp[i+1] == '0' || Main_temp[i+1] == '1')) { error_chur(); return 0; }
		//if it's operator (not _)
		if (operators.find(temp1) != operators.end() && operators.find(temp2) != operators.end() && temp1 != "_") { error_chur(); return 0; }
		//if it's '->'
		if (temp1 == "-" && temp2 == ">") {
			auto iter = Main.cbegin();
			Main[i] += temp2; Main.erase(iter + i + 1); l--;
		}
		//cout << Main[i];
	}
	//for (auto now : Main) { cout << now << " "; } //checking

	//the main block of expression processing Main
	//for (auto now : Temp_main) { cout << now << " "; }
		while (Main.size() != 1) {
			auto iter = Main.cbegin();
			if (Main.size() < 3) { //if it is not possible to do the main loop
				if (Main.size() == 2) { //unary minus
					if (Main[1] == "1") { Main[0] = "0"; }//replacing a number with the opposite
					else { Main[0] = "1"; }
					Main.erase(iter + 1);
				}
				else { std::cout << Main[0] << std::endl;  std::cout << "0" << " " << "0" << std::endl << "1" << " " << "1"; return 1; }
			}

			for (int k = 0, l = Main.size(); k < l - 2; k++) {
				std::string temp1, temp2, temp3; //three neighbors of a character or symbol
				temp1 = Main[k]; temp2 = Main[k + 1]; temp3 = Main[k + 2];
				if (temp1 == "_" && (temp2 == "0" || temp2 == "1")) { //unary minus
					while (temp1 == "_") {
						if (temp2 == "1") { Main[k] = "0"; }//replacing a number with the opposite
						else { Main[k] = "1"; }
						Main.erase(iter + k + 1);
						if (k) { k--; }
						temp1 = Main[k]; temp2 = Main[k + 1];
						if (Main.size() == 2) { break; }
					}
					if (Main.size() > 2) { temp3 = Main[k + 2]; }
				}
				if (temp3 == ")" && temp1 == "(") { Main.erase(iter + k + 2); Main.erase(iter + k); break; } //if the sign is in parentheses
				if (operators.find(temp2) != operators.end()) { //if the middle character is the operator
					if (temp1 != ")" && temp3 != "(") {
						if (temp2 == "&") {
							if ((temp1 == "0" || temp1 == "1") && (temp3 == "0" || temp3 == "1")) { //if the extreme characters are numbers
								podschet(temp1, temp2, temp3, Main, k);
								break;
							}
						}
						else if (temp2 == "|") {
							if (k == 0) {
								if (k + 3 == Main.size()) { //if there are 3 characters left
									podschet(temp1, temp2, temp3, Main, k);
									break;
								}
								else {
									if (Main[k + 3] == "&") { continue; } //if on the right is multiplication
									else { //if there is no multiplication on the right
										podschet(temp1, temp2, temp3, Main, k);
										break;
									}
								}
							}
							else { //if the left is not the beginning
								if (k + 3 == Main.size()) { //if the end is on the right
									if (Main[k - 1] == "&") { continue; } //if on the left is multiplication
									else { //if there is no multiplication on the right
										podschet(temp1, temp2, temp3, Main, k);
										break;
									}
								}
								else { //if the right and left are not restricted
									if (Main[k - 1] == "&" || Main[k + 3] == "&") { continue; } //if left or right multiplication
									else { //if there is no multiplication on the right or left
										podschet(temp1, temp2, temp3, Main, k);
										break;
									}
								}
							}
							break;
						}
						else {
							if (k == 0) {
								if (k + 3 == Main.size()) { //if there are 3 characters left
									podschet(temp1, temp2, temp3, Main, k);
									break;
								}
								else {
									if (Main[k + 3] == "&" || Main[k + 3] == "|") { continue; } //if on the right is multiplication
									else { //if there is no multiplication on the right
										podschet(temp1, temp2, temp3, Main, k);
										break;
									}
								}
							}
							else { //if the left is not the beginning
								if (k + 3 == Main.size()) { //if the end is on the right
									if (Main[k - 1] == "&" || Main[k + 3] == "|") { continue; } //if on the left is multiplication
									else { //if there is no multiplication on the right
										podschet(temp1, temp2, temp3, Main, k);
										break;
									}
								}
								else { //if the right and left are not restricted
									if (Main[k - 1] == "&" || Main[k + 3] == "&" || Main[k - 1] == "|" || Main[k + 3] == "|") { continue; } //if left or right multiplication
									else { //if there is no multiplication on the right or left
										podschet(temp1, temp2, temp3, Main, k);
										break;
									}
								}
							}
							break;
						}
					}
					else { continue; }
				}
			}
			//for (auto now : Temp_main) { cout << now << " "; }
		}
		std::cout << Main[0] << " ";

	return true;
}