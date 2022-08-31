#include <iostream>
#include <string>

/* Exercise 5 - Dynamic Allocation for Array Sizes
Create a Student class that contains a char array of size 5 for a name and an int for an age. Ask
the user to enter how many students they want in a class. Then, initialize an array of students in
the heap of exactly the size they asked for. You can now probably tell how dynamic allocation is
useful.
Ask the user for a name and an age for each student and then print them all to the screen. Note
that you won’t be able to use names longer than 4 characters.
Remember to free any allocated memory.*/
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class FStudent
{
private:
	char* Name;
	int Age;

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void SetName(const char* NewName)
	{
		int FullNameSize = std::strlen(NewName) + 1;
		Name = new char[FullNameSize];
		memcpy_s(Name, FullNameSize, NewName, FullNameSize);
	}

public:
	FStudent() : Age(1) {}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	FStudent(char* NewName, int NewAge) : Age(NewAge)
	{
		SetName(NewName);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	~FStudent()
	{
		delete Name;
		Name = nullptr;
	}
	
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const char* GetName() const
	{
		return Name;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const int GetAge() const
	{
		return Age;
	}

};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	char TestName[2] = { 'a', '\0' };
	FStudent* TestStudent = new FStudent(TestName, 4);
	delete TestStudent;

	std::cout << "This happens because we're initializing a built-in type array in the heap memory when we call the SetName function in the constructor." << std::endl;
	std::cout << "However, we're actually never deleting of freeing that heap memory, which we should probably do in a destructor. This is one of the" << std::endl;
	std::cout << "types of memory leaks that we studied in class." << std::endl << std::endl;

	std::cout << "How many students do you want? ";

	int NumberOfStudents;
	std::cin >> NumberOfStudents;

	FStudent* Students = new FStudent[NumberOfStudents];

	std::cout << "You now have " << NumberOfStudents << " students!" << std::endl << std::endl;

	for (int i = 0; i < NumberOfStudents; i++)
	{
		std::cin.ignore(500, '\n');

		std::cout << "Enter a name for student #" << i + 1 << ": ";
		char TemporaryStudentName[32];
		std::cin.getline(TemporaryStudentName, 32, '\n');

		std::cout << "Enter the age of student #" << i + 1 << ": ";
		int StudentAge;
		std::cin >> StudentAge;

		Students[i] = FStudent(TemporaryStudentName, StudentAge);
		std::cout << std::endl << std::endl;
	}

	std::cout << "Here are your students:" << std::endl << std::endl;

	for (int i = 0; i < NumberOfStudents; i++)
	{
		std::cout << "Student " << i + 1 << std::endl << "Name: " << Students[i].GetName() << std::endl << "Age: " << Students[i].GetAge() << std::endl << std::endl;
	}

	delete[] Students;
	Students = nullptr;
}