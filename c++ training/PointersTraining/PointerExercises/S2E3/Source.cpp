#include <iostream>

/* Exercise 3 - Dynamic Allocation Dangers: Memory Leaks

There are dangers when it comes to allocating memory in the heap. One of these dangers is
memory leaks! When you allocate memory on the heap, you’re promising that you’ll manage
that memory… which means that your memory will outlive its current scope and so you need to
free the memory manually. But what happens when you can’t access the memory anymore?
You won’t be able to deallocate it and you’ll have a memory leak (useless memory that’s not
available for new allocations)
Let’s create a couple of functions that will create memory leaks. Create the following functions:
void MemoryLeak1();
void MemoryLeak2(int* intPtr);
The first function should declare an int pointer and initialize it by allocating an int in the heap.
That’s all the function does.
The second function takes in an int pointer but does the same thing. It should assign an int
allocated in the heap to intPtr. That’s all it needs to do.
In your main function, call the first function. Then, declare an int pointer (initialized to nullptr) and
pass it into the second function.
Then, try to think of a way in which you could free any of that allocated memory inside the main
function. You’ll find that there is no way to do it - you’ve created two memory leaks. These leaks
will live in memory for as long as the program is running and you won’t be able to store any new
data in those memory locations.
Print to the console why each of those functions creates a memory leak.*/

void MemoryLeak1()
{
	int* IntPtr = new int(0);
}

void MemoryLeak2(int* IntPtr)
{
	IntPtr = new int(0);
}

int main()
{
	MemoryLeak1;

	int* IntPtr = nullptr;
	MemoryLeak2(IntPtr);


	std::cout << "The first memory leak is simpler, you're creating an integer in heap memory, and once the function scope's over" << std::endl;
	std::cout << "the variable will be lost for you to access, and so as well for deletion." << std::endl << std::endl;

	std::cout << "As for the second one, it seems to be trickier, I think it all comes down to references," << std::endl;
	std::cout << "when we define a function as such, all we are doing really, is creating a copy of the pointer," << std::endl;
	std::cout << "a copy that is given an adress in the heap memory, so once again, whenever the function scope" << std::endl;
	std::cout << "comes to an end, so will the pointer copy, hence the information of memory that will never" << std::endl;
	std::cout << "be used again, will now be lost for us to delete." << std::endl;
}