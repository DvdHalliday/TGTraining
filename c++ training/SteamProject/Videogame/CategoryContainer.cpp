#include "CategoryContainer.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FCategoryContainer::FCategoryContainer() : CurrentNumberOfCategories(0)
{
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
bool FCategoryContainer::AddCategory(FCategory Category)
{
	if (!IsFull())
	{
		Categories[CurrentNumberOfCategories++] = Category;
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FCategoryContainer::RemoveCategory(int Index)
{
	if (IsEmpty())
	{
		return false;
	}
	for (int i = Index; i < CurrentNumberOfCategories && i < MaxCategoriesAmount-1; i++)
	{
		Categories[i] = Categories[i + 1];
	}
	CurrentNumberOfCategories--;
	return true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FCategory FCategoryContainer::GetCategory(int Index) const
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
	Categories[CategoryIndex].AddGame(Game);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int FCategoryContainer::GetCurrentNumberOfCategories() const
{
	return CurrentNumberOfCategories;
}
