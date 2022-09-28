#pragma once
#include "Videogame.h"

class FCategory
{
private:
	const static int MaxGamesAmount = 30;
	FVideogame Games[MaxGamesAmount];
	int CurrentNumberOfGames;
	std::string Name;

public:
	FCategory();
	FCategory(const std::string NewName);

	FCategory(const FCategory& Other);
	~FCategory() {}

	void AddGame(const FVideogame& Videogame);
	bool IsFull() const;

	const std::string& GetName() const;
	bool GetGameAt(const int Index, FVideogame& OutVideogame) const;
	int GetCurrentNumberOfGames() const;
};
