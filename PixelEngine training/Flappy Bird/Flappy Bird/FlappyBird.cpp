#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
struct FBird
{
public:
	int X;

	float Position = 0.f;
	float Acceleration = 0.f;
	float Velocity = 0.f;

	FBird(int NewX = 0) : X(NewX) {}
};

class FGame : public olc::PixelGameEngine
{
public:
	FGame()
	{
		sAppName = "Flappy Bird";
	}

private:
	float Gravity = 700.f;

	FBird Bird;

	std::list<int> SectionList;
	float SectionWidth;
	float LevelPosition = 0.f;

	int AttemptCount = 0;
	int FlapCount = 0;
	int MaxFlapCount = 0;

	bool bHasCollided = false;
	bool bResetGame = false;

protected:
	bool OnUserCreate() override
	{
		SectionList = { 0, 0, 0, 0 };
		SectionWidth = (float)ScreenWidth() / (float)(SectionList.size() - 1);

		Bird = FBird((int)(ScreenWidth() / 3.f));
		Bird.Position = 15.f;

		bResetGame = true;

		return true;
	}

	bool OnUserUpdate(float ElapsedTime) override
	{
		if (bResetGame)
		{
			bHasCollided = false;
			bResetGame = false;

			SectionList = { 0, 0, 0, 0 };

			Bird.Acceleration = 0.f;
			Bird.Velocity = 0.f;
			Bird.Position = 15.f;

			FlapCount = 0;
			AttemptCount++;
		}

		if (bHasCollided)
		{
			if (GetKey(olc::Key::SPACE).bReleased)
			{
				bResetGame = true;
			}
		}
		else
		{
			if (GetKey(olc::Key::SPACE).bPressed && Bird.Velocity >= Gravity / 40.f)
			{
				Bird.Acceleration = 0.f;
				Bird.Velocity = -Gravity / 6.f;

				FlapCount++;
				if (FlapCount > MaxFlapCount)
				{
					MaxFlapCount = FlapCount;
				}
			}
			else
			{
				Bird.Acceleration += Gravity * ElapsedTime;
			}

			if (Bird.Acceleration >= Gravity)
			{
				Bird.Acceleration = Gravity;
			}

			Bird.Velocity += Bird.Acceleration * ElapsedTime;
			Bird.Position += Bird.Velocity * ElapsedTime;

			LevelPosition += 170.f * ElapsedTime;

			if (LevelPosition > SectionWidth)
			{
				LevelPosition -= SectionWidth;
				SectionList.pop_front();

				int NewSection = rand() % (ScreenHeight() - 100);
				if (NewSection <= 50)
				{
					NewSection = 0;
				}

				SectionList.push_back(NewSection);
			}

			FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

			int CurrentSectionIndex = 0;
			for (int Section : SectionList)
			{
				if (Section != 0)
				{
					FillRect(CurrentSectionIndex * SectionWidth + 30 - LevelPosition, ScreenHeight() - Section,
						60, ScreenHeight(), olc::VERY_DARK_GREEN);

					FillRect(CurrentSectionIndex * SectionWidth + 30 - LevelPosition, 0,
						60, ScreenHeight() - Section - 120, olc::VERY_DARK_GREEN);
				}
				CurrentSectionIndex++;
			}

			bHasCollided = Bird.Position < 2 || Bird.Position > ScreenHeight() - 20;

			if (Bird.Velocity > 0)
			{
				DrawString(Bird.X, Bird.Position, "\\\\\\");
				DrawString(Bird.X, Bird.Position + 8, "<\\\\\\=Q");

				if (!bHasCollided)
				{
					bHasCollided = GetDrawTarget()->GetPixel(Bird.X, Bird.Position) == olc::VERY_DARK_GREEN ||
						GetDrawTarget()->GetPixel(Bird.X, Bird.Position + 16) == olc::VERY_DARK_GREEN ||
						GetDrawTarget()->GetPixel(Bird.X + 24, Bird.Position) == olc::VERY_DARK_GREEN ||
						GetDrawTarget()->GetPixel(Bird.X + 48, Bird.Position + 8) == olc::VERY_DARK_GREEN ||
						GetDrawTarget()->GetPixel(Bird.X + 48, Bird.Position + 16) == olc::VERY_DARK_GREEN;
				}
			}
			else
			{
				DrawString(Bird.X, Bird.Position, "<///=Q");
				DrawString(Bird.X, Bird.Position + 8, "///");

				if (!bHasCollided)
				{
					bHasCollided = GetDrawTarget()->GetPixel(Bird.X, Bird.Position) == olc::VERY_DARK_GREEN ||
						GetDrawTarget()->GetPixel(Bird.X, Bird.Position + 16) == olc::VERY_DARK_GREEN ||
						GetDrawTarget()->GetPixel(Bird.X + 48, Bird.Position) == olc::VERY_DARK_GREEN ||
						GetDrawTarget()->GetPixel(Bird.X + 48, Bird.Position + 8) == olc::VERY_DARK_GREEN ||
						GetDrawTarget()->GetPixel(Bird.X + 24, Bird.Position + 16) == olc::VERY_DARK_GREEN;
				}
			}

			DrawString(1, 1, "Attempt: " + std::to_string(AttemptCount) + " Score: " + std::to_string(FlapCount) + " Highest Score: " + std::to_string(MaxFlapCount));
		}

		return true;
	}
};

int main()
{
	FGame demo;

	if (demo.Construct(720, 350, 2, 2))
		demo.Start();
}