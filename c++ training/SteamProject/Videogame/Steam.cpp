#include "Steam.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenMainMenu()
{
	system("cls");

	const std::string MainMenuMessage = "Welcome to the Steam store! What would you like to do? \n1 - Add a game\n2 - Modify or create game categories \n3 - View all games \n4 - Exit \nTELL ME: ";

	enum class EMainMenuCommand { AddGameMenu = 1, CategoryManagerMenu, GameDisplayerMenu, Exit };

	switch ((EMainMenuCommand)GetValidatedInput(MainMenuMessage, 1, 4))
	{
	case EMainMenuCommand::AddGameMenu:
		ActiveCommand = EMenuCommand::AddGamesMenu;
		break;

	case EMainMenuCommand::CategoryManagerMenu:
		ActiveCommand = EMenuCommand::CategoryManagerMenu;
		break;

	case EMainMenuCommand::GameDisplayerMenu:
		ActiveCommand = EMenuCommand::GameDisplayerMenu;
		break;

	case EMainMenuCommand::Exit:
		ActiveCommand = EMenuCommand::Exit;
		break;

	default:
		std::cout << "MainMenu Error, please contact support";
		break;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenAddGamesMenu()
{
	system("cls");

	// CategoryIndex is set to -1 and that value is representing the uncategorized category
	int CategoryIndex = -1;

	CategoryIndex = ChooseCategory();
	system("cls");

	std::string GameName = GetValidatedInput("Please insert the name of the game: ");

	std::string GameStudio = GetValidatedInput("Please insert a valid name for the game studio: ");

	const int Year = GetValidatedInput("Please insert the year the game was published: ", 1900, 2022);

	int Month = GetValidatedInput("Please insert the month the game was published (1-12): ", 1, 12);

	int Day = GetValidDay(Month, Year);

	FVideogame Game = FVideogame(GameName, GameStudio, FDate(Day, Month, Year));

	if (CategoryIndex == -1)
	{
		Uncategorized.AddGame(Game);
	}

	else
	{
		CategoryContainer.AddGameToCategory(CategoryIndex, Game);
	}

	NumberOfGames++;

	ActiveCommand = EMenuCommand::MainMenu;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenCategoryManagerMenu()
{
	system("cls");
	std::string CategoryManagerMessage = "What would you rather do next? \n1 - Add a new category\n2 - Remove a category\n3 - Go back to main menu\nTELL ME : ";
	std::cout << CategoryManagerMessage;

	enum class ECategoryManagerCommand { CreateCategory = 1, RemoveCategory, MainMenu };

	switch ((ECategoryManagerCommand)GetValidatedInput(CategoryManagerMessage, 1, 3))
	{
	case ECategoryManagerCommand::CreateCategory:
		OpenCreateCategory();
		break;

	case ECategoryManagerCommand::RemoveCategory:
		OpenRemoveCategory();
		break;

	case ECategoryManagerCommand::MainMenu:
		ActiveCommand = EMenuCommand::MainMenu;
		return;

	default:
		std::cout << "CategoryManager Error, please contact support";
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenGameDisplayerMenu() {
	system("cls");

	if (NumberOfGames == 0)
	{
		std::cout << "There are currently no games to display. Please type Enter to return to the main menu. ";

		RequestEnter();
		ActiveCommand = EMenuCommand::MainMenu;

		return;
	}

	if (Uncategorized.GetCurrentNumberOfGames() != 0)
	{
		std::cout << "---------------------------------------------------------\n" << "Uncategorized Games\n" << std::endl;
		for (int i = 0; i < Uncategorized.GetCurrentNumberOfGames(); i++)
		{
			FVideogame Game = Uncategorized.GetGame(i);
			std::cout << Game.GetName() << "\t by " << Game.GetStudio() << "\t published on " << Game.GetFormattedDate() << std::endl;
		}
	}

	for (int i = 0; i < CategoryContainer.GetCurrentNumberOfCategories(); i++)
	{
		if (CategoryContainer.GetCategory(i).GetCurrentNumberOfGames() != 0)
		{
			std::cout << "---------------------------------------------------------\n" << CategoryContainer.GetCategory(i).GetName() << " Games\n" << std::endl;

			for (int j = 0; j < CategoryContainer.GetCategory(i).GetCurrentNumberOfGames(); j++)
			{
				FVideogame Game = CategoryContainer.GetCategory(i).GetGame(j);
				std::cout << Game.GetName() << "\t by " << Game.GetStudio() << "\t published on " << Game.GetFormattedDate() << std::endl;
			}
		}
	}

	std::cout << "\nPlease type Enter to return to the previous menu ";

	RequestEnter();

	ActiveCommand = EMenuCommand::MainMenu;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::RequestEnter() const
{
	std::cin.ignore(500, '\n');

	while (std::cin.get() != '\n')
	{
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenCreateCategory()
{
	system("cls");

	if (CategoryContainer.IsFull())
	{
		std::cout << "There is no available space right now to create another category, please type Enter to return to the previous menu";

		RequestEnter();
		ActiveCommand = EMenuCommand::CategoryManagerMenu;

		return;
	}

	std::string CategoryName = GetValidatedInput("Please enter a name for the new category: ");
	FCategory Category(CategoryName);

	CategoryContainer.AddCategory(Category);

	system("cls");

	std::cout << "Category created succesfuly. Please type Enter to return to the previous menu";

	RequestEnter();
	ActiveCommand = EMenuCommand::CategoryManagerMenu;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenRemoveCategory()
{
	system("cls");

	if (CategoryContainer.IsEmpty())
	{
		std::cout << "There is currently no category. Please type Enter to return to the previous menu";

		RequestEnter();
		ActiveCommand = EMenuCommand::CategoryManagerMenu;

		return;

	}

	std::cout << "Choose one of the following options or categories to remove:\n" << std::endl << "0 - Don't remove any category, return to the previous menu" << std::endl;
	for (int i = 1; i <= CategoryContainer.GetCurrentNumberOfCategories(); i++)
	{
		std::cout << i << " - " << CategoryContainer.GetCategory(i - 1).GetName() << std::endl;
	}

	std::cout << std::endl;

	int UserChoice = GetValidatedInput("Please enter a valid choice : ", 0, CategoryContainer.GetCurrentNumberOfCategories());

	if (UserChoice == 0)
	{
		ActiveCommand = EMenuCommand::CategoryManagerMenu;
		return;
	}

	CategoryContainer.RemoveCategory(UserChoice - 1);

	system("cls");


	std::cout << "Category removed succesfully. Please type Enter to return to the previous menu ";

	RequestEnter();
	ActiveCommand = EMenuCommand::CategoryManagerMenu;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int FSteam::ChooseCategory() const
{
	if (CategoryContainer.IsEmpty() || !AskChooseCategory())
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

	return GetValidatedInput("TELL ME: ", 1, CategoryContainer.GetCurrentNumberOfCategories()) - 1;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FSteam::AskChooseCategory() const
{
	system("cls");
	std::string AskChooseCategoryMessage = "Would you like to choose a category for your new game? \n1 - Yes\n2 - No\nTELL ME : ";
	std::cout << AskChooseCategoryMessage;

	enum class EQuestionCategoryCommand { Yes = 1, No };

	switch ((EQuestionCategoryCommand)GetValidatedInput(AskChooseCategoryMessage, 1, 2))
	{
	case EQuestionCategoryCommand::Yes:
		return true;

	case EQuestionCategoryCommand::No:
		return false;

	default:
		std::cout << "AskChooseCategoryMenu Error, please contact support";
		return false;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FSteam::IsInteger(const float Float) const
{
	return (Float - floor(Float)) == 0.f;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FSteam::IsInRange(const float Value, const int LowerBound, const int UpperBound) const
{
	return Value >= LowerBound && Value <= UpperBound;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int FSteam::GetValidatedInput(const std::string Message, const int LowerBound, const int UpperBound) const
{
	std::cout << Message;

	float UserInput;
	std::cin >> UserInput;

	while (!std::cin.good() || !IsInteger(UserInput) || !IsInRange(UserInput, LowerBound, UpperBound))
	{
		ResetConsoleInputScreen();

		std::cout << Message;
		std::cin >> UserInput;
	}
	return (int)UserInput;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::string FSteam::GetValidatedInput(const std::string Message) const
{
	std::cout << Message;

	std::string UserInput;
	std::cin >> UserInput;

	while (!std::cin.good() || UserInput.empty())
	{
		ResetConsoleInputScreen();

		std::cout << Message;
		std::cin >> UserInput;
	}
	return UserInput;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int FSteam::GetValidDay(const int Month, const int Year) const
{
	switch (Month)
	{
		// Case for february
	case 2:
		if (Year % 4 == 0 && Year != 1900)
		{
			return GetValidatedInput("Please insert the day the game was published: ", 1, 29);
		}
		else
		{
			return GetValidatedInput("Please insert the actual day the game was published: ", 1, 28);
		}

		// Cases of months that have 31 days
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return GetValidatedInput("Please insert the day the game was published: ", 1, 31);

		// Cases of months that have 30 days
	case 4:
	case 6:
	case 9:
	case 11:
		return GetValidatedInput("Please insert the day the game was published: ", 1, 30);

	default:
		"AddGame Date Error, please contact support";
		return 1;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::ResetConsoleInputScreen() const
{
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	system("cls");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FSteam::FSteam() : ActiveCommand(EMenuCommand::MainMenu), NumberOfGames(0)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::RunSteam()
{
	while (ActiveCommand != EMenuCommand::Exit)
	{
		switch (ActiveCommand)
		{
		case EMenuCommand::MainMenu:
			OpenMainMenu();
			break;

		case EMenuCommand::AddGamesMenu:
			OpenAddGamesMenu();
			break;

		case EMenuCommand::CategoryManagerMenu:
			OpenCategoryManagerMenu();
			break;

		case EMenuCommand::GameDisplayerMenu:
			OpenGameDisplayerMenu();
			break;

		case EMenuCommand::Exit:
			break;

		default:
			std::cout << "Menu Error, please contact support";
			break;
		}
	}
}
