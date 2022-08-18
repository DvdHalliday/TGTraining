#include "Steam.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::OpenMainMenu()
{
	system("cls");

	const std::string MainMenuMessage = "Welcome to the Steam store! What would you like to do? \n1 - Add a game\n2 - Modify or create game categories \n3 - View all games \n4 - Exit \nTELL ME: ";

	enum class EMainMenuCommand { AddGameMenu = 1, CategoryManagerMenu, GameDisplayerMenu, Exit };

	int Choice;
	ValidateInput(Choice, MainMenuMessage, 1, 4);

	switch ((EMainMenuCommand)Choice)
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

	std::string GameName;
	ValidateInput(GameName, "Please insert the name of the game: ");

	std::string GameStudio;
	ValidateInput(GameStudio, "Please insert a valid name for the game studio: ");

	int Year;
	ValidateInput(Year, "Please insert the year the game was published: ", 1900, 2022);

	int Month;
	ValidateInput(Month, "Please insert the month the game was published (1-12): ", 1, 12);

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

	enum class ECategoryManagerCommand { CreateCategory = 1, RemoveCategory, MainMenu };

	int Choice;
	ValidateInput(Choice, CategoryManagerMessage, 1, 3);

	switch ((ECategoryManagerCommand)Choice)
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
			FVideogame Game;
			if (Uncategorized.GetGameAt(i, Game))
			{
				std::cout << Game.GetName() << "\t by " << Game.GetStudio() << "\t published on " << Game.GetFormattedDate() << std::endl;
			}
		}
	}

	for (int i = 0; i < CategoryContainer.GetCurrentNumberOfCategories(); i++)
	{
		FCategory Category;
		if (CategoryContainer.GetCategoryAt(i, Category) && Category.GetCurrentNumberOfGames() != 0)
		{
			std::cout << "---------------------------------------------------------\n" << Category.GetName() << " Games\n" << std::endl;

			for (int j = 0; j < Category.GetCurrentNumberOfGames(); j++)
			{
				FVideogame Game;
				if (Category.GetGameAt(j, Game))
				{
					std::cout << Game.GetName() << "\t by " << Game.GetStudio() << "\t published on " << Game.GetFormattedDate() << std::endl;
				}
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

	std::string CategoryName;
	ValidateInput(CategoryName, "Please enter a name for the new category: ");

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
		FCategory Category;
		if (CategoryContainer.GetCategoryAt(i - 1, Category))
		{
			std::cout << i << " - " << Category.GetName() << std::endl;
		}

	}

	std::cout << std::endl;

	int UserChoice;
	ValidateInput(UserChoice, "Please enter a valid choice : ", 0, CategoryContainer.GetCurrentNumberOfCategories());

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
const int& FSteam::ChooseCategory() const
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
		FCategory Category;
		if (CategoryContainer.GetCategoryAt(i - 1, Category))
		{
			std::cout << i << " - " << Category.GetName() << std::endl;
		}
	}
	int Choice;
	ValidateInput(Choice, "TELL ME: ", 1, CategoryContainer.GetCurrentNumberOfCategories());
	return Choice - 1;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const bool& FSteam::AskChooseCategory() const
{
	system("cls");
	std::string AskChooseCategoryMessage = "Would you like to choose a category for your new game? \n1 - Yes\n2 - No\nTELL ME : ";

	enum class EQuestionCategoryCommand { Yes = 1, No };

	int Choice;
	ValidateInput(Choice, AskChooseCategoryMessage, 1, 2);

	switch ((EQuestionCategoryCommand)Choice)
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
bool FSteam::IsInteger(const float& Float) const
{
	return (Float - floor(Float)) == 0.f;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FSteam::IsInRange(const float& Value, const int& LowerBound, const int& UpperBound) const
{
	return Value >= LowerBound && Value <= UpperBound;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::ValidateInput(int& OutInput, const std::string& Message, const int& LowerBound, const int& UpperBound) const
{
	std::cout << Message;

	std::cin >> OutInput;

	while (!std::cin.good() || !IsInteger(OutInput) || !IsInRange(OutInput, LowerBound, UpperBound))
	{
		ResetConsoleInputScreen();

		std::cout << Message;
		std::cin >> OutInput;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FSteam::ValidateInput(std::string& OutInput, const std::string& Message) const
{
	std::cout << Message;

	std::cin >> OutInput;

	while (!std::cin.good() || OutInput.empty())
	{
		ResetConsoleInputScreen();

		std::cout << Message;
		std::cin >> OutInput;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const int& FSteam::GetValidDay(const int& Month, const int& Year) const
{
	int Day;
	switch (Month)
	{
		// Case for february
	case 2:
		if (Year % 4 == 0 && Year != 1900)
		{
			ValidateInput(Day, "Please insert the day the game was published: ", 1, 29);
			return Day;
		}
		else
		{
			ValidateInput(Day, "Please insert the actual day the game was published: ", 1, 28);
			return Day;
		}

		// Cases of months that have 31 days
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		ValidateInput(Day, "Please insert the day the game was published: ", 1, 31);
		return Day;

		// Cases of months that have 30 days
	case 4:
	case 6:
	case 9:
	case 11:
		ValidateInput(Day, "Please insert the day the game was published: ", 1, 30);
		return Day;

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
FSteam::FSteam(const FSteam& Other) : Uncategorized(Other.Uncategorized), NumberOfGames(Other.NumberOfGames), ActiveCommand(Other.ActiveCommand),
CategoryContainer(Other.CategoryContainer)
{
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
