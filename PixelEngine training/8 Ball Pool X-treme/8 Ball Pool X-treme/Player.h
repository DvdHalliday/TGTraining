#pragma once
#include "Cue.h"

class FEightBallPool;

class FPlayer
{
public:
    enum class EBallType {Striped = 0, Solid};
    
private:
    int Score;
    FCue* Cue;

    const EBallType BallType;
    
public:
    FPlayer(const EBallType NewBallType, const FBall* CueBall);

    void SetScore(const int NewScore);
    void AddScore(const int OtherScore);
    
    void Strike(FEightBallPool* Game);

    FCue& GetCue();

    void SetCueValues(const float MouseX, const float MouseY);    
};
