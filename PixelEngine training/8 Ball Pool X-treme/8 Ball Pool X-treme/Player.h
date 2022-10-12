#pragma once
#include "Cue.h"

class FPlayer
{
private:
    int Score;
    const FCue* Cue;

    enum class EBallType {Striped = 0, Solid};

    const EBallType BallType;
    
public:
    FPlayer(const EBallType NewBallType, const FBall& CueBall);

    void SetScore(const int NewScore);
    void AddScore(const int OtherScore);
    
    void Strike();

    const FCue& GetCue() const;

    void SetCueValues(const float MouseX, const float MouseY);    
};
