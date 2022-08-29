#include <iostream>

/* Exercise 5 - Dynamic Allocation for Array Sizes
Create a Student class that contains a char array of size 5 for a name and an int for an age. Ask
the user to enter how many students they want in a class. Then, initialize an array of students in
the heap of exactly the size they asked for. You can now probably tell how dynamic allocation is
useful.
Ask the user for a name and an age for each student and then print them all to the screen. Note
that you won’t be able to use names longer than 4 characters.
Remember to free any allocated memory.*/

class FStudent
{
private:
	std::string Name;
	int Age;

public:
	FStudent() : Age(1) {}
	FStudent(const std::string& NewName, int NewAge) : Name(NewName), Age(NewAge)
	{
	}

	const std::string& GetName() const
	{
		return Name;
	}
	const int GetAge() const
	{
		return Age;
	}
};

int main()
{
	std::cout << "How many students do you want? ";

	int NumberOfStudents;
	std::cin >> NumberOfStudents;

	FStudent* Students = new FStudent[NumberOfStudents];

	std::cout << "You now have " << NumberOfStudents << " students!" << std::endl << std::endl;

	for (int i = 0; i < NumberOfStudents; i++)
	{
		std::cout << "Enter a name for student #" << i+1 << ": ";
		std::string StudentName;
		std::cin >> StudentName;

		std::cout << "Enter the age of student #" << i+1 << ": ";
		int StudentAge;
		std::cin >> StudentAge;

		Students[i] = FStudent(StudentName, StudentAge);
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