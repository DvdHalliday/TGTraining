#include "YourShape.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FYourShapeApp::OpenMainMenu()
{
	system("cls");

	const std::string MainMenuMessage = "Welcome to YourShape app! How would you like to store your shapes?\n\n1 - Using a built-in array\n\n2 - Using a static array\n\n3 - Using a dynamic array\n\n4 - Exit app\n\nPlease do tell me: ";

	enum class EMainMenuCommand { BuiltIn = 1, Static, Dynamic, Exit };

	switch ((EMainMenuCommand)GetValidatedInput(MainMenuMessage, 1, 4))
	{
	case EMainMenuCommand::BuiltIn:
		ActiveCommand = EMenuCommand::AskForShapesBuiltInMenu;
		break;

	case EMainMenuCommand::Static:
		ActiveCommand = EMenuCommand::AskForShapesStaticMenu;
		break;

	case EMainMenuCommand::Dynamic:
		ActiveCommand = EMenuCommand::AskForShapesDynamicMenu;
		break;

	case EMainMenuCommand::Exit:
		ActiveCommand = EMenuCommand::Exit;
		break;

	default:
		std::cout << "Main Menu Error, please contact support";
		break;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FYourShapeApp::IsInteger(const float Float) const
{
	return (Float - floor(Float)) == 0.f;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FYourShapeApp::IsInRange(const float Value, const int LowerBound, const int UpperBound) const
{
	return Value >= LowerBound && Value <= UpperBound;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int FYourShapeApp::GetValidatedInput(const std::string& Message, const int LowerBound, const int UpperBound) const
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
float FYourShapeApp::GetValidatedFloatInput(const std::string& Message) const
{
	std::cout << Message;

	float UserInput;
	std::cin >> UserInput;

	while (!std::cin.good() || UserInput <= 0)
	{
		ResetConsoleInputScreen();

		std::cout << Message;
		std::cin >> UserInput;
	}
	return UserInput;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::string FYourShapeApp::GetValidatedInput(const std::string& Message) const
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
void FYourShapeApp::ResetConsoleInputScreen() const
{
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	system("cls");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FYourShapeApp::RunApp()
{
	while (ActiveCommand != EMenuCommand::Exit)
	{
		switch (ActiveCommand)
		{
		case EMenuCommand::MainMenu:
			OpenMainMenu();
			break;

		case EMenuCommand::AskForShapesBuiltInMenu:
			//OpenAskForShapesBuiltInMenu();
			break;

		case EMenuCommand::AskForShapesStaticMenu:
			//OpenAskForShapesStaticMenu();
			break;

		case EMenuCommand::AskForShapesDynamicMenu:
			//OpenAskForShapesDynamicMenu();
			break;

		case EMenuCommand::Exit:
			break;

		default:
			std::cout << "Menu Error, please contact support";
			break;
		}
	}
}
