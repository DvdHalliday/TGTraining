#include "Category.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FCategory::FCategory() : Name("Default Name"), CurrentNumberOfGames(0)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FCategory::FCategory(const std::string NewName) : Name(NewName), CurrentNumberOfGames(0)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FCategory::FCategory(const FCategory& Other) : Name(Other.Name), CurrentNumberOfGames(Other.CurrentNumberOfGames)
{
	memcpy_s(Games, sizeof Games, Other.Games, sizeof Other.Games);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FCategory::AddGame(const FVideogame& Videogame)
{
	if (!IsFull())
	{
		// This adds the game in the current CurrentNumberOfGames position and after that increases its value adding 1
		Games[CurrentNumberOfGames++] = Videogame;
		return;
	}

	std::cout << "Full category Error, please contact support" << std::endl;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FCategory::IsFull() const
{
	return CurrentNumberOfGames >= MaxGamesAmount;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const std::string& FCategory::GetName() const
{
	return Name;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FCategory::GetGameAt(const int Index, FVideogame& OutVideogame) const
{
	if (Index >= 0 && Index < CurrentNumberOfGames)
	{
		OutVideogame = Games[Index];
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int FCategory::GetCurrentNumberOfGames() const
{
	return CurrentNumberOfGames;
}
