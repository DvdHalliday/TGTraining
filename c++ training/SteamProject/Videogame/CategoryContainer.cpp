#include "CategoryContainer.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FCategoryContainer::IsFull() const
{
	return CurrentNumberOfCategories >= MaxCategoriesAmount;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FCategoryContainer::IsEmpty() const
{
	return CurrentNumberOfCategories == 0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FCategoryContainer::AddCategory(const FCategory Category)
{
	if (!IsFull())
	{
		Categories[CurrentNumberOfCategories++] = Category;
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FCategoryContainer::RemoveCategory(const int Index)
{
	if (IsEmpty() || Index < 0 || Index >= CurrentNumberOfCategories)
	{
		return false;
	}
	for (int i = Index; i < CurrentNumberOfCategories-1; i++)
	{
		Categories[i] = Categories[i + 1];
	}
	CurrentNumberOfCategories--;
	return true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FCategory FCategoryContainer::GetCategory(const int Index) const
{
	if (Index >= 0 && Index < CurrentNumberOfCategories)
	{
		return Categories[Index];
	}
	return FCategory();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FCategoryContainer::AddGameToCategory(const int CategoryIndex, const FVideogame Game)
{
	if (CategoryIndex < 0 || CategoryIndex >= CurrentNumberOfCategories) 
	{
		std::cout << "Index Out Of Bounds in AddGameToCategory Error, please contact support" << std::endl;
		return;
	}
	Categories[CategoryIndex].AddGame(Game);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int FCategoryContainer::GetCurrentNumberOfCategories() const
{
	return CurrentNumberOfCategories;
}
