#include <iostream>

int main()
{
	std::cout << "Please enter a number: ";

	int IntVariable;
	std::cin >> IntVariable;

	std::cout << "The value of your variable is " << IntVariable << "." << std::endl;
	std::cout << "The memory address where your variable is stored is " << &IntVariable << std::endl << std::endl;

	std::cout << "Please enter another number: ";

	std::cin >> IntVariable;

	std::cout << "The value of your variable is " << IntVariable << "." << std::endl;
	std::cout << "The memory address where your variable is stored is " << &IntVariable << std::endl << std::endl;

	std::cout << "Please enter one more number: ";

	int AnotherIntVariable;
	std::cin >> AnotherIntVariable;

	std::cout << "The value of your variable is " << AnotherIntVariable << "." << std::endl;
	std::cout << "The memory address where your variable is stored is " << &AnotherIntVariable << std::endl;
}