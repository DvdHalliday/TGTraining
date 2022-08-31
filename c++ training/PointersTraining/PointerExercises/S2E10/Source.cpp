#include <iostream>
#include "ClassA.h"
#include "ClassB.h"


int main()
{
	FClassA classA;
	FClassB classB;

	std::cout << "Well, I think this is happening because the linker simply can't tell whether the ClassA or the ClassB were first declared." << std::endl;
	std::cout << "This is basically a chicken or egg situation. You cannot have one without the other one at least being declared beforehand." << std::endl;
	std::cout << "The error messages are not helpful but this is how C++ tries to deal with stuff it doesn't quite know," << std::endl;
	std::cout << "So since it doesn't really know what FCLassB strictly is, it tries to tell you to add a semicolon before everything goes wrong," << std::endl;
	std::cout << "and right after that it kinda tries to cast the objects to an int but still fails in its attempt." << std::endl << std::endl;

	std::cout << "I think forward declarations are really useful optimization-wise. Having worked in compilers a bit in the past I can really see" << std::endl;
	std::cout << "why using a forward declaration could be used on high performance when implemented with look aheads." << std::endl;
	std::cout << "Also, when dealing with OOP in Java I often found myself in one of these cyclic reference situations, and usually ended up" << std::endl;
	std::cout << "trying to work a way around it just to avoid that sort of conundrum." << std::endl << std::endl;

	std::cout << "I guess this is happening due to the fact that creating a pointer is easy enough, you only really need the space of the pointer" << std::endl;
	std::cout << "to be initialized, which will always be, I think, in this computer, 8 bytes. If you try to initializa an object, now that would be" << std::endl;
	std::cout << "trouble, for even though you were already promised that an object as such exists, you really don't know further information about it," << std::endl;
	std::cout << "you have no idea of its size, members, methods." << std::endl;

	return 0;
}