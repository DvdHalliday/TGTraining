#include "Date.h"

FDate::FDate()
{
	SetDate(1, 1, 2000);
}

FDate::FDate(int Day, int Month, int Year)
{
	SetDate(Day, Month, Year);
}

void FDate::SetDate(int NewDay, int NewMonth, int NewYear)
{
	Day = NewDay;
	Month = NewMonth;
	Year = NewYear;
}

int FDate::GetDay() const
{
	return Day;
}

int FDate::GetMonth() const
{
	return Month;
}

int FDate::GetYear() const
{
	return Year;
}

std::string FDate::ToFormattedString() const
{
	std::string ReturnString = std::to_string(GetDay()) + "/" + std::to_string(GetMonth()) + "/" + std::to_string(GetYear());
	return ReturnString;
}
