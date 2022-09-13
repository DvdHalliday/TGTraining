#include <iostream>

/* Exercise 1 - Useless Program
Create an integer that will instantiate an integer to the heap and assign it whatever value you
like. Print the value of the integer and the memory address of that int.
Remember that when you’re allocating memory in the heap, you need to free it manually. This is
done with the delete keyword. Make sure to free the memory you allocated for your int before
exiting the program.*/

int main()
{
	int* Integer = new int(56);

	std::cout << "I've dynamically allocated an integer. It's value is " << *Integer << " and its memory address is " << Integer << std::endl;

	delete Integer;
}