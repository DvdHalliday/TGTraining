#include <iostream>

//Create a printer class.This class should allow you to store a string and then output it in different formats.Ask the user to input a string and then show what your printer can do!Remember to use char arrays instead of stringsand avoid the std namespace.
//
//You class should have the following methods :
//Printer();
//Printer(std::string outputString);
//void Print();
//void PrintReversed();
//void PrintSpaced(int spaces);
//void PrintVertically();


class Printer {
private:
	char m_outputString[60];
	void Filler(const char newString[]) {
		for (int i = 0; i < std::strlen(newString)+1; i++) {
			m_outputString[i] = newString[i];
		}
	}
public:
	Printer() {
		Filler("Hello!");
	}
	Printer(char outputString[]) {
		Filler(outputString);
	}
	void Print() {
		std::cout << m_outputString << std::endl;
	}
	void PrintReversed() {
		char reversedString[60];
		for (int i = 0; i < std::strlen(m_outputString); i++) {
			reversedString[std::strlen(m_outputString) - i - 1] = m_outputString[i];
		}
		reversedString[std::strlen(m_outputString)] = '\0';
		std::cout << reversedString << std::endl;
	}
	void PrintSpaced(int spaces) {
		char spacing[10] = "";
		for (int i = 0; i < spaces; i++) {
			spacing[i] = ' ';
		}
		spacing[spaces] = '\0';
		for (int j = 0; j < std::strlen(m_outputString); j++) {
			std::cout << m_outputString[j] << spacing;
		}
		std::cout << std::endl;
	}
	void PrintVertically() {
		for (int j = 0; j < std::strlen(m_outputString); j++) {
			std::cout << m_outputString[j] << std::endl;
		}
	}
};

int main() {
	std::cout << "Welcome! Please enter a string: ";
	char messagePassed[60];
	std::cin.getline(messagePassed,60,'\n');
	Printer myPrinter = Printer(messagePassed);
	myPrinter.Print();
	myPrinter.PrintReversed();
	myPrinter.PrintSpaced(9);
	myPrinter.PrintVertically();
}