#include "Cue.h"


FCue::FCue(const FBall& NewBall) : TargetBall(&NewBall)
{
    Distance = TargetBall->GetRadius() + 10;
}

FCue& FCue::operator=(const FCue& NewCue)
{
    TargetBall = NewCue.TargetBall;
    Distance = TargetBall->GetRadius() + 10;
    return *this;
}

void FCue::SetAngle(const float NewAngle)
{
    Angle = NewAngle;
}

void FCue::SetDistance(const float NewDistance)
{
    if (NewDistance > TargetBall->GetRadius())
    {
        Distance = NewDistance;
    }
}

void FCue::SetActiveState(const bool bNewIsActive)
{
    bIsActive = bNewIsActive;
}

float FCue::GetAngle() const
{
    return Angle;
}

float FCue::GetDistance() const
{
    return Distance;
}

bool FCue::IsActive() const
{
    return bIsActive;
}
