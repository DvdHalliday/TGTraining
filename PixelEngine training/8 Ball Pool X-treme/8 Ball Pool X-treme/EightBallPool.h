#pragma once
#include "olcPixelGameEngine.h"
#include "Player.h"

class FEightBallPool : public olc::PixelGameEngine
{
private:
    olc::Sprite* Background = nullptr;
    olc::Decal* BackgroundDecal = nullptr;

    olc::Sprite* CueSprite = nullptr;
    olc::Decal* CueDecal = nullptr;
    
    olc::Sprite* CueBallSprite = nullptr;

    olc::Sprite* BallOneSprite = nullptr;

    FBall* CueBall = new FBall(0);
    FBall* BallOne = new FBall(1);

    FPlayer PlayerOne = FPlayer(FPlayer::EBallType::Striped, CueBall);
    FPlayer PlayerTwo = FPlayer(FPlayer::EBallType::Solid, CueBall);
    
    std::list<FBall*> Balls;
    std::list<std::pair<olc::vf2d, olc::vf2d>> Edges;
    std::list<FBall*> FakeBalls;

public:
    FEightBallPool();

    bool OnUserCreate() override;

    bool OnUserUpdate(float ElapsedTime) override;

    FPlayer& GetPlayer();

    FBall* GetCueBall();

    void DrawBall(const FBall* Ball);

    bool DoBallsOverlap(const FBall* Ball, const FBall* OtherBall) const;
};
