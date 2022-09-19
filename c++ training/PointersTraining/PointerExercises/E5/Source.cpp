#include <iostream>

/* Exercise 5 - Pointers and Arrays
Watch this extra resource video before starting: Link
Arrays are just values that are stored in a contiguous block of memory. That means that an
array variable is pretty much just a pointer that points to the first element of the array. You could
handle it the same way if you used a pointer directly.
Create a program where you declare an array of 10 integers. Then, using a for loop, access
every entry of the array by index and print the sum of all elements to the console.
Then, declare an int pointer and assign the array variable to this pointer (you don’t need to get
the memory address from the array variable, you can assign it directly).
Now, loop through the array, but this time instead of accessing the array elements from the
array itself, use the pointer variable. You can access the values in the same exact way you
accessed them when using an array. Print the sum to the console again.
Finally, make your loop iterate more times than the size of the array (something like 35
iterations) and print the sum of the value you get for all iterations. What’s the result? Does it
make sense?
Página 1 de 5Section 1 - PointersObjectiveWe’ll explore what makes c++ so powerful: pointers!InstructionsPlease take a look at your resources. Then, create a Visual Studio Solution and create aseparate project for each of the following exercises. Add this solution to a local git repositoryand create a code review for each finished project.NOTE: Method examples don’t have const specifiers, but you should maintain constcorrectness.ResourcesRandom Youtube ChannelsPlease take a look at the following videos:- Why Do Computers Use 1’s and 0’s? Binary and Transistors Explained. (Link)- Memory in a computer system (Link) (The visual quality of this video is terrible, sorry :p)The Cherno C++ Series (Link)Please take a look at the following video by the Cherno:- POINTERS in C++ExercisesExercise 1 - Understanding Memory AddressesCreate a program that will ask the user to enter an integer and assign the given value to avariable. Then, print the value to the console, and print the memory address of that variable.Then, ask for another value and assign that value to the same variable. Print the value and thememory address to the console.Finally, ask for one more value. This time, assign the value to a different variable. Print thevalue and the memory address to the console. Do the results make sense to you?
Página 2 de 5Example outputPlease enter a number: 55The value of your variable is 55.The memory address where your variable is stored is 0x7ffed6d51c70Please enter another number: 123The value of your variable is 123.The memory address where your variable is stored is 0x7ffed6d51c70Please enter one more number: 66The value of your variable is 66.The memory address where your variable is stored is 0x7ffed6d51c74Exercise 2 - Understanding PointersCreate a program that will ask the user for an integer value. Assign the value to an integervariable.Then, create an int* variable and assign it to the memory address of the integer variable.Ask the user to enter a new value for the variable. Then, using only the pointer variable, changethe value of the integer variable to the new value.Print the resulting value of variable a.Example outputPlease enter a value for variable a: 35The value of variable a is now 35Please enter a new value for variable a: 99The value of variable a is now 99Fun fact: I didn’t have to touch a directly to change its value :)Exercise 3 - Understanding Pointers 2
Página 3 de 5Create a program that will ask the user to enter two integers and assign the given values to twoseparate integers.Declare an int* variable and assign it to the memory address of the first integer. Now, using onlythe pointer variable, print the value of the first integer and its memory address. Additionally, printthe value and the memory address of the pointer variable.Then, assign the memory address of the second integer to the same pointer variable. Do thesame thing as before: using only the pointer variable, print the value of the integer, its memoryaddress, and the value and memory address of the pointer variable.Do the results make sense to you?Example outputPlease enter a value for variable a: 15Please enter a value for variable b: 36Using pointer variable p, I’ve determined that:The value of a is 15The memory address of variable a is 0x7ffdf1c96e10The value of variable p is 0x7ffdf1c96e10The memory address of variable p is 0x7ffdf1c96e10Using the same pointer variable p, I’ve also determined that:The value of b is 36The memory address of variable b is 0x7ffdf1c96e0cThe value of variable p is 0x7ffdf1c96e0cThe memory address of variable p is 0x7ffdf1c96e0cExercise 4 - Understanding Pointers 3Create a program where you declare an int variable and initialize it to whatever value you want.Print the value to the console.Then, create two int pointer variables that point to the variable you just created.Dereference the first pointer and add one to the dereferenced value. Do the same thing with thesecond pointer. Print the final value of your initial variable. Do these results make sense to you?Example outputThe value of my variable is 5.The value of my variable after the pointer stuff I did is 7.
*/

int main()
{
	int IntegerArray[10] = { 25, 20, 15,15,36,89,11,5,9,56 };

	std::cout << "When I use this array: " << std::endl;

	for (int Value : IntegerArray)
	{
		std::cout << Value << " ";
	}
	std::cout << std::endl << std::endl;

	int SumArray = 0;

	for (int Value : IntegerArray)
	{
		SumArray += Value;
	}
	std::cout << "This is the sum when I loop through the array:" << std::endl << SumArray << std::endl << std::endl;

	int SumPointer = 0;

	for (int* ArrayPointer = IntegerArray; ArrayPointer < IntegerArray + 10; ArrayPointer++)
	{
		SumPointer += *ArrayPointer;
	}
	std::cout << "This is the sum when I loop through the array:" << std::endl << SumPointer << std::endl << std::endl;

	int SumPointerOuttaBounds = 0;

	for (int* ArrayPointer = IntegerArray; ArrayPointer < IntegerArray + 20; ArrayPointer++)
	{
		SumPointerOuttaBounds += *ArrayPointer;
	}
	std::cout << "This is the sum when I loop through the array:" << std::endl << SumPointerOuttaBounds << std::endl << std::endl;

}