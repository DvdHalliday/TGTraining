#include "YourShape.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include <string>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FYourShapeApp::OpenMainMenu()
{
	system("cls");

	const std::string MainMenuMessage = "Welcome to YourShape app! How would you like to store your shapes?\n\n1 - Using a built-in array\n2 - Using a static array\n3 - Using a dynamic array\n4 - Exit app\n\nPlease do tell me: ";

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
void FYourShapeApp::OpenAskForShapesBuiltInMenu()
{
	system("cls");

	const std::string BuiltInMessage = "How many shapes would you like to create: ";

	int ShapesAmount = (int)GetValidatedInput(BuiltInMessage, 1, INT_MAX);

	FShape** Shapes = new FShape * [ShapesAmount];

	for (int i = 0; i < ShapesAmount; i++)
	{
		Shapes[i] = GetNewShape(i + 1);
	}

	DisplayShapes(Shapes, ShapesAmount);

	ActiveCommand = EMenuCommand::MainMenu;

	// Delete every heap-shape we created
	for (int i = 0; i < ShapesAmount; i++)
	{
		delete Shapes[i];
		Shapes[i] = nullptr;
	}

	delete[] Shapes;
	Shapes = nullptr;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FYourShapeApp::OpenAskForShapesStaticMenu()
{
	system("cls");

	const std::string StaticMenuMessage = "How many shapes would you like to create: ";

	const int ShapesAmount = 5;

	TStaticArray<FShape*, ShapesAmount> Shapes;

	for (int i = 0; i < ShapesAmount; i++)
	{
		Shapes[i] = GetNewShape(i + 1);
	}

	DisplayShapes(Shapes.GetData(), ShapesAmount);

	ActiveCommand = EMenuCommand::MainMenu;
	// Delete every heap-shape we created
	for (int i = 0; i < ShapesAmount; i++)
	{
		delete Shapes[i];
		Shapes[i] = nullptr;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FYourShapeApp::OpenAskForShapesDynamicMenu()
{
	system("cls");

	TDynamicArray<FShape*> Shapes;

	std::string DynamicMenuMessage = "What would you like to do?\n\n1 - Add a new shape\n2 - Display your current shapes\n3 - Get back to main menu\n\nPlease do tell me: ";

	enum class EDynamicMenuCommand { NewShape = 1, DisplayShapes, MainMenu };

	EDynamicMenuCommand UserChoice;

	do
	{
		system("cls");

		UserChoice = (EDynamicMenuCommand)GetValidatedInput(DynamicMenuMessage, 1, 3);
		switch (UserChoice)
		{
		case EDynamicMenuCommand::NewShape:
			Shapes.PushBack(GetNewShape(Shapes.GetSize() + 1));
			break;

		case EDynamicMenuCommand::DisplayShapes:
			DisplayShapes(Shapes.GetData(), Shapes.GetSize());
			break;

		case EDynamicMenuCommand::MainMenu:
			ActiveCommand = EMenuCommand::MainMenu;
			break;

		default:
			std::cout << "Dynamic Menu Error, please contact support";
			break;
		}
	} while (UserChoice != EDynamicMenuCommand::MainMenu);

	// Delete every heap-shape we created
	for (int i = 0; i < Shapes.GetSize(); i++)
	{
		delete Shapes[i];
		Shapes[i] = nullptr;
	}

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FShape* FYourShapeApp::GetNewShape(const int ShapeIndex) const
{
	enum class EShape { Circle = 1, Square };

	system("cls");

	std::string IterationMessage = "Shape #" + std::to_string(ShapeIndex) + "\n\nThis shape is a\n\n1 - Circle\n2 - Square\n\nTell me: ";

	switch ((EShape)GetValidatedInput(IterationMessage, 1, 2))
	{
	case EShape::Circle:
	{
		system("cls");

		float CircleRadius = GetValidatedFloatInput("Shape #" + std::to_string(ShapeIndex) + "\n\nEnter a valid radius for your circle: ");
		return new FCircle(CircleRadius);
	}

	case EShape::Square:
	{
		system("cls");

		float SquareSideLength = GetValidatedFloatInput("Shape #" + std::to_string(ShapeIndex) + "\n\nEnter a valid side length for your square: ");
		return new FSquare(SquareSideLength);
	}

	default:
		system("cls");

		std::cout << "Static shapes error, please contact support" << std::endl;
		break;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FYourShapeApp::DisplayShapes(FShape** ArrayPointer, const int ArraySize) const
{
	system("cls");

	if (ArraySize == 0)
	{
		std::cout << "There are currently no shapes registered, so no areas or perimeters ;c" << std::endl << std::endl;

		std::cout << "Please hit enter to return to main menu ";

		RequestEnter();
		return;
	}

	std::cout << "Here's a list of your shapes, as well as their areas and perimeters" << std::endl << std::endl;

	for (int i = 0; i < ArraySize; i++)
	{
		FShape* ShapePointer = *(ArrayPointer + i);
		std::cout << "Shape #" << i + 1 << " is a " << ShapePointer->GetShapeName() << std::endl;
		std::cout << "Area: " << ShapePointer->GetArea() << std::endl << "Perimeter: " << ShapePointer->GetPerimeter() << std::endl << std::endl;
	}

	std::cout << "Please hit enter to return to main menu ";

	RequestEnter();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FYourShapeApp::RequestEnter() const
{
	std::cin.ignore(500, '\n');

	while (std::cin.get() != '\n')
	{
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
			OpenAskForShapesBuiltInMenu();
			break;

		case EMenuCommand::AskForShapesStaticMenu:
			OpenAskForShapesStaticMenu();
			break;

		case EMenuCommand::AskForShapesDynamicMenu:
			OpenAskForShapesDynamicMenu();
			break;

		case EMenuCommand::Exit:
			break;

		default:
			std::cout << "Menu Error, please contact support";
			break;
		}
	}
}
