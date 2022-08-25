#include <iostream>

/* Exercise 4 - Dynamic Allocation Dangers: Dangling Pointers
There is another danger when using dynamic memory. Let’s see it:
Allocate an int in the heap and assign it to an int pointer variable. Immediately after that, delete
the allocated memory.
We’ve previously discussed pointer validity. Check the validity of the pointer. If the pointer is
valid, print “The pointer is valid!”. If it’s not, print “The pointer is not valid…”.
Run your program. You’ll see that the pointer is valid. Try accessing the value of whatever the
pointer is pointing to and you’ll most likely crash. You’ve got a false positive in your validation
due to a dangling pointer.
Print to the console why you think this is happening. It’s important to keep in mind that after
freeing memory in the heap, any pointer that was pointing to it should be set to null. From now
on, this will be expected in the exercises.*/


int main()
{
	int* SoonToBeADanglingPointer = new int(1);
	delete SoonToBeADanglingPointer;

	SoonToBeADanglingPointer = nullptr;

	if (SoonToBeADanglingPointer)
	{
		std::cout << *SoonToBeADanglingPointer;
	}

	std::cout << "Well, this is simply happening cause even though the memory was set free again," << std::endl;
	std::cout << "the pointer will still be the same, it will still contain the address of the former" << std::endl;
	std::cout << "integer. It will crash because whatever used to be in that address is now lost, or set to nothing." << std::endl;
	std::cout << "So, if you try to retrieve an integer from what's left there, you're likely gonna' be facing trouble." << std::endl;
}