#include "Videogame.h"

FVideogame::FVideogame() : Name(""), Studio(""), Date(FDate())
{
}

FVideogame::FVideogame(std::string NewName, std::string NewStudio, FDate NewDate) : Name(NewName), Studio(NewStudio), Date(NewDate)
{
}

bool FVideogame::IsValid() const
{
	bool bIsValidDate = Date.GetDay() > 0 && Date.GetDay() < 32 &&
		Date.GetMonth() > 0 && Date.GetMonth() < 13 &&
		Date.GetYear() > 1900 && Date.GetDay() < 2023;
	return (Name != "") && (Studio != "") && bIsValidDate;
}

std::string FVideogame::GetFormattedDate() const
{
	return Date.ToFormattedString();
}

std::string FVideogame::GetName() const
{
	return Name;
}

std::string FVideogame::GetStudio() const
{
	return Studio;
}