#pragma once
#include "Category.h"

class FCategoryContainer {
private:
	const static int MaxCategoriesAmount = 30;
	FCategory Categories[MaxCategoriesAmount];
	int CurrentNumberOfCategories;

public:
	FCategoryContainer();

	bool IsFull() const;
	bool IsEmpty() const;

	bool AddCategory(FCategory Category);
	bool RemoveCategory(int Index);

	FCategory GetCategory(int Index) const;
	int GetCurrentNumberOfCategories() const;
};
