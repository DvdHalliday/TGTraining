#pragma once
#include "Videogame.h"

class FCategory {

private:
	const static int MaxGamesAmount = 30;
	FVideogame Games[MaxGamesAmount];
	int CurrentNumberOfGames;
	std::string Name;

public:
	FCategory();
	FCategory(std::string Name);

	void AddGame(FVideogame Videogame);
	bool CanAddGame() const;

	std::string GetName() const;
	FVideogame GetGame(int Index) const;
	int GetCurrentNumberOfGames() const;
};
