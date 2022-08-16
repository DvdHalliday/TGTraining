#pragma once
#include<iostream>
#include<string>

class FDate
{
private:
	int Day;
	int Month;
	int Year;
public:
	FDate();
	FDate(const int NewDay, const int NewMonth, const int NewYear);

	void SetDate(const int Day, const int Month, const int Year);

	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;
	bool IsValid() const;

	std::string ToFormattedString() const;
};