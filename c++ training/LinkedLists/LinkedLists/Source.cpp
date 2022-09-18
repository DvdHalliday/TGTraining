#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include "SinglyLinkedList.h"

template<typename T>
void PrintList(TSLList<T>& List)
{
	std::cout << "Size: " << List.GetSize() << "\t\tList Contents: { ";
	for (const T& Element : List)
	{
		std::cout << Element << ' ';
	}
	std::cout << "}\n";
}

template<typename T>
void PrintHead(const TSLList<T>& List, const std::string& CorrectHead)
{
	std::cout << "Head is:\t" << List.GetHead() << (List.GetHead() == CorrectHead ? " CORRECT" : " INCORRECT") << std::endl;
}

template<typename T>
void PrintTail(const TSLList<T>& List, const std::string& CorrectTail)
{
	std::cout << "Tail is:\t" << List.GetTail() << (List.GetTail() == CorrectTail ? " CORRECT" : " INCORRECT") << std::endl;
}

int main()
{
	// Memory Leak Detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Uncomment the next line if you need to check where a memory leak occurred!
	//_CrtSetBreakAlloc(252); // <--- replace 'Code' with whichever code you saw in the output window

	// Linked List
	std::cout << "*******************************************************************************\n";
	std::cout << "**                           Linked List Test!                               **\n";
	std::cout << "*******************************************************************************\n\n";

	// Definitions
	TSLList<std::string> List;

	// Test 1
	std::cout << "\n*** Test 1 ***\n";

	PrintList(List);

	List.AddHead("Correctly");
	PrintList(List);
	List.AddHead("Read");
	PrintList(List);
	List.AddHead("Should");
	PrintList(List);
	List.AddHead("This");
	PrintList(List);

	PrintHead(List, "This");
	PrintTail(List, "Correctly");

	std::cout << std::endl;

	List.Clear();
	PrintList(List);

	List.AddTail("This");
	PrintList(List);
	List.AddTail("Should");
	PrintList(List);
	List.AddTail("Read");
	PrintList(List);
	List.AddTail("Correctly");
	PrintList(List);

	PrintHead(List, "This");
	PrintTail(List, "Correctly");

	std::cout << std::endl;

	List.Clear();
	List.AddHead("Head");
	PrintList(List);

	PrintHead(List, "Head");
	PrintTail(List, "Head");

	std::cout << std::endl;

	List.Clear();
	List.AddTail("Tail");
	PrintList(List);

	PrintHead(List, "Tail");
	PrintTail(List, "Tail");
	List.Clear();

	// Test 2
	std::cout << "\n*** Test 2 ***\n";
	std::cout << "Inserting and removing...";

	List.AddTail("This");
	List.AddTail("Is");
	List.AddTail("A");
	List.AddTail("List");

	std::cout << std::endl;
	PrintList(List);

	std::cout << "\nRemoving Is...\n";
	List.Remove(1);
	PrintList(List);

	std::cout << "\nRemoving invalid indices... shouldn't change anything!\n";
	List.Remove(4);
	List.Remove(5);
	List.Remove(6);
	List.Remove(-1);
	List.Remove(-10);
	PrintList(List);

	std::cout << "\nInserting Elements...!\n";
	List.Insert("Is", 0);
	List.Insert("?", 4);
	List.Insert("Dumb", 3);
	PrintList(List);

	std::cout << "\nInserting at invalid indices... shouldn't change anything!\n";
	List.Insert("Shouldn't be here!", 7);
	List.Insert("Shouldn't be here!", 8);
	List.Insert("Shouldn't be here!", -1);
	List.Insert("Shouldn't be here!", -10);
	PrintList(List);

	// Test 3
	std::cout << "\n*** Test 3 ***\n";
	std::cout << "Testing Copy Constructor and Assignment...\n";

	List.Clear();
	List.AddTail("This");
	List.AddTail("Is");
	List.AddTail("A");
	List.AddTail("List");

	std::cout << "Using Copy Constructor...\n";
	TSLList<std::string> Other = List;
	PrintList(List);
	PrintList(Other);

	Other.Clear();
	Other.AddHead("Head");
	List = Other;
	PrintList(List);

	List.Clear();
	Other.Clear();

	List.AddHead("This should be here!");
	Other.AddHead("This should NOT be here!");
	Other = List;
	PrintList(Other);

	TSLList<std::string>* ListPointer = new TSLList<std::string>;
	ListPointer->AddTail("Test");
	ListPointer->AddTail("Pointer");
	ListPointer->AddTail("Contents");

	TSLList<std::string> SomeList(*ListPointer);
	delete ListPointer;
	ListPointer = nullptr;

	PrintList(SomeList);
	SomeList.Clear();
	PrintList(SomeList);
}