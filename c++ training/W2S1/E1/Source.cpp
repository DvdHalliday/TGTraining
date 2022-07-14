#include <iostream>

//Exercise 1 - Understanding classes
//Create a class called FirstClass with a public constructor and destructor.Have the constructor output “I’m in the constructor!” and have the destructor output “I’m in the destructor!”.Then, instantiate 5 classes and run your program, are the constructorand destructor calls where you expected them to be ?
//
//Now create a loop of at least five iterations.For each iteration, instantiate your class once.Run your program, are the constructorand destructor calls where you expected them to be ?


class FirstClass {
public:
	FirstClass() {
		std::cout << "I'm in the constructor!" << std::endl;
	}

	~FirstClass() {
		std::cout << "I'm in the destructor!" << std::endl;
	}
};

void instantiateFiveObjects() {
	FirstClass first;
	FirstClass second;
	FirstClass third;
	FirstClass fourth;
	FirstClass fifth;

}

void instantiateInsideFor(int iterations) {
	for (int i = 0; i < iterations; i++) {
		std::cout << "Iteration number " << i << std::endl;
		FirstClass iterationObject;
	}
}

int main() {
	std::cout << "Let's first call the 5 manually instantiated objects" << std::endl;
	instantiateFiveObjects();
	std::cout << "\nNow let's instantiate them in a for loop" << std::endl;
	instantiateInsideFor(7);
}