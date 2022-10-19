#include "Player.h"

#include "EightBallPool.h"

FPlayer::FPlayer(const EBallType NewBallType, const FBall* CueBall) : Score(0), BallType(NewBallType)
{
    Cue = new FCue(*CueBall);
}

void FPlayer::SetScore(const int NewScore)
{
    Score = NewScore;
}

void FPlayer::AddScore(const int OtherScore)
{
    Score += OtherScore;
}

void FPlayer::Strike(FEightBallPool* Game)
{
    // To do: Save the initial Cue distance to the cue ball, animate the cue moving to the cue ball
    // And add the new velocity to the white ball depending on the original cue distance
    const float OriginalDistance = Game->GetPlayer().GetCue().GetDistance();
    olc::vf2d NewVelocity = - 5.f * OriginalDistance * Game->GetPlayer().GetCue().GetDirection();
    Game->GetCueBall()->SetVelocity(NewVelocity);
}

FCue& FPlayer::GetCue()
{
    return *Cue;
}

void FPlayer::SetCueValues(const float MouseX, const float MouseY)
{
    // To do: Add values for Cue angle and Distance depending on the x and y mouse coordinates
}
