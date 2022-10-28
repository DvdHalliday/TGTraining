#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"


class FAsteroidsGame : public olc::PixelGameEngine
{
private:
	struct FSpaceObject
	{
		float X;
		float Y;

		float Dx;
		float Dy;

		int Size;

		float Angle;
	};

	struct FModel
	{
		std::vector<std::pair<float, float>> ModelVector;
	};

	std::vector<FSpaceObject> Asteroids;
	std::vector<FSpaceObject> Bullets;

	FSpaceObject Player;
	bool bDead;

	int Score;

	FModel Ship;
	FModel Asteroid;

public:
	FAsteroidsGame()
	{
		sAppName = "Asteroids";
	}

	bool OnUserCreate() override
	{
		Ship.ModelVector =
		{
			{0.f, -5.f},
			{-2.5f, 2.5f},
			{2.5f, 2.5f}
		};

		int VerticesAmount = 30;
		for (int i = 0; i < VerticesAmount; i++)
		{
			float Radius = (float)rand() / (float)RAND_MAX * .1f + .95f;
			float Angle = (float)i / (float)VerticesAmount * 6.283185f;
			Asteroid.ModelVector.push_back(std::make_pair(Radius * sinf(Angle), Radius * cosf(Angle)));
		}

		ResetGame();

		return true;
	}

	bool OnUserUpdate(float ElapsedTime) override
	{
		if (bDead)
		{
			ResetGame();
		}

		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

		// Left steer
		if (GetKey(olc::LEFT).bHeld)
		{
			Player.Angle -= 5.f * ElapsedTime;
		}
		// Right steer
		if (GetKey(olc::RIGHT).bHeld)
		{
			Player.Angle += 5.f * ElapsedTime;
		}

		// Thrust
		if (GetKey(olc::UP).bHeld)
		{
			Player.Dx += sin(Player.Angle) * 50.f * ElapsedTime;
			Player.Dy -= cos(Player.Angle) * 50.f * ElapsedTime;
		}

		// Update position
		Player.X += Player.Dx * ElapsedTime;
		Player.Y += Player.Dy * ElapsedTime;

		// Check boundaries
		WrapCoordinates(Player.X, Player.Y, Player.X, Player.Y);

		if (GetKey(olc::SPACE).bReleased)
		{
			// Let's calculate a value that go from 0 to 1 in accordance to the dot product of the player's angle
			// and the player's momentum, this values will then be multiplied to the player's momentum.
			float Linearity = (NormalizedDotProduct(Player.Dx, Player.Dy, sinf(Player.Angle), -cosf(Player.Angle)) + 1.f) / 2.f;
			Bullets.push_back({ Player.X, Player.Y, Linearity * Player.Dx + 100.f * sinf(Player.Angle), Linearity * Player.Dy - 100.f * cosf(Player.Angle), 0, 0 });
		}

		// Draw & update asteroids
		for (FSpaceObject& CurrentAsteroid : Asteroids)
		{
			UpdateAsteroid(CurrentAsteroid, ElapsedTime);
		
			// Draw Asteroid
			DrawWireFrameModel(Asteroid.ModelVector, CurrentAsteroid.X, CurrentAsteroid.Y, CurrentAsteroid.Angle, (float)CurrentAsteroid.Size, olc::Pixel(255, 150, 0));

			if (IsPointInsideCircle(Player.X, Player.Y, CurrentAsteroid.X, CurrentAsteroid.Y, (float)CurrentAsteroid.Size))
			{
				bDead = true;
			}
		}

		std::vector<FSpaceObject> NewAsteroids;

		// Draw & update bullet
		for (FSpaceObject& Bullet : Bullets)
		{
			Bullet.X += Bullet.Dx * ElapsedTime;
			Bullet.Y += Bullet.Dy * ElapsedTime;

			// Draw bullet
			FillRect((int)Bullet.X, (int)Bullet.Y, 2, 2);

			DetectBulletInAsteroids(Bullet, NewAsteroids);
		}

		for (FSpaceObject& CurrentAsteroid : NewAsteroids)
		{
			Asteroids.push_back(CurrentAsteroid);
		}

		RemoveBullets();

		if (!Asteroids.empty())
		{
			auto Iterator = std::remove_if(Asteroids.begin(), Asteroids.end(), [&](FSpaceObject SpaceObject) {return SpaceObject.X < 0; });
			if (Iterator != Asteroids.end())
			{
				Asteroids.erase(Iterator);
			}
		}
		else
		{
			Score += 50;

			Asteroids.push_back({ 70 * sinf(Player.Angle - 3.14159f / 2.f), 70 * cosf(Player.Angle - 3.14159f / 2.f),
				50 * sinf(Player.Angle), 50 * cosf(Player.Angle), (int)64, 0.f });
			Asteroids.push_back({ 100 * sinf(Player.Angle - 3.14159f / 2.f), 100 * cosf(Player.Angle - 3.14159f / 2.f),
				50 * sinf(-Player.Angle), 50 * cosf(-Player.Angle), (int)64, 0.f });

		}

		// Draw player
		DrawWireFrameModel(Ship.ModelVector, Player.X, Player.Y, Player.Angle, 4.f);

		// Draw score
		DrawString(2, 2, "Score: " + std::to_string(Score), olc::WHITE, 1);

		return true;
	}

	void ResetGame()
	{
		Asteroids.clear();
		Bullets.clear();

		Asteroids.push_back({ 20.f, 20.f, 80.f, 16.f, (int)64, 0.f });
		Asteroids.push_back({ 100.f, 70.f, -40.f, 46.f, (int)64, 0.f });

		// Player initialising setup
		Player.X = (float)ScreenWidth() / 2.f;
		Player.Y = (float)ScreenHeight() / 2.f;
		Player.Dx = 0.f;
		Player.Dy = 0.f;
		Player.Angle = 0.f;
		bDead = false;

		bDead = false;

		Score = 0;
	}

	void UpdateAsteroid(FSpaceObject& CurrentAsteroid, float ElapsedTime)
	{
		CurrentAsteroid.X += CurrentAsteroid.Dx * ElapsedTime;
		CurrentAsteroid.Y += CurrentAsteroid.Dy * ElapsedTime;
		CurrentAsteroid.Angle += .5f * ElapsedTime;

		WrapCoordinates(CurrentAsteroid.X, CurrentAsteroid.Y, CurrentAsteroid.X, CurrentAsteroid.Y);
	}

	void DetectBulletInAsteroids(FSpaceObject& Bullet, std::vector<FSpaceObject>& OutNewAsteroids)
	{
		for (FSpaceObject& CurrentAsteroid : Asteroids)
		{
			if (IsPointInsideCircle(Bullet.X, Bullet.Y, CurrentAsteroid.X, CurrentAsteroid.Y, (float)CurrentAsteroid.Size))
			{
				Bullet.X = -100.f;

				if (CurrentAsteroid.Size > 16)
				{
					float AngleFirstAsteroid = ((float)rand() / (float)RAND_MAX) * 6.283185f;
					float AngleSecondAsteroid = ((float)rand() / (float)RAND_MAX) * 6.283185f;

					OutNewAsteroids.push_back({ CurrentAsteroid.X, CurrentAsteroid.Y, 80 * sinf(AngleFirstAsteroid), 40 * cosf(AngleFirstAsteroid), CurrentAsteroid.Size / 2, 0.f });
					OutNewAsteroids.push_back({ CurrentAsteroid.X, CurrentAsteroid.Y, 40 * sinf(AngleSecondAsteroid), 80 * cosf(AngleSecondAsteroid), CurrentAsteroid.Size / 2, 0.f });
				}

				CurrentAsteroid.X = -100.f;

				Score += 10;
			}
		}
	}

	void RemoveBullets()
	{
		if (!Bullets.empty())
		{
			auto Iterator = std::remove_if(Bullets.begin(), Bullets.end(), [&](FSpaceObject SpaceObject)
				{return SpaceObject.X < 1 || SpaceObject.Y < 1 ||
				SpaceObject.X >= ScreenWidth() - 1 ||
				SpaceObject.Y >= ScreenHeight() - 1; });
			if (Iterator != Bullets.end())
			{
				Bullets.erase(Iterator);
			}
		}
	}

	float NormalizedDotProduct(float FirstX, float FirstY, float SecondX, float SecondY)
	{
		float FirstNorm = sqrt(FirstX * FirstX + FirstY * FirstY);
		float SecondNorm = sqrt(SecondX * SecondX + SecondY * SecondY);

		if (FirstNorm == 0)
		{
			FirstNorm = 1;
		}
		if (SecondNorm == 0)
		{
			SecondNorm = 1;
		}
		return (FirstX * SecondX + FirstY * SecondY) / (FirstNorm * SecondNorm);
	}

	bool IsPointInsideCircle(float PointX, float PointY, float CenterX, float CenterY, float Radius)
	{
		return sqrt((PointX - CenterX) * (PointX - CenterX) + (PointY - CenterY) * (PointY - CenterY)) <= Radius;
	}

	void WrapCoordinates(float InputX, float InputY, float& OutputX, float& OutputY)
	{
		OutputX = InputX;
		OutputY = InputY;

		if (InputX < 0.f)
		{
			OutputX += (float)ScreenWidth();
		}
		if (InputX >= ScreenWidth())
		{
			OutputX -= (float)ScreenWidth();
		}

		if (InputY < 0.f)
		{
			OutputY += (float)ScreenHeight();
		}
		if (InputY >= ScreenHeight())
		{
			OutputY -= (float)ScreenHeight();
		}
	}

	bool Draw(int32_t x, int32_t y, olc::Pixel p = olc::WHITE) override
	{
		float FormattedX;
		float FormattedY;

		WrapCoordinates(x, y, FormattedX, FormattedY);

		return PixelGameEngine::Draw(FormattedX, FormattedY, p);
	}

	// Original code from Javid, modified for the PixelGameEngine
	void DrawWireFrameModel(const std::vector<std::pair<float, float>>& vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f, olc::Pixel Color = olc::WHITE)
	{
		// pair.first = x coordinate
		// pair.second = y coordinate

		// Create translated model vector of coordinate pairs
		std::vector<std::pair<float, float>> vecTransformedCoordinates;
		int verts = vecModelCoordinates.size();
		vecTransformedCoordinates.resize(verts);

		// Rotate
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecModelCoordinates[i].first * cosf(r) - vecModelCoordinates[i].second * sinf(r);
			vecTransformedCoordinates[i].second = vecModelCoordinates[i].first * sinf(r) + vecModelCoordinates[i].second * cosf(r);
		}

		// Scale
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first * s;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second * s;
		}

		// Translate
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;
		}

		// Draw Closed Polygon
		for (int i = 0; i < verts + 1; i++)
		{
			int j = (i + 1);
			DrawLine(vecTransformedCoordinates[i % verts].first, vecTransformedCoordinates[i % verts].second,
				vecTransformedCoordinates[j % verts].first, vecTransformedCoordinates[j % verts].second, Color);
		}
	}

};

int main()
{
	FAsteroidsGame AsteroidsGame;
	if (AsteroidsGame.Construct(640, 400, 2, 2))
		AsteroidsGame.Start();
	return 0;
}