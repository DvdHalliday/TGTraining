#include "EightBallPool.h"

FEightBallPool::FEightBallPool()
{
    sAppName = "8-Ball pool X-TREME";
}

bool FEightBallPool::OnUserCreate()
{
    Clear(olc::Pixel(234, 221, 202));

    Background = new olc::Sprite("./Images/Table.png");
    BackgroundDecal = new olc::Decal(Background);

    CueSprite = new olc::Sprite("./Images/Cue.png");
    CueDecal = new olc::Decal(CueSprite);

    CueBallSprite = new olc::Sprite("./Images/CueBall.png");
    CueBall->SetDecal(CueBallSprite);

    BallOneSprite = new olc::Sprite("./Images/BallOne.png");
    BallOne->SetDecal(BallOneSprite);

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

    CueBall->SetPosition(static_cast<float>(ScreenWidth()) / 3.f, static_cast<float>(ScreenHeight()) / 2.f);
    BallOne->SetPosition(static_cast<float>(ScreenWidth()) / 3.f, static_cast<float>(ScreenHeight()) / 3.f);

    CueBall->SetVelocity(0.f, 0.f);
    BallOne->SetVelocity(0.f, 0.f);

    Balls.push_back(CueBall);
    Balls.push_back(BallOne);
    return true;
}

bool FEightBallPool::OnUserUpdate(float ElapsedTime)
{
        DrawDecal({0.f, 0.f}, BackgroundDecal);
        
        std::list<std::pair<FBall*, FBall*>> CollidingPairs;
        
        for (auto& Ball : Balls)
        {
            Ball->Move(ElapsedTime);
            DrawBall(Ball);
            
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
                    FakeBall->SetVelocity(-Ball->GetVelocity());

                    FakeBalls.push_back(FakeBall);
                    CollidingPairs.emplace_back(Ball, FakeBall);

                    const float BallsDistance = (Ball->GetPosition() - FakeBall->GetPosition()).mag();
                    const float HalfOverlapDistance = 0.5f * (BallsDistance - Ball->GetRadius() - FakeBall->
                        GetRadius());

                    Ball->AddPosition(-HalfOverlapDistance * (Ball->GetPosition() - FakeBall->GetPosition()).norm());
                    Ball->SetVelocity(.9f * Ball->GetVelocity());
                }
            }

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

        olc::vf2d DirectionVector = static_cast<olc::vf2d>(GetMousePos()) - CueBall->GetPosition();
        olc::vf2d UnitDirectionVector = DirectionVector.norm();
        PlayerOne.GetCue().SetAngle(atan2f(UnitDirectionVector.y,UnitDirectionVector.x) + 3.1516f / 2.f);
        PlayerOne.GetCue().SetDistance(DirectionVector.mag());
        DrawRotatedDecal(CueBall->GetPosition() + PlayerOne.GetCue().GetDistance() * PlayerOne.GetCue().GetDirection(), CueDecal, PlayerOne.GetCue().GetAngle(), {40.f,396.f});

        if (GetMouse(0).bReleased)
        {
            PlayerOne.Strike(this);
        }
        CollidingPairs.clear();

        for (const auto& FakeBall : FakeBalls)
        {
            delete FakeBall;
        }

        FakeBalls.clear();

        return true;
    }

FPlayer& FEightBallPool::GetPlayer()
{
    return PlayerOne;
}

FBall* FEightBallPool::GetCueBall()
{
    return CueBall;
}

void FEightBallPool::DrawBall(const FBall* Ball)
{
    DrawDecal(Ball->GetPosition() - olc::vf2d(25.f, 25.f), Ball->GetDecal());
}

bool FEightBallPool::DoBallsOverlap(const FBall* Ball, const FBall* OtherBall) const
{
    return pow(Ball->GetPosition().x - OtherBall->GetPosition().x, 2.f) + pow(
        Ball->GetPosition().y - OtherBall->GetPosition().y, 2.f) <= pow(
        Ball->GetRadius() + OtherBall->GetRadius(), 2.f);
}
