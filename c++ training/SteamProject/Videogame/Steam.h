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

	bool IsInteger(const float& Float) const;
	bool IsInRange(const float& Value, const int& LowerBound, const int& UpperBound) const;
	void ValidateInput(int& OutInput, const std::string& Message, const int& LowerBound, const int& UpperBound) const;
	void ValidateInput(std::string& OutInput, const std::string& Message) const;

	void ResetConsoleInputScreen() const;

	const int& ChooseCategory() const;
	const bool& AskChooseCategory() const;

	void RequestEnter() const;

	const int& GetValidDay(const int& Month, const int& Year) const;

	void OpenCreateCategory();
	void OpenRemoveCategory();

public:
	FSteam();
	FSteam(const FSteam& Other);
	~FSteam() {}

	void RunSteam();

};