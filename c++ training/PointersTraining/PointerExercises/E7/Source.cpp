#include <iostream>

/* Exercise 7 - Pointer validity
Declare the following function:
void incrementNumber(int* numberPtr);
The function should increase the value of whatever integer the pointer is pointing to.
In the main function, create an integer and assign it a value. Create an int pointer and initialize it
to be a null pointer. Then, assign the memory address of your integer to it. Pass in your pointer
to the incrementNumber function and print the result to the screen. Run your program.
After making sure the function is working fine, comment out the line where you are initializing
the pointer to the memory address of your int.
Depending on whether you validated the pointer or not, your program may have crashed. This is
one of the dangers of pointers.
Accessing null pointers will crash your application, so it’s important to be sure to add validity
checks when there is even the slightest possibility that the value of a pointer will be null!*/

void IncrementNumber(int* NumberPtr)
{
	(*NumberPtr)++;
}

int main()
{
	int Three = 3;
	int* ThreePointer = nullptr;

	ThreePointer = &Three;
	if (ThreePointer)
	{
		IncrementNumber(ThreePointer);
	}
	std::cout << "The result is " << Three << std::endl;
}
