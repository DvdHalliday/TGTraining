#pragma once
#include "CategoryContainer.h"



class FSteam 
{
private:
	FCategoryContainer CategoryContainer;
	FCategory Uncategorized = FCategory("Uncategorized");

	int NumberOfGames;

	enum class EMenuCommand
	{
		MainMenu = 1,
		AddGamesMenu,
		CategoryManagerMenu,
		GameDisplayerMenu,
		Exit
	};
	EMenuCommand ActiveCommand;
	
	void OpenMainMenu();
	void OpenAddGamesMenu();
	void OpenCategoryManagerMenu();
	void OpenGameDisplayerMenu();

	bool IsInteger(const float Float) const;
	bool IsInRange(const float Value, const int LowerBound, const int UpperBound) const;
	int GetValidatedInput(const std::string Message, const int LowerBound, const int UpperBound) const;
	std::string GetValidatedInput(const std::string Message) const;

	void ResetConsoleInputScreen() const;

	int ChooseCategory() const;
	bool AskChooseCategory() const;

	void RequestEnter() const;

	int GetValidDay(const int Month, const int Year) const;

	void OpenCreateCategory();
	void OpenRemoveCategory();

public:
	FSteam();
	void RunSteam();

};