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
	FDate(const int& NewDay, const int& NewMonth, const int& NewYear);

	FDate(const FDate& Other);
	~FDate() {};

	void SetDate(const int& Day, const int& Month, const int& Year);

	const int& GetDay() const;
	const int& GetMonth() const;
	const int& GetYear() const;
	bool IsValid() const;

	std::string ToFormattedString() const;
};