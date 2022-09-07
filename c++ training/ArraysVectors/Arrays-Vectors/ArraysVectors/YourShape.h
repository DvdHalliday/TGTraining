#pragma once
#include "Circle.h"
#include "Square.h"
#include <iostream>
#include "DynamicArray.h"

class FYourShapeApp 
{
private:
	enum class EMenuCommand
	{
		MainMenu = 1,
		AskForShapesBuiltInMenu,
		AskForShapesStaticMenu,
		AskForShapesDynamicMenu,
		Exit
	};
	EMenuCommand ActiveCommand = EMenuCommand::MainMenu;

	void OpenMainMenu();
	void OpenAskForShapesBuiltInMenu();
	void OpenAskForShapesStaticMenu();
	void OpenAskForShapesDynamicMenu();

	FShape* GetNewShape(const int ShapeIndex) const;
	void DisplayShapes(FShape** ArrayPointer, int ArraySize) const;

	bool IsInteger(const float Float) const;
	bool IsInRange(const float Value, const int LowerBound, const int UpperBound) const;
	
	int GetValidatedInput(const std::string& Message, const int LowerBound, const int UpperBound) const;
	float GetValidatedFloatInput(const std::string& Message) const;
	std::string GetValidatedInput(const std::string& Message) const;

	void ResetConsoleInputScreen() const;
	void RequestEnter() const;

public:
	FYourShapeApp() {}
	void RunApp();
};