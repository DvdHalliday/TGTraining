#include "Steam.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenMainMenu()
{
	system("cls");

	const std::string MainMenuMessage = "Welcome to the Steam store! What would you like to do? \n1 - Add a game\n2 - Modify or create game categories \n3 - View all games \n4 - Exit \nTELL ME: ";
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
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
	GameStudio = ValidateInputAndReturnValidatedInput(GameStudio, "Please insert a valid name for the game studio: ");

	float TemporalYear;
	std::cout << "Please insert the year the game was published: ";
	std::cin >> TemporalYear;
	const int Year = ValidateInputAndReturnValidatedInput(TemporalYear, "Please insert the actual year the game was published: ", 1900, 2022);

	float TemporalMonth;
	std::cout << "Please insert the month the game was published (1-12): ";
	std::cin >> TemporalMonth;
	int Month = ValidateInputAndReturnValidatedInput(TemporalMonth, "Please insert the actual month the game was published (1-12): ", 1, 12);

	float TemporalDay;
	std::cout << "Please insert the day the game was published: ";
	std::cin >> TemporalDay;
	int Day = GetValidDay(TemporalDay, Month, Year);

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

	ActiveCommand = MenuCommand::MainMenu;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenCategoryManagerMenu()
{
	system("cls");
	std::string CategoryManagerMessage = "What would you rather do next? \n1 - Add a new category\n2 - Remove a category\n3 - Go back to main menu\nTELL ME : ";
	std::cout << CategoryManagerMessage;

	enum class CategoryManagerCommand { CreateCategory = 1, RemoveCategory, MainMenu };
	CategoryManagerCommand UserChoice;

	float TemporalUserChoice;
	std::cin >> TemporalUserChoice;

	UserChoice = (CategoryManagerCommand)ValidateInputAndReturnValidatedInput(TemporalUserChoice, CategoryManagerMessage, 1, 3);

	switch (UserChoice)
	{
	case CategoryManagerCommand::CreateCategory:
		OpenCreateCategory();
		break;

	case CategoryManagerCommand::RemoveCategory:
		OpenRemoveCategory();
		break;

	case CategoryManagerCommand::MainMenu:
		ActiveCommand = MenuCommand::MainMenu;
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

		std::cin.ignore(500, '\n');
		if (std::cin.peek() == '\n')
		{
			OpenMainMenu();
		}
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

	if (!CategoryContainer.IsEmpty())
	{
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
	}

	std::cout << "\nPlease type Enter to return to the previous menu ";

	std::cin.ignore(500, '\n');
	if (std::cin.peek() == '\n')
	{
		OpenMainMenu();
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenCreateCategory()
{
	system("cls");

	if (CategoryContainer.IsFull())
	{
		std::cout << "There is no available space right now to create another category, please type Enter to return to the previous menu";

		std::cin.ignore(500, '\n');
		if (std::cin.peek() == '\n')
		{
			OpenCategoryManagerMenu();
		}
		return;
	}

	std::cout << "Please enter a name for the new category: ";
	std::string TemporaryCategoryName;
	std::cin >> TemporaryCategoryName;

	std::string CategoryName = ValidateInputAndReturnValidatedInput(TemporaryCategoryName, "Please enter a valid name for the new category: ");
	FCategory Category(CategoryName);

	CategoryContainer.AddCategory(Category);

	system("cls");

	std::cout << "Category created succesfuly. Please type Enter to return to the previous menu";

	std::cin.ignore(500, '\n');
	if (std::cin.peek() == '\n')
	{
		OpenCategoryManagerMenu();
	}
	return;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenRemoveCategory()
{
	system("cls");

	if (CategoryContainer.IsEmpty())
	{
		std::cout << "There is currently no category. Please type Enter to return to the previous menu";

		std::cin.ignore(500, '\n');
		if (std::cin.peek() == '\n')
		{
			OpenCategoryManagerMenu();
		}
		return;

	}

	std::cout << "Choose one of the following options or categories to remove:\n" << std::endl << "0 - Don't remove any category, return to the previous menu" << std::endl;
	for (int i = 1; i <= CategoryContainer.GetCurrentNumberOfCategories(); i++)
	{
		std::cout << i << " - " << CategoryContainer.GetCategory(i-1).GetName() << std::endl;
	}

	std::cout << "\nPlease enter your choice: ";

	float TemporalUserChoice;
	std::cin >> TemporalUserChoice;

	int UserChoice = ValidateInputAndReturnValidatedInput(TemporalUserChoice, "Please enter a valid choice : ", 0, CategoryContainer.GetCurrentNumberOfCategories());

	if (UserChoice == 0)
	{
		OpenCategoryManagerMenu();
		return;
	}

	CategoryContainer.RemoveCategory(UserChoice - 1);

	system("cls");


	std::cout << "Category removed succesfully. Please type Enter to return to the previous menu ";

	std::cin.ignore(500, '\n');
	if (std::cin.peek() == '\n')
	{
		OpenCategoryManagerMenu();
	}
	return;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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

	return ValidateInputAndReturnValidatedInput(TemporalUserChoice, "TELL ME A VALID OPTION: ", 1, CategoryContainer.GetCurrentNumberOfCategories()) - 1;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FSteam::IsInteger(float Float) const
{
	return (Float - floor(Float)) == 0.f;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FSteam::IsInRange(float Value, int LowerBound, int UpperBound) const
{
	return Value >= LowerBound && Value <= UpperBound;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::string FSteam::ValidateInputAndReturnValidatedInput(std::string StringInput, std::string Message)
{
	while (!std::cin.good() || StringInput == "")
	{
		ResetConsoleInputScreen();

		std::cout << Message;
		std::cin >> StringInput;
	}
	return StringInput;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int FSteam::GetValidDay(float TemporalDay, int Month, int Year)
{
	switch (Month)
	{
		// Case for february
	case 2:
		if (Year % 4 == 0 && Year != 1900)
		{
			return ValidateInputAndReturnValidatedInput(TemporalDay, "Please insert the actual day the game was published: ", 1, 29);
		}
		else
		{
			return ValidateInputAndReturnValidatedInput(TemporalDay, "Please insert the actual day the game was published: ", 1, 28);
		}

		// Cases of months that have 31 days
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return ValidateInputAndReturnValidatedInput(TemporalDay, "Please insert the actual day the game was published: ", 1, 31);

		// Cases of months that have 30 days
	case 4:
	case 6:
	case 9:
	case 11:
		return ValidateInputAndReturnValidatedInput(TemporalDay, "Please insert the actual day the game was published: ", 1, 30);

	default:
		"AddGame Date Error, please contact support";
		return 1;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::ResetConsoleInputScreen()
{
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	system("cls");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FSteam::FSteam() : ActiveCommand(MenuCommand::MainMenu), NumberOfGames(0)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::RunSteam()
{
	while (true)
	{
		switch (ActiveCommand)
		{
		case MenuCommand::MainMenu:
			OpenMainMenu();
			break;

		case MenuCommand::AddGamesMenu:
			OpenAddGamesMenu();
			break;

		case MenuCommand::CategoryManagerMenu:
			OpenCategoryManagerMenu();
			break;

		case MenuCommand::GameDisplayerMenu:
			OpenGameDisplayerMenu();
			break;

		case MenuCommand::Exit:
			return;

		default:
			std::cout << "Menu Error, please contact support";
			break;
		}
	}
}
