#pragma once
#include "Shape.h"

class FSquare : public FShape
{
private:
	float SideLength = 1.f;

public:
	FSquare() {}
	FSquare(const int NewSideLength);

	virtual float GetArea() const override;
	virtual float GetPerimeter() const override;
};