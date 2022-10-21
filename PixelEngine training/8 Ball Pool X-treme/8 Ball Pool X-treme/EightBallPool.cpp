#include "EightBallPool.h"
//----------------------------------------------------------------------------------------------------------------------
FEightBallPool::FEightBallPool()
{
    sAppName = "8-Ball pool X-TREME";
}
//----------------------------------------------------------------------------------------------------------------------
FEightBallPool::~FEightBallPool()
{
    delete CueBallSprite;
    delete BallOneSprite;
    delete BallTwoSprite;
    delete BallThreeSprite;
    delete BallFourSprite;
    delete BallFiveSprite;
    delete BallSixSprite;
    delete BallSevenSprite;
    delete BallEightSprite;
    delete BallNineSprite;
    delete BallTenSprite;
    delete BallElevenSprite;
    delete BallTwelveSprite;
    delete BallThirteenSprite;
    delete BallFourteenSprite;
    delete BallFifteenSprite;

    delete Background;
    delete BackgroundDecal;
    delete CueSprite;
    delete CueDecal;

    for (int i = 0; i < static_cast<int>(Balls.capacity()); i++)
    {
        delete Balls[i];
    }
}
//----------------------------------------------------------------------------------------------------------------------
bool FEightBallPool::OnUserCreate()
{
    Clear(olc::Pixel(234, 221, 202));

    Balls.reserve(16);

    Background = new olc::Sprite("./Images/Table.png");
    BackgroundDecal = new olc::Decal(Background);

    CueSprite = new olc::Sprite("./Images/Cue.png");
    CueDecal = new olc::Decal(CueSprite);

    Balls.push_back(CueBall);
    CreateBalls();

    SetEdges();

    return true;
}
//----------------------------------------------------------------------------------------------------------------------
bool FEightBallPool::OnUserUpdate(float ElapsedTime)
{
    DrawDecal({0.f, 0.f}, BackgroundDecal);

    bAreBallsMoving = false;
    UpdateBalls(ElapsedTime);

    CollidePairs();

    if (!bAreBallsMoving && !bIsTurnHappening && bHasHit)
    {
        SwitchTurn();
    }

    DrawCue();

    HitBall();
    
    for (const auto& FakeBall : FakeBalls)
    {
        delete FakeBall;
    }

    CollidingPairs.clear();
    FakeBalls.clear();

    return true;
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::SetEdges()
{
    Edges.push_back({{100, 55}, {113, 68}});
    Edges.push_back({{113, 68}, {607, 68}});
    Edges.push_back({{607, 68}, {611, 56}});
    Edges.push_back({{668, 56}, {671, 68}});
    Edges.push_back({{671, 68}, {1167, 68}});
    Edges.push_back({{1167, 68}, {1180, 55}});
    Edges.push_back({{1224, 99}, {1211, 112}});
    Edges.push_back({{1211, 112}, {1211, 594}});
    Edges.push_back({{1211, 594}, {1224, 607}});
    Edges.push_back({{1180, 651}, {1167, 638}});
    Edges.push_back({{1167, 638}, {671, 638}});
    Edges.push_back({{671, 638}, {668, 649}});
    Edges.push_back({{611, 649}, {607, 638}});
    Edges.push_back({{607, 638}, {113, 638}});
    Edges.push_back({{113, 638}, {100, 651}});
    Edges.push_back({{56, 607}, {69, 594}});
    Edges.push_back({{69, 594}, {69, 112}});
    Edges.push_back({{69, 112}, {56, 99}});
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::CreateBalls()
{
    for (int i = 1; i < static_cast<int>(Balls.capacity()); i++)
    {
        Balls.push_back(new FBall(i));
    }

    BallOneSprite = new olc::Sprite("./Images/BallOne.png");
    BallTwoSprite = new olc::Sprite("./Images/BallTwo.png");
    BallThreeSprite = new olc::Sprite("./Images/BallThree.png");
    BallFourSprite = new olc::Sprite("./Images/BallFour.png");
    BallFiveSprite = new olc::Sprite("./Images/BallFive.png");
    BallSixSprite = new olc::Sprite("./Images/BallSix.png");
    BallSevenSprite = new olc::Sprite("./Images/BallSeven.png");
    BallEightSprite = new olc::Sprite("./Images/BallEight.png");
    BallNineSprite = new olc::Sprite("./Images/BallNine.png");
    BallTenSprite = new olc::Sprite("./Images/BallTen.png");
    BallElevenSprite = new olc::Sprite("./Images/BallEleven.png");
    BallTwelveSprite = new olc::Sprite("./Images/BallTwelve.png");
    BallThirteenSprite = new olc::Sprite("./Images/BallThirteen.png");
    BallFourteenSprite = new olc::Sprite("./Images/BallFourteen.png");
    BallFifteenSprite = new olc::Sprite("./Images/BallFifteen.png");
    CueBallSprite = new olc::Sprite("./Images/CueBall.png");

    CueBall->SetDecal(CueBallSprite);
    Balls[1]->SetDecal(BallOneSprite);
    Balls[2]->SetDecal(BallTwoSprite);
    Balls[3]->SetDecal(BallThreeSprite);
    Balls[4]->SetDecal(BallFourSprite);
    Balls[5]->SetDecal(BallFiveSprite);
    Balls[6]->SetDecal(BallSixSprite);
    Balls[7]->SetDecal(BallSevenSprite);
    Balls[8]->SetDecal(BallEightSprite);
    Balls[9]->SetDecal(BallNineSprite);
    Balls[10]->SetDecal(BallTenSprite);
    Balls[11]->SetDecal(BallElevenSprite);
    Balls[12]->SetDecal(BallTwelveSprite);
    Balls[13]->SetDecal(BallThirteenSprite);
    Balls[14]->SetDecal(BallFourteenSprite);
    Balls[15]->SetDecal(BallFifteenSprite);

    SetInitialBallsPosition();
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::DrawCue()
{
    const olc::vf2d DirectionVector = static_cast<olc::vf2d>(GetMousePos()) - CueBall->GetPosition();
    const olc::vf2d UnitDirectionVector = DirectionVector.norm();

    CurrentPlayer->GetCue().SetAngle(atan2f(UnitDirectionVector.y, UnitDirectionVector.x) + 3.1516f / 2.f);
    float CueDistance = CurrentPlayer->GetCue().GetDistance();

    if (GetMouse(0).bHeld && !bAreBallsMoving)
    {
        CueDistance = DirectionVector.mag();
    }

    CurrentPlayer->GetCue().SetDistance(CueDistance);

    olc::Pixel PlayerPixelTone;
    if (CurrentPlayer->GetBallType() == FPlayer::EBallType::Striped)
    {
        PlayerPixelTone = olc::RED;
    }
    else
    {
        PlayerPixelTone = olc::BLUE;
    }

    if (!bAreBallsMoving)
    {
        DrawRotatedDecal(
            CueBall->GetPosition() + CurrentPlayer->GetCue().GetDistance() * CurrentPlayer->GetCue().GetDirection(),
            CueDecal, CurrentPlayer->GetCue().GetAngle(), {40.f, 396.f}, {1, 1}, PlayerPixelTone);
    }
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::HitBall()
{
    if (GetMouse(0).bReleased && !bAreBallsMoving)
    {
        if (!GetMouse(1).bHeld)
        {
            CurrentPlayer->Strike(this);
            bIsTurnHappening = true;
            bHasScoredBall = false;
            bHasHit = true;
        }
        else
        {
            CurrentPlayer->GetCue().SetDistance(CueBall->GetRadius() + 10.f);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::SetInitialBallsPosition()
{
    for (int i = 1; i < static_cast<int>(Balls.capacity()); i++)
    {
        Balls[i]->SetActiveState(true);
    }
    CueBall->SetPosition(328.f + 25.f, 329.f + 25.f);
    Balls[1]->SetPosition(911.f + 25.f, 329.f + 25.f);
    Balls[2]->SetPosition(955.f + 25.f, 304.f + 25.f);
    Balls[3]->SetPosition(998.f + 25.f, 279.f + 25.f);
    Balls[4]->SetPosition(1042.f + 25.f, 253.f + 25.f);
    Balls[5]->SetPosition(1085.f + 25.f, 431.f + 25.f);
    Balls[6]->SetPosition(1085.f + 25.f, 278.f + 25.f);
    Balls[7]->SetPosition(1042.f + 25.f, 354.f + 25.f);
    Balls[8]->SetPosition(998.f + 25.f, 329.f + 25.f);
    Balls[9]->SetPosition(955.f + 25.f, 354.f + 25.f);
    Balls[10]->SetPosition(998.f + 25.f, 380.f + 25.f);
    Balls[11]->SetPosition(1042.f + 25.f, 405.f + 25.f);
    Balls[12]->SetPosition(1085.f + 25.f, 228.f + 25.f);
    Balls[13]->SetPosition(1085.f + 25.f, 380.f + 25.f);
    Balls[14]->SetPosition(1042.f + 25.f, 304.f + 25.f);
    Balls[15]->SetPosition(1085.f + 25.f, 329.f + 25.f);
}
//----------------------------------------------------------------------------------------------------------------------
bool FEightBallPool::CheckScored(FBall* Ball)
{
    const bool bCheckRightHolesX = Ball->GetPosition().x > 1181.f + 25.f;
    const bool bCheckLeftHolesX = Ball->GetPosition().x < 99.f - 25.f;
    const bool bCheckTopHolesY = Ball->GetPosition().y < 98.f - 25.f;
    const bool bCheckBottomHolesY = Ball->GetPosition().y > 608.f + 25.f;

    const bool bCheckTopLeftHole = bCheckTopHolesY && bCheckLeftHolesX;
    const bool bCheckTopMiddleHole = Ball->GetPosition().y < 68.f - 25.f;
    const bool bCheckTopRightHole = bCheckTopHolesY && bCheckRightHolesX;
    const bool bCheckBottomLeftHole = bCheckBottomHolesY && bCheckLeftHolesX;
    const bool bCheckBottomMiddleHole = Ball->GetPosition().y > 638.f + 25.f;
    const bool bCheckBottomRightHole = bCheckBottomHolesY && bCheckRightHolesX;

    if (bCheckTopLeftHole || bCheckTopMiddleHole || bCheckTopRightHole || bCheckBottomLeftHole || bCheckBottomMiddleHole
        || bCheckBottomRightHole)
    {
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::CollidePairs()
{
    for (auto& Pair : CollidingPairs)
    {
        // The normal vector to the tangential vector that separates the two circle centers
        olc::vf2d Normal = (Pair.first->GetPosition() - Pair.second->GetPosition()).norm();
        olc::vf2d Tangential = Normal.perp();

        const float TangentialDotProductFirst = Tangential.dot(Pair.first->GetVelocity());
        const float TangentialDotProductSecond = Tangential.dot(Pair.second->GetVelocity());

        const float NormalDotProductFirst = Normal.dot(Pair.first->GetVelocity());
        const float NormalDotProductSecond = Normal.dot(Pair.second->GetVelocity());

        float MomentumFirst = (2.f * Pair.second->GetRadius() * 10.f * NormalDotProductSecond) / (Pair.first->
            GetRadius() * 10.f + Pair.second->GetRadius() * 10.f);
        float MomentumSecond = (2.f * Pair.first->GetRadius() * 10.f * NormalDotProductFirst) / (Pair.first->
            GetRadius() * 10.f + Pair.second->GetRadius() * 10.f);

        Pair.first->SetVelocity(Tangential * TangentialDotProductFirst + Normal * MomentumFirst);
        Pair.second->SetVelocity(Tangential * TangentialDotProductSecond + Normal * MomentumSecond);
    }
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::UpdateBalls(const float ElapsedTime)
{
    for (auto& Ball : Balls)
    {
        Ball->Move(ElapsedTime);
        if (CheckScored(Ball))
        {
            HandleScoredBall(Ball);
        }

        if (!Ball->IsActive())
        {
            continue;
        }

        if (Ball->GetVelocity() != olc::vf2d{0.f, 0.f})
        {
            bAreBallsMoving = true;
        }

        DrawBall(Ball);

        CheckBallToEdgeCollisions(Ball);

        CheckBallToBallCollisions(Ball);
    }
    
    if (!bAreBallsMoving && !bHasScoredBall && bHasHit)
    {
        bIsTurnHappening = false;
    }
}
//----------------------------------------------------------------------------------------------------------------------
FPlayer& FEightBallPool::GetPlayer()
{
    return *CurrentPlayer;
}
//----------------------------------------------------------------------------------------------------------------------
FBall* FEightBallPool::GetCueBall()
{
    return CueBall;
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::DrawBall(const FBall* Ball)
{
    DrawDecal(Ball->GetPosition() - olc::vf2d(25.f, 25.f), Ball->GetDecal());
}
//----------------------------------------------------------------------------------------------------------------------
bool FEightBallPool::DoBallsOverlap(const FBall* Ball, const FBall* OtherBall) const
{
    return pow(Ball->GetPosition().x - OtherBall->GetPosition().x, 2.f) + pow(
        Ball->GetPosition().y - OtherBall->GetPosition().y, 2.f) <= pow(
        Ball->GetRadius() + OtherBall->GetRadius(), 2.f);
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::CheckBallToEdgeCollisions(FBall* Ball)
{
    for (const auto& Edge : Edges)
    {
        const olc::vf2d Line = Edge.first - Edge.second;
        const olc::vf2d LineStartToBall = Ball->GetPosition() - Edge.second;

        const float T = std::max(0.f, std::min(Line.mag2(), Line.dot(LineStartToBall))) / Line.mag2();
        const olc::vf2d ClosestPoint = Edge.second + T * Line;

        if ((Ball->GetPosition() - ClosestPoint).mag2() <= pow(Ball->GetRadius(), 2.f))
        {
            auto* FakeBall = new FBall(-1);
            FakeBall->SetPosition(
                ClosestPoint + (ClosestPoint - Ball->GetPosition()).norm() * Ball->GetRadius());
            Ball->SetVelocity(.7f * Ball->GetVelocity());
            FakeBall->SetVelocity(-Ball->GetVelocity());

            FakeBalls.push_back(FakeBall);
            CollidingPairs.emplace_back(Ball, FakeBall);

            const float BallsDistance = (Ball->GetPosition() - FakeBall->GetPosition()).mag();
            const float HalfOverlapDistance = 0.5f * (BallsDistance - Ball->GetRadius() - FakeBall->
                GetRadius());

            Ball->AddPosition(-HalfOverlapDistance * (Ball->GetPosition() - FakeBall->GetPosition()).norm());
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::CheckBallToBallCollisions(FBall* Ball)
{
    for (auto& TargetBall : Balls)
    {
        if (Ball->GetNumber() != TargetBall->GetNumber() && DoBallsOverlap(Ball, TargetBall))
        {
            CollidingPairs.emplace_back(Ball, TargetBall);

            const olc::vf2d Difference = Ball->GetPosition() - TargetBall->GetPosition();

            const float BallsDistance = Difference.mag();
            const float HalfOverlapDistance = 0.5f * (BallsDistance - Ball->GetRadius() - TargetBall->
                GetRadius());

            Ball->AddPosition(-HalfOverlapDistance * Difference.norm());
            TargetBall->AddPosition(HalfOverlapDistance * Difference.norm());
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::SwitchTurn()
{
    if (CurrentPlayer->GetBallType() == FPlayer::EBallType::Striped)
    {
        CurrentPlayer = &PlayerTwo;
    }
    else
    {
        CurrentPlayer = &PlayerOne;
    }

    bIsTurnHappening = true;
    bHasScoredBall = false;
    bHasHit = false;
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::HandleScoredBall(FBall* Ball)
{
    // Cue ball scored
    if (Ball->GetNumber() == 0)
    {
        PutCueBallBackOnTable();
        bIsTurnHappening = false;
    }
    // Ball 8 scored
    else if (Ball->GetNumber() == 8)
    {
        if (CurrentPlayer->GetScore() == 7 && Ball->IsActive())
        {
            Ball->SetActiveState(false);
            bHasScoredBall = true;
            SetInitialBallsPosition();
        }
        else
        {
            SetInitialBallsPosition();
        }
    }
    // Striped or solid ball scored
    else
    {
        if (Ball->GetNumber() < 8)
        {
            if (CurrentPlayer->GetBallType() == FPlayer::EBallType::Solid)
            {
                if (Ball->IsActive())
                {
                    bHasScoredBall = true;
                    Ball->SetActiveState(false);
                    CurrentPlayer->AddScore(1);
                }
            }
            else
            {
                if (Ball->IsActive())
                {
                    PutBallBackOnTable(Ball);
                    bIsTurnHappening = false;
                }
            }
        }
        else
        {
            if (CurrentPlayer->GetBallType() == FPlayer::EBallType::Striped)
            {
                if (Ball->IsActive())
                {
                    bHasScoredBall = true;
                    Ball->SetActiveState(false);
                    CurrentPlayer->AddScore(1);
                }
            }
            else
            {
                if (Ball->IsActive())
                {
                    PutBallBackOnTable(Ball);
                    bIsTurnHappening = false;
                }
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::PutBallBackOnTable(FBall* Ball)
{
    olc::vf2d NewPosition;
    do
    {
        NewPosition = {
            200.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 880.f)),
            200.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 308))
        };
    }
    while (IsPositionInAnyBall(NewPosition));

    Ball->SetVelocity({0.f, 0.f});
    Ball->SetPosition(NewPosition);
}
//----------------------------------------------------------------------------------------------------------------------
void FEightBallPool::PutCueBallBackOnTable()
{
    olc::vf2d NewPosition;
    do
    {
        NewPosition = {
            100.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 250.f)),
            100.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 508))
        };
    }
    while (IsPositionInAnyBall(NewPosition));

    CueBall->SetVelocity({0.f, 0.f});
    CueBall->SetPosition(NewPosition);
}
//----------------------------------------------------------------------------------------------------------------------
bool FEightBallPool::IsPositionInAnyBall(const olc::vf2d& Position) const
{
    for (auto& Ball : Balls)
    {
        if ((Ball->GetPosition() - Position).mag() <= Ball->GetRadius())
        {
            return true;
        }
    }

    return false;
}