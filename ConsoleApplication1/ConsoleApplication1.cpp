#include <iostream>
#include <string>

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
	
}