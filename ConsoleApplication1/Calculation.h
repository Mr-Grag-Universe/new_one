#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "logic_exs.cpp"

void Calculation() {
	//explain rules
	std::cout << "Please, enter your expression using following rules." << std::endl;
	std::cout << "" << std::endl;
	
	//entering number of the operation
	std::string number_str;
	std::cin >> number_str;
	int number = 0;
	while (!translator(number_str, number)) {
		std::cout << "Ånter a number,please." << std::endl;
		std::cin >> number_str;
	};

	//doing
	bool main_bool = false;
	switch (number){
		case 1: //if it's logic ecspression
			while (!logic_exs()) {
				std::cout << "Enter your logic ecspression." << std::endl;
			}
			break;
		case 2: //if it's usual number expression
			while (1) {
				
			}
			break;
	}
}