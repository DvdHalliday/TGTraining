#include "Category.h"

FCategory::FCategory() : Name("Default Name"), CurrentNumberOfGames(0)
{
}

FCategory::FCategory(std::string NewName) : Name(NewName), CurrentNumberOfGames(0)
{
}

void FCategory::AddGame(FVideogame Videogame)
{
	// This adds the game in the current CurrentNumberOfGames position and after that increases its value adding 1
	Games[CurrentNumberOfGames++] = Videogame;
}

bool FCategory::CanAddGame() const
{
	return CurrentNumberOfGames < MaxGamesAmount;
}

std::string FCategory::GetName() const
{
	return Name;
}

FVideogame FCategory::GetGame(int Index) const
{
	if (Index >= 0 && Index < CurrentNumberOfGames)
	{
		return Games[Index];
	}
	return FVideogame();
}

int FCategory::GetCurrentNumberOfGames() const
{
	return CurrentNumberOfGames;
}
