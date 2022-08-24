#include <iostream>

/* Create a program that will ask the user for an integer value. Assign the value to an integer
variable.
Then, create an int* variable and assign it to the memory address of the integer variable.
Ask the user to enter a new value for the variable. Then, using only the pointer variable, change
the value of the integer variable to the new value.
Print the resulting value of variable a.*/

int main()
{
	std::cout << "Please enter a value for variable A: ";

	int A;
	std::cin >> A;

	std::cout << "The value of variable A is now " << A << std::endl << std::endl;

	std::cout << "Please enter a new value for variable A: ";

	int* APointer = &A;
	std::cin >> *APointer;

	std::cout << "The value of variable A is now " << A << std::endl << std::endl;

	std::cout << "Fun fact: I didn’t have to touch A directly to change its value :)" << std::endl;
}