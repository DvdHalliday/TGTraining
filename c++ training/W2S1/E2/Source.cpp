#include <iostream>
#include <string>

//Exercise 2 - Military Clock
//Create a class called MilitaryClock that stores and displays the military time.
//
//Your class should contain the following constructors and methods :
//	MilitaryClock();
//MilitaryClock(short hours, short minutes);
//void SetTime(short hours, short minutes);
//void DisplayTime();
//
//Here’s an example of how the class could be used :
//MilitaryClock clock;
//clock.Display();
//clock = MilitaryClock(7, 0);
//clock.Display();
//clock.SetTime(12, 15);
//clock.Display();
//
//Don’t forget that military time is displayed as hhmm so add a preceding 0 before hours / minutes if their value is less than 10.

class MilitaryClock {
private:

	short m_hours, m_minutes;

public:

	MilitaryClock() {
		m_hours = 0;
		m_minutes = 0;
	}

	MilitaryClock(short hours, short minutes) {
		m_hours = hours;
		m_minutes = minutes;
	}

	void SetTime(short hours, short minutes) {
		m_hours = hours;
		m_minutes = minutes;
	}

	void Display() const{
		std::cout << GetAsFourDigitString() << std::endl;
	}

	std::string GetAsFourDigitString() const{
		std::string formattedString = "";
		if (m_hours < 10) formattedString += '0';
		formattedString += std::to_string(m_hours);
		if (m_minutes < 10) formattedString += '0';
		formattedString += std::to_string(m_minutes);
		return formattedString;
	}

};

int main() {
	MilitaryClock clock;
	clock.Display();
	clock = MilitaryClock(7, 0);
	clock.Display();
	clock.SetTime(12, 15);
	clock.Display();
}