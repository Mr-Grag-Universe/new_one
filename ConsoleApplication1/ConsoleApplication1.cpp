#include <iostream>
#include <string>
#include "translator_str_int.h"

int main()
{
	//the begining of work
	std::cout << "Hello!" << std::endl;
	std::string temp;
	while (temp != "START") {
	std::cout << "Input 'START' if you want to start work with calculator, and 'FINISH' otherwise.";
	std::cin >> temp;
	if (temp == "FINISH") { return 0; }
	else if (temp != "START") { std::cout << "The command is not recognized. Please, repeat."; }
	}

	std::cout << "Good time of day! We glad to see you in our application." << std::endl;
	std::cout << "Chouse, please, what do you want to do now.";
	std::cout << "'1' - Calculate the value of a given expression." << std::endl;

	int number_of_the_work;
	std::cin >> temp;
	translator(temp,number_of_the_work);

	switch (number_of_the_work)
	{
		case '1':
			//Calculation();
			break;
	}

	return 0;
}