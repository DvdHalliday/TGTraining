#include <iostream>

/* Exercise 2 - Understanding Stack vs Heap
Let’s compare the memory addresses of the stack and the heap.
First, create three int variables called stackInt1, stackInt2, and stackInt3. These variables should
be allocated in the stack. Initialize them to whatever value you want and then print their value
and memory addresses.
Then, create three more int variables and call them healpInt1, heapInt2, and heapInt3. These
variables should be allocated in the heap. Initialize them to whatever value you want and print
their value and memory addresses.
What can you notice from the memory addresses in the stack vs the memory addresses in the
heap? Print the answer to that question to the console (Yep, we’re doing quizzes in exercises
now).
Remember to free any memory you allocate in the heap.*/

int main()
{
	int StackInt1 = 15;
	int StackInt2 = 20;
	int StackInt3 = 16;

	std::cout << "I created three stack variables:\nTheir values are :" << std::endl;
	std::cout << StackInt1 << std::endl << StackInt2 << std::endl << StackInt3 << std::endl;
	std::cout << "Their memory addresses are " << std::endl;
	std::cout << &StackInt1 << std::endl << &StackInt2 << std::endl << &StackInt3 << std::endl << std::endl;

	int* HeapInt1 = new int(36);
	int* HeapInt2 = new int(5);
	int* HeapInt3 = new int(11);

	std::cout << "I created three heap variables:\nTheir values are :" << std::endl;
	std::cout << *HeapInt1 << std::endl << *HeapInt2 << std::endl << *HeapInt3 << std::endl;
	std::cout << "Their memory addresses are " << std::endl;
	std::cout << HeapInt1 << std::endl << HeapInt2 << std::endl << HeapInt3 << std::endl << std::endl;

	delete HeapInt1, HeapInt2, HeapInt3;

	std::cout << "The difference between these memory addresses is: essentially, that the variables that areinitialised and allocated in the stack are " << std::endl;
	std::cout << "being stored continuously one after another, every 4 bytes, which is the size of every integer." << std::endl;
	std::cout << "Heap allocated integers are, on the other hand, given memory locations that seem much more random, there is in fact not necessarilly " << std::endl;
	std::cout << "always much correlation between the variables addresses altogether. They might be near each other, however there will not always be" << std::endl;
	std::cout << "the same distance between one another." << std::endl;
}