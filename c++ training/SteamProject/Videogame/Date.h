#pragma once
#include<iostream>
#include<string>

class FDate {
private:
	int Day;
	int Month;
	int Year;
public:
	FDate();
	FDate(int Day, int Month, int Year);

	void SetDate(int Day, int Month, int Year);

	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;

	std::string ToFormattedString() const;
};