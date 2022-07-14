#include <iostream>

//Exercise 3 - Shapes and Areas
//Create two classes : a Circle class and a Square class.For each class, take in the necessary information to calculate its areaand perimeter.Remember to validate input.
//
//Ask the user if they want to create a circle or a square.For their pick, ask the necessary information to create the shape.Then, tell them the areaand the perimeter of their shape.
//
//Your class should have the following methods :
//ExampleShape();
//ExampleShape(/* Params */);
//float GetArea();
//float GetPerimeter();

class Circle {
private:
	float m_radius;
public:
	Circle() {
		m_radius = 1.0f;
	}
	Circle(float radius) {
		m_radius = radius;
	}
	float GetArea() {
		return 3.14159265358979323846f *m_radius * m_radius;
	}
	float GetPerimeter() {
		return 2 * 3.14159265358979323846f * m_radius;
	}
};

class Square {
private:
	float m_sideLength;
public:
	Square() {
		m_sideLength = 1.0f;
	}
	Square(float sideLength) {
		m_sideLength = sideLength;
	}
	float GetArea() {
		return m_sideLength * m_sideLength;
	}
	float GetPerimeter() {
		return 4 * m_sideLength;
	}
};

int main() {
	enum Choices{CircleChoice=1,SquareChoice};
	std::cout << "Welcome to create-a-shape, what type of shape do you want?\n1 - Circle\n2 - Square\nYour choice: ";
	float choice;
	std::cin >> choice;
	while (!std::cin.good() || (choice != 1 && choice != 2) || (choice - floor(choice) != 0.0f)) { //This checks if the choice is an integer 1 or 2
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Enter a valid option: ";
		std::cin >> choice;
	}
	Circle circle;
	Square square;
	switch ((int)choice) {
	case CircleChoice:
		std::cout << "\nEnter radius for your circle: ";
		float radius;
		std::cin >> radius;
		while (!std::cin.good()) { 
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Enter a valid radius for your circle: ";
			std::cin >> radius;
		}
		circle = Circle(radius);
		std::cout << "Your shape's area: " << circle.GetArea() << std::endl;
		std::cout << "Your shape's perimeter: " << circle.GetPerimeter() << std::endl;
		break;
	case SquareChoice:
		std::cout << "\nEnter side length for your square: ";
		float sideLength;
		std::cin >> sideLength;
		while (!std::cin.good()) { 
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Enter a valid side length for your square: ";
			std::cin >> sideLength;
		}
		square = Square(sideLength);
		std::cout << "Your shape's area: " << square.GetArea() << std::endl;
		std::cout << "Your shape's perimeter: " << square.GetPerimeter() << std::endl;
		break;
	}
}