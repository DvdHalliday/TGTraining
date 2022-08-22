#include "CategoryContainer.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FCategoryContainer::FCategoryContainer() : CurrentNumberOfCategories(0)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FCategoryContainer::FCategoryContainer(const FCategoryContainer& Other) : CurrentNumberOfCategories(Other.CurrentNumberOfCategories)
{
	memcpy_s(Categories, sizeof Categories, Other.Categories, sizeof Other.Categories);
}
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
bool FCategoryContainer::AddCategory(const FCategory& Category)
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
bool FCategoryContainer::GetCategoryAt(const int Index, FCategory& OutCategory) const
{
	if (Index >= 0 && Index < CurrentNumberOfCategories)
	{
		OutCategory = Categories[Index];
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FCategoryContainer::AddGameToCategory(const int CategoryIndex, const FVideogame& Game)
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
