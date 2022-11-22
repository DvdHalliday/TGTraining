#pragma once
#include "olcPixelGameEngine.h"

class FBall
{
private:
	olc::vf2d Position = { 0.f,0.f };
	olc::vf2d Velocity = { 0.f,0.f };
	olc::vf2d Acceleration = { 0.f,0.f };

	const int Number = 1;

	bool bIsActive = true;

	olc::Decal* Decal = nullptr;

public:
	FBall(const int NewNumber = 1) :  Number(NewNumber) {}

	~FBall();

	void SetPosition(const float X, const float Y);

	void SetPosition(const olc::vf2d& NewPosition);
	
	void SetVelocity(const float X, const float Y);

	void SetVelocity(const olc::vf2d& NewVelocity);

	void SetActiveState(const bool bNewIsActive);

	void SetDecal(olc::Sprite* NewSprite);

	void AddPosition(const olc::vf2d& OtherPosition);
	
	void AddVelocity(const olc::vf2d& OtherVelocity);

	const olc::vf2d& GetPosition() const;

	const olc::vf2d& GetVelocity() const;

	int GetNumber() const;

	olc::Decal* GetDecal() const;

	float GetRadius() const;

	bool IsActive() const;

	void Move(const float ElapsedTime);
};
