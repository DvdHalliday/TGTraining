#pragma once
#include "Shape.h"

class FSquare : public FShape
{
private:
	float SideLength = 1.f;
	const static std::string ShapeName;


public:
	FSquare() {}
	FSquare(const float NewSideLength);

	virtual float GetArea() const override;
	virtual float GetPerimeter() const override;
	virtual const std::string& GetShapeName() const override;
};