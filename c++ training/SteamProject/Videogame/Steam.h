#pragma once
#include "CategoryContainer.h"

class FSteam {
private:
	FCategoryContainer CategoryContainer;
	FCategory Uncategorized = FCategory("Uncategorized");

public:
	void RunSteam();

};