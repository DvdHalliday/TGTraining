#include "Steam.h"

void FSteam::OpenMainManu()
{
	system("cls");

	std::string MainMenuMessage = "Welcome to the Steam store! What would you like to do? \n1 - Add a game\n2 - Modify or create game categories \n3 - View all games \n4 - Exit \nTELL ME: ";
	std::cout << MainMenuMessage;

	enum class MainMenuCommand { AddGameMenu = 1, CategoryManagerMenu, GameDisplayerMenu, Exit };
	MainMenuCommand UserChoice;

	float TemporalUserChoice;
	std::cin >> TemporalUserChoice;

	UserChoice = (MainMenuCommand)ValidateInputAndReturnValidatedInput(TemporalUserChoice, MainMenuMessage, 1, 4);

	switch (UserChoice)
	{
	case MainMenuCommand::AddGameMenu:
		ActiveCommand = MenuCommand::AddGamesMenu;
		break;

	case MainMenuCommand::CategoryManagerMenu:
		ActiveCommand = MenuCommand::CategoryManagerMenu;
		break;

	case MainMenuCommand::GameDisplayerMenu:
		ActiveCommand = MenuCommand::GameDisplayerMenu;
		break;

	case MainMenuCommand::Exit:
		ActiveCommand = MenuCommand::Exit;
		break;

	default:
		std::cout << "MainMenu Error, please contact support";
	}
}

void FSteam::OpenAddGamesMenu()
{
	system("cls");
	// CategoryIndex is set to -1 and that value is representing the uncategorized category
	int CategoryIndex = -1;
	if (!CategoryContainer.IsEmpty())
	{
		CategoryIndex = ChooseCategory();
		system("cls");
	}

	std::string GameName;
	std::cout << "Please insert the name of the game: ";
	std::cin >> GameName;
	GameName = ValidateInputAndReturnValidatedInput(GameName, "Please insert a valid name for the game: ");

	std::string GameStudio;
	std::cout << "Please insert the name of the game studio: ";
	std::cin >> GameStudio;
	GameName = ValidateInputAndReturnValidatedInput(GameName, "Please insert a valid name for the game studio: ");

	float TemporalYear;
	std::cout << "Please insert the year the game was published: ";
	std::cin >> TemporalYear;
	int Year = ValidateInputAndReturnValidatedInput(TemporalYear, "Please insert the actual year the game was published: ", 1900, 2022);

	float TemporalMonth;
	std::cout << "Please insert the month the game was published (1-12): ";
	std::cin >> TemporalMonth;
	int Month = ValidateInputAndReturnValidatedInput(TemporalMonth, "Please insert the actual month the game was published (1-12): ", 1, 12);

	float TemporalDay;
	std::cout << "Please insert the day the game was published: ";
	std::cin >> TemporalDay;
	int Day;

	switch (Month)
	{
	// Case for february
	case 2:
		if (Year % 4 == 0 && Year != 1900)
		{
			Day = ValidateInputAndReturnValidatedInput(TemporalDay, "Please insert the actual day the game was published: ", 1, 29);
		}
		else
		{
			Day = ValidateInputAndReturnValidatedInput(TemporalDay, "Please insert the actual day the game was published: ", 1, 28);
		}
		break;
	// Cases of months that have 31 days
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		Day = ValidateInputAndReturnValidatedInput(TemporalDay, "Please insert the actual day the game was published: ", 1, 31);
		break;
	// Cases of months that have 30 days
	case 4:
	case 6:
	case 9:
	case 11:
		Day = ValidateInputAndReturnValidatedInput(TemporalDay, "Please insert the actual day the game was published: ", 1, 30);
		break;
	default:
		"AddGame Date Error, please contact support";
	}
	
	FVideogame Game = FVideogame(GameName, GameStudio, FDate(Day, Month, Year));

	if (CategoryIndex == -1)
	{
		Uncategorized.AddGame(Game);
	}
	else
	{
		CategoryContainer.GetCategory(CategoryIndex).AddGame(Game);
	}

	ActiveCommand = MenuCommand::MainMenu;
}


int FSteam::ChooseCategory()
{
	if (!AskChooseCategory())
	{
		// Same value as it was, the Uncategorized one
		return -1;
	}

	system("cls");

	std::cout << "Choose one of the following categories:\n" << std::endl;

	for (int i = 1; i <= CategoryContainer.GetCurrentNumberOfCategories(); i++)
	{
		std::cout << i << " - " << CategoryContainer.GetCategory(i - 1).GetName() << std::endl;
	}

	std::cout << "TELL ME: ";
	float TemporalUserChoice;
	std::cin >> TemporalUserChoice;

	return ValidateInputAndReturnValidatedInput(TemporalUserChoice, "TELL ME A VALID OPTION: ", 1, CategoryContainer.GetCurrentNumberOfCategories());
}


bool FSteam::AskChooseCategory()
{
	system("cls");
	std::string AskChooseCategoryMessage = "Would you like to choose a category for your new game? \n1 - Yes\n2 - No\nTELL ME : ";
	std::cout << AskChooseCategoryMessage;

	enum class QuestionCategoryCommand { Yes = 1, No };
	QuestionCategoryCommand UserChoice;

	float TemporalUserChoice;
	std::cin >> TemporalUserChoice;

	UserChoice = (QuestionCategoryCommand)ValidateInputAndReturnValidatedInput(TemporalUserChoice, AskChooseCategoryMessage, 1, 2);

	switch (UserChoice)
	{
	case QuestionCategoryCommand::Yes:
		return true;

	case QuestionCategoryCommand::No:
		return false;

	default:
		std::cout << "AskChooseCategoryMenu Error, please contact support";
		return false;
	}
}

bool FSteam::IsInteger(float Float) const
{
	return (Float - floor(Float)) == 0.f;
}

bool FSteam::IsInRange(float Value, int LowerBound, int UpperBound) const
{
	return Value >= LowerBound && Value <= UpperBound;
}

int FSteam::ValidateInputAndReturnValidatedInput(float Input, std::string Message, int LowerBound, int UpperBound)
{
	while (!std::cin.good() || !IsInteger(Input) || !IsInRange(Input, LowerBound, UpperBound))
	{
		ResetConsoleInputScreen();

		std::cout << Message;
		std::cin >> Input;
	}
	return (int)Input;
}

std::string FSteam::ValidateInputAndReturnValidatedInput(std::string StringInput, std::string Message)
{
	while (!std::cin.good() || StringInput == "" || StringInput == "\n")
	{
		ResetConsoleInputScreen();

		std::cout << Message;
		std::cin >> StringInput;
	}
	return StringInput;
}

void FSteam::ResetConsoleInputScreen()
{
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	system("cls");
}


FSteam::FSteam()
{
	ActiveCommand = MenuCommand::MainMenu;
}

void FSteam::RunSteam()
{
	while (true)
	{
		switch (ActiveCommand)
		{
		case MenuCommand::MainMenu:
			OpenMainManu();
			break;

		case MenuCommand::AddGamesMenu:
			OpenAddGamesMenu();
			break;

		case MenuCommand::CategoryManagerMenu:
			//OpenCategoryManagerMenu();

		case MenuCommand::GameDisplayerMenu:
			//OpenGameDisplayerMenu();
			break;

		case MenuCommand::Exit:
			return;

		default:
			std::cout << "Menu Error, please contact support";
			break;
		}
	}
}
