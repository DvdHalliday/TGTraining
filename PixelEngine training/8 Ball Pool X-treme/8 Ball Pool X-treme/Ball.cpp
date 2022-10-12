#include "Ball.h"

void FBall::SetPosition(const float X, const float Y)
{
    Position = {X, Y};
}

void FBall::SetVelocity(const float X, const float Y)
{
    Velocity = {X, Y};
}

void FBall::SetActiveState(const bool bNewIsActive)
{
    bIsActive = bNewIsActive;
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

const olc::Pixel& FBall::GetColor() const
{
    return Color;
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
            Velocity = {0.f,0.f};
        }
        else
        {
            Velocity += Acceleration * ElapsedTime;
        }
    }
}


