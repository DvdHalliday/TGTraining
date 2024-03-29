#pragma once
#include "Category.h"

class FCategoryContainer 
{
private:
	const static int MaxCategoriesAmount = 30;
	FCategory Categories[MaxCategoriesAmount];
	int CurrentNumberOfCategories;

public:
	FCategoryContainer();

	FCategoryContainer(const FCategoryContainer& Other);
	~FCategoryContainer() {}

	bool IsFull() const;
	bool IsEmpty() const;

	bool AddCategory(const FCategory& Category);
	bool RemoveCategory(const int Index);

	void AddGameToCategory(const int CategoryIndex, const FVideogame& Game);

	bool GetCategoryAt(const int Index, FCategory& OutCategory) const;
	int GetCurrentNumberOfCategories() const;
};
