#pragma once
#include <iostream>
#include "Date.h"

class FVideogame
{
private:
	std::string Name;
	std::string Studio;
	FDate Date;

public:
	FVideogame() {}
	FVideogame(const std::string Name, const std::string Studio, const FDate Date);

	bool IsValid() const;

	std::string GetFormattedDate() const;
	std::string GetName() const;
	std::string GetStudio() const;
};
