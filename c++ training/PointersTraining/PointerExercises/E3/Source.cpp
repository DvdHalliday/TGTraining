#include <iostream>

/* Create a program that will ask the user to enter two integers and assign the given values to two
separate integers.
Declare an int* variable and assign it to the memory address of the first integer. Now, using only
the pointer variable, print the value of the first integer and its memory address. Additionally, print
the value and the memory address of the pointer variable.
Then, assign the memory address of the second integer to the same pointer variable. Do the
same thing as before: using only the pointer variable, print the value of the integer, its memory
address, and the value and memory address of the pointer variable.
Do the results make sense to you?*/

int main()
{
	std::cout << "Please enter a value for variable A: ";

	int A;
	std::cin >> A;

	std::cout << "Please enter a value for variable B: ";

	int B;
	std::cin >> B;

	int* P = &A;
	std::cout << "Using pointer variable P, I've determined that:\nThe value of A is " << *P << std::endl;
	std::cout << "The memory address of variable A is " << P << std::endl << "The value of variable P is " << P << std::endl;
	std::cout << "The memory address of variable P is" << &P << std::endl << std::endl;

	P = &B;
	std::cout << "Using pointer variable P, I've determined that:\nThe value of B is " << *P << std::endl;
	std::cout << "The memory address of variable B is " << P << std::endl << "The value of variable P is " << P << std::endl;
	std::cout << "The memory address of variable P is" << &P << std::endl << std::endl;
}