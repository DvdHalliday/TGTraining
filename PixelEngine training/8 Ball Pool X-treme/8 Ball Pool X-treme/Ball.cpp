#include "Ball.h"

FBall::~FBall()
{
    delete Decal;
    Decal = nullptr;
}

void FBall::SetPosition(const float X, const float Y)
{
    Position = {X, Y};
}

void FBall::SetPosition(const olc::vf2d& NewPosition)
{
    Position = NewPosition;
}

void FBall::SetVelocity(const float X, const float Y)
{
    Velocity = {X, Y};
}

void FBall::SetVelocity(const olc::vf2d& NewVelocity)
{
    Velocity = NewVelocity;
}

void FBall::SetActiveState(const bool bNewIsActive)
{
    bIsActive = bNewIsActive;
}

void FBall::SetDecal(olc::Sprite* NewSprite)
{
    if (Decal)
    {
        delete Decal;
        Decal = nullptr;
    }
    Decal = new olc::Decal(NewSprite);
}

void FBall::AddPosition(const olc::vf2d& OtherPosition)
{
    Position += OtherPosition;
}

void FBall::AddVelocity(const olc::vf2d& OtherVelocity)
{
    Velocity += OtherVelocity;
}

const olc::vf2d& FBall::GetPosition() const
{
    return Position;
}

const olc::vf2d& FBall::GetVelocity() const
{
    return Velocity;
}

int FBall::GetNumber() const
{
    return Number;
}

olc::Decal* FBall::GetDecal() const
{
    return Decal;
}

float FBall::GetRadius() const
{
    return 25.f;
}

bool FBall::IsActive() const
{
    return bIsActive;
}

void FBall::Move(const float ElapsedTime)
{
    if (Velocity != olc::vf2d({0.f, 0.f}))
    {
        Acceleration = -Velocity.norm() * 50;

        Position += Velocity * ElapsedTime;

        if (Velocity.dot(Velocity + Acceleration * ElapsedTime) < 0)
        {
            Velocity = {0.f, 0.f};
        }
        else
        {
            Velocity += Acceleration * ElapsedTime;
        }
    }
}
