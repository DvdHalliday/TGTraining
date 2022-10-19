#define OLC_PGE_APPLICATION
#include "EightBallPool.h"

int main()
{
    FEightBallPool Game;
    if (Game.Construct(1280, 708, 1, 1))
        Game.Start();
}
