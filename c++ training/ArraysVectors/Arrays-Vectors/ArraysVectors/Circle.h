#pragma once
#include "Shape.h"

class FCircle : public FShape
{
private:
	float Radius = 1.f;

public:
	FCircle() {}
	FCircle(const int NewRadius);

	virtual float GetArea() const override;
	virtual float GetPerimeter() const override;
};