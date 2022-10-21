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
    olc::Sprite* BallTwoSprite = nullptr;
    olc::Sprite* BallThreeSprite = nullptr;
    olc::Sprite* BallFourSprite = nullptr;
    olc::Sprite* BallFiveSprite = nullptr;
    olc::Sprite* BallSixSprite = nullptr;
    olc::Sprite* BallSevenSprite = nullptr;
    olc::Sprite* BallEightSprite = nullptr;
    olc::Sprite* BallNineSprite = nullptr;
    olc::Sprite* BallTenSprite = nullptr;
    olc::Sprite* BallElevenSprite = nullptr;
    olc::Sprite* BallTwelveSprite = nullptr;
    olc::Sprite* BallThirteenSprite = nullptr;
    olc::Sprite* BallFourteenSprite = nullptr;
    olc::Sprite* BallFifteenSprite = nullptr;


    FBall* CueBall = new FBall(0);

    FPlayer PlayerOne = FPlayer(FPlayer::EBallType::Striped, CueBall);
    FPlayer PlayerTwo = FPlayer(FPlayer::EBallType::Solid, CueBall);

    FPlayer* CurrentPlayer = &PlayerOne;
    
    std::vector<FBall*> Balls;
    std::list<std::pair<olc::vf2d, olc::vf2d>> Edges;
    std::list<std::pair<FBall*, FBall*>> CollidingPairs;
    std::list<FBall*> FakeBalls;

    bool bAreBallsMoving = false;
    bool bIsTurnHappening = true;
    bool bHasScoredBall = false;
    bool bHasHit = false;
    
public:
    FEightBallPool();

    ~FEightBallPool() override;

    bool OnUserCreate() override;

    bool OnUserUpdate(float ElapsedTime) override;

    void SetEdges();

    void CreateBalls();

    void SetInitialBallsPosition();

    bool CheckScored(FBall* Ball);

    void UpdateBalls(const float ElapsedTime);

    void CollidePairs();

    void CheckBallToEdgeCollisions(FBall* Ball);

    void CheckBallToBallCollisions(FBall* Ball);

    void SwitchTurn();

    void HandleScoredBall(FBall* Ball);

    void DrawCue();

    void HitBall();

    void PutBallBackOnTable(FBall* Ball);

    void PutCueBallBackOnTable();

    bool IsPositionInAnyBall(const olc::vf2d& Position) const;

    FPlayer& GetPlayer();

    FBall* GetCueBall();

    void DrawBall(const FBall* Ball);

    bool DoBallsOverlap(const FBall* Ball, const FBall* OtherBall) const;
};

