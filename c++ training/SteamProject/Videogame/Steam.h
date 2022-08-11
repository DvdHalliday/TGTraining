#pragma once
#include "CategoryContainer.h"



class FSteam {
private:
	FCategoryContainer CategoryContainer;
	FCategory Uncategorized = FCategory("Uncategorized");

	int NumberOfGames;

	enum class MenuCommand
	{
		MainMenu = 1,
		AddGamesMenu,
		CategoryManagerMenu,
		GameDisplayerMenu,
		Exit
	};
	MenuCommand ActiveCommand;
	
	void OpenMainMenu();
	void OpenAddGamesMenu();
	void OpenCategoryManagerMenu();
	void OpenGameDisplayerMenu();

	bool IsInteger(const float Float) const;
	bool IsInRange(const float Value, const int LowerBound, const int UpperBound) const;
	int ValidateInputAndReturnValidatedInput(float FirstInput, const std::string Message, const int LowerBound, const int UpperBound);
	std::string ValidateInputAndReturnValidatedInput(std::string StringInput, const std::string Message);

	void ResetConsoleInputScreen();

	int ChooseCategory();
	bool AskChooseCategory();

	int GetValidDay(float TemporalDay, const int Month, const int Year);

	void OpenCreateCategory();
	void OpenRemoveCategory();

public:
	FSteam();
	void RunSteam();

};