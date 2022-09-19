#pragma once
#include "Shape.h"

class FSquare : public FShape
{
private:
	float SideLength = 1.f;

public:
	FSquare() {}
	FSquare(const float NewSideLength);
	FSquare(const FSquare& Other);

	virtual float GetArea() const override;
	virtual float GetPerimeter() const override;
	virtual std::string GetShapeName() const override;

	bool operator==(const FSquare& Other) const;
};