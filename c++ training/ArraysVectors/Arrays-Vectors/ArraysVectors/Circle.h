#pragma once
#include "Shape.h"

class FCircle : public FShape
{
private:
	float Radius = 1.f;
	const static std::string ShapeName;

public:
	FCircle() {}
	FCircle(const float NewRadius);
	FCircle(const FCircle& Other);

	virtual float GetArea() const override;
	virtual float GetPerimeter() const override;
	virtual const std::string& GetShapeName() const override;
};