#include "Player.h"

FPlayer::FPlayer(const EBallType NewBallType, const FBall& CueBall) : BallType(NewBallType)
{
    Cue = new FCue(CueBall);
}

void FPlayer::SetScore(const int NewScore)
{
    Score = NewScore;
}

void FPlayer::AddScore(const int OtherScore)
{
    Score += OtherScore;
}

void FPlayer::Strike()
{
    // To do: Save the initial Cue distance to the cue ball, animate the cue moving to the cue ball
    // And add the new velocity to the white ball depending on the original cue distance
}

const FCue& FPlayer::GetCue() const
{
    return *Cue;
}

void FPlayer::SetCueValues(const float MouseX, const float MouseY)
{
    // To do: Add values for Cue angle and Distance depending on the x and y mouse coordinates
}
