#pragma once
#include "CategoryContainer.h"



class FSteam {
private:
	FCategoryContainer CategoryContainer;
	FCategory Uncategorized = FCategory("Uncategorized");

	enum class MenuCommand
	{
		MainMenu = 1,
		AddGamesMenu,
		CategoryManagerMenu,
		GameDisplayerMenu,
		Exit
	};
	MenuCommand ActiveCommand;
	
	void OpenMainManu();
	void OpenAddGamesMenu();
	void OpenCategoryManagerMenu();
	void OpenGameDisplayerMenu();

	bool IsInteger(float Float) const;
	bool IsInRange(float Value, int LowerBound, int UpperBound) const;
	int ValidateInputAndReturnValidatedInput(float FirstInput, std::string Message, int LowerBound, int UpperBound);
	std::string ValidateInputAndReturnValidatedInput(std::string StringInput, std::string Message);

	void ResetConsoleInputScreen();

	int ChooseCategory();
	bool AskChooseCategory();

	void OpenCreateCategory();
	void OpenRemoveCategory();

public:
	FSteam();
	void RunSteam();

};