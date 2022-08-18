#pragma once
#include "Videogame.h"

class FCategory 
{
private:
	const static int MaxGamesAmount = 30;
	FVideogame Games[MaxGamesAmount];
	int CurrentNumberOfGames = 0;
	std::string Name = "Default name";

public:
	FCategory() {}
	FCategory(const std::string NewName);

	void AddGame(const FVideogame Videogame);
	bool IsFull() const;

	std::string GetName() const;
	FVideogame GetGame(const int Index) const;
	int GetCurrentNumberOfGames() const;
};
