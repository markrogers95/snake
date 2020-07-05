#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>

using namespace std;

class snakeGame : public olc::PixelGameEngine
{
public:
	snakeGame()
	{
		sAppName = "SNAKE";
	}

private:

	int xPos = 0;
	int yPos = 0;

	int xVel = 0;
	int yVel = 0;

	int length = 0;

	int foodXPos;
	int foodYPos;

	vector<std::vector<int>> tail;

	int* pixel_array;

	void update(int xVel, int yVel) {
		this->xPos += xVel;
		this->yPos += yVel;
	}

protected:

	bool OnUserCreate() override {

		Draw(this->xPos, this->yPos, olc::Pixel(255, 255, 255));

		foodXPos = rand() % ScreenWidth();
		foodYPos = rand() % ScreenHeight();

		Draw(foodXPos, foodYPos, olc::Pixel(255, 0, 0));

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		this_thread::sleep_for(50ms);

		if (this->tail.begin() != this->tail.end()) {
	
			for (int i = 0; i < tail.size() - 1; i++) {
				if (tail[i][0] == this->xPos && tail[i][1] == this->yPos) {
					return true;
				}
				tail[i] = tail[i + 1];
			}
			this->tail[length - 1] = { this->xPos, this->yPos };
		}

		if (this->xPos == this->foodXPos && this->yPos == this->foodYPos) {
			foodXPos = rand() % ScreenWidth();
			foodYPos = rand() % ScreenHeight();
			length++;

			vector<int> tailInsert = { xPos, yPos };
			tail.push_back(tailInsert);
		}

		if (GetKey(olc::LEFT).bPressed) {
			if (this->xVel == 1) {
				return true;
			}
			this->xVel = -1;
			this->yVel = 0;
		}

		if (GetKey(olc::RIGHT).bPressed) {
			if (this->xVel == -1) {
				return true;
			}
			this->xVel = 1;
			this->yVel = 0;
		}
		if (GetKey(olc::UP).bPressed) {
			if (this->yVel == 1) {
				return true;
			}
			this->yVel = -1;
			this->xVel = 0;
		}
		if (GetKey(olc::DOWN).bPressed) {
			if (this->yVel == -1) {
				return true;
			}
			this->yVel = 1;
			this->xVel = 0;
		}

		if (this->xPos == ScreenWidth()) {
			this->xPos = 0;
		}

		if (this->xPos == -1) {
			this->xPos = ScreenWidth();
		}

		if (this->yPos == ScreenHeight()) {
			this->yPos = 0;
		}

		if (this->yPos == -1) {
			this->yPos = ScreenHeight();
		}




		this->update(this->xVel, this->yVel);

		for (int i = 0; i < ScreenWidth(); i++) {
			for (int j = 0; j < ScreenHeight(); j++) {
				Draw(i, j, olc::Pixel(0, 0, 0));
			}
		}

		for (int k = 0; k < tail.size(); k++) {
			if (tail[k][0] == this->xPos && tail[k][1] == this->yPos) {
				while (!GetKey(olc::Key::SPACE).bHeld) {
					return true;
				}
			}
			Draw(tail[k][0], tail[k][1], olc::Pixel(255, 255, 255));
		}

		Draw(this->xPos, this->yPos, olc::Pixel(255, 255, 255));
		Draw(foodXPos, foodYPos, olc::Pixel(255, 0, 0));
		return true;
	}
	

};


int main()
{
	snakeGame demo;
	demo.Construct(50, 50, 8, 8);
	demo.Start();
	return 0;
}