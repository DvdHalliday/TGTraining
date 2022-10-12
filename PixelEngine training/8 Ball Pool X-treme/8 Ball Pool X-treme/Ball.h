#pragma once
#include "olcPixelGameEngine.h"

class FBall
{
private:
	olc::vf2d Position = { 0.f,0.f };
	olc::vf2d Velocity = { 0.f,0.f };
	olc::vf2d Acceleration = { 0.f,0.f };

	const int Number = 1;
	const olc::Pixel Color = olc::WHITE;

	bool bIsActive = true;

public:
	FBall(const olc::vf2d& NewPosition, const int NewNumber = 1, const olc::Pixel NewColor = olc::WHITE) : Position(NewPosition),
		Number(NewNumber), Color(NewColor) {}

	void SetPosition(const float X, const float Y);

	void SetVelocity(const float X, const float Y);

	void SetActiveState(const bool bNewIsActive);

	const olc::vf2d& GetPosition() const;

	const olc::vf2d& GetVelocity() const;

	int GetNumber() const;

	const olc::Pixel& GetColor() const;

	float GetRadius() const;

	bool IsActive() const;

	void Move(const float ElapsedTime);
};
