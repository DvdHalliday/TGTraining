#include <iostream>

/*	Exercise 1 - Understanding Memory Addresses
Create a program that will ask the user to enter an integer and assign the given value to a
variable.Then, print the value to the console, and print the memory address of that variable.
Then, ask for another valueand assign that value to the same variable.Print the valueand the
memory address to the console.
Finally, ask for one more value.This time, assign the value to a different variable.Print the
valueand the memory address to the console.Do the results make sense to you ?*/

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