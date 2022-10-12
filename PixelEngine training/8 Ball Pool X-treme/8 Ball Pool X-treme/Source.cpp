#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Player.h"

class FEightBallPool : public olc::PixelGameEngine
{
private:
    olc::Sprite* Background = nullptr;
    olc::Decal* BackgroundDecal = nullptr;

    olc::Sprite* CueBallSprite = nullptr;
    olc::Decal* CueBallDecal = nullptr;
    
    FBall CueBall = FBall({(float)ScreenWidth() / 2.f,(float)ScreenHeight() / 2.f});

    std::list<std::pair<olc::vf2d, olc::vf2d>> BoundaryLineSegments;

public:
    FEightBallPool()
    {
        sAppName = "8-Ball pool X-TREME";
    }

    bool OnUserCreate() override
    {
        Clear(olc::Pixel(234, 221, 202));

        Background = new olc::Sprite("./Images/Table.png");
        BackgroundDecal = new olc::Decal(Background);

        CueBallSprite = new olc::Sprite("./Images/CueBall.png");
        CueBallDecal = new olc::Decal(CueBallSprite);

        BoundaryLineSegments.push_back({{100,55},{113,68}});
        BoundaryLineSegments.push_back({{113,68},{607,68}});
        BoundaryLineSegments.push_back({{607,68},{611,56}});
        BoundaryLineSegments.push_back({{668,56},{671,68}});
        BoundaryLineSegments.push_back({{671,68},{1167,68}});
        BoundaryLineSegments.push_back({{1167,68},{1180,55}});
        BoundaryLineSegments.push_back({{1224,99},{1211,112}});
        BoundaryLineSegments.push_back({{1211,112},{1211,594}});
        BoundaryLineSegments.push_back({{1211,594},{1224,607}});
        BoundaryLineSegments.push_back({{1180,651},{1167,638}});
        BoundaryLineSegments.push_back({{1167,638},{671,638}});
        BoundaryLineSegments.push_back({{671,638},{668,649}});
        BoundaryLineSegments.push_back({{611,649},{607,638}});
        BoundaryLineSegments.push_back({{607,638},{113,638}});
        BoundaryLineSegments.push_back({{113,638},{100,651}});
        BoundaryLineSegments.push_back({{56,607},{69,594}});
        BoundaryLineSegments.push_back({{69,594},{69,112}});
        BoundaryLineSegments.push_back({{69,512},{56,99}});

        CueBall.SetPosition((float)ScreenWidth() / 2.f,(float)ScreenHeight() / 2.f);

        CueBall.SetVelocity(180.f,100);
        return true;
    }

    bool OnUserUpdate(float ElapsedTime) override
    {
        DrawDecal({0.f, 0.f}, BackgroundDecal);

        CueBall.Move(ElapsedTime);
        PrintBall(CueBall);

        return true;
    }

    void PrintBall(FBall& Ball)
    {
        DrawDecal(Ball.GetPosition()-olc::vf2d(25.f,25.f),CueBallDecal);
    }
};

int main()
{
    FEightBallPool Game;
    if (Game.Construct(1280, 708, 1, 1))
        Game.Start();
}
