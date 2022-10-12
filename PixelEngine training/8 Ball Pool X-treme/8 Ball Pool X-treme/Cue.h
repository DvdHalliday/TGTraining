#pragma once
#include "Ball.h"

class FCue
{
private:
    const FBall* TargetBall;
    // The next angle represents the angle of the cue around the target ball
    float Angle = 0;
    // The next distance represents the distance to the target ball circumference
    float Distance;

    bool bIsActive = false;

public:
    FCue(const FBall& NewBall);

    FCue& operator=(const FCue& NewCue);

    void SetAngle(const float NewAngle);

    void SetDistance(const float NewDistance);

    void SetActiveState(const bool bNewIsActive);
    
    float GetAngle() const;

    float GetDistance() const;

    bool IsActive() const;
};
