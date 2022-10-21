#include "Cue.h"

//----------------------------------------------------------------------------------------------------------------------
FCue::FCue(const FBall& NewBall) : TargetBall(&NewBall)
{
    Distance = TargetBall->GetRadius() + 10;
}
//----------------------------------------------------------------------------------------------------------------------
FCue& FCue::operator=(const FCue& NewCue)
{
    TargetBall = NewCue.TargetBall;
    Distance = TargetBall->GetRadius() + 10;
    return *this;
}
//----------------------------------------------------------------------------------------------------------------------
void FCue::SetAngle(const float NewAngle)
{
    Angle = NewAngle;
}
//----------------------------------------------------------------------------------------------------------------------
void FCue::SetDistance(const float NewDistance)
{
    if (NewDistance > TargetBall->GetRadius() + 9 && NewDistance < 150.f)
    {
        Distance = NewDistance;
    }
}
//----------------------------------------------------------------------------------------------------------------------
float FCue::GetAngle() const
{
    return Angle;
}
//----------------------------------------------------------------------------------------------------------------------
olc::vf2d FCue::GetDirection() const
{
    return olc::vf2d{sinf(Angle),-cosf(Angle)};
}
//----------------------------------------------------------------------------------------------------------------------
float FCue::GetDistance() const
{
    return Distance;
}