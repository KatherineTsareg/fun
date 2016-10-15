#pragma once
#include "stdafx.h"
#include "level.h"
//#include <SFML/Graphics.hpp>

const int ground = 420;


class Player
{
public:
	Player(sf::Texture & texture, Level & lvl);

	float dx, dy, speed;
	int playerScore;//новая переменная, хранящая очки игрока
	bool onGround;
	
	void Control();
	void Update(float time);
	float getplayercoordinateX() { return x; }
	float getplayercoordinateY() { return y; }
	sf::Sprite sprite;
	enum {STAY, LEFT, RIGHT, JUMP, FALL} state;
	FloatRect GetRect();
private:
	float x, y;
	float currentFrame, currentFrameJump;
	float w = 75.f;
	float h = 152.f;
	sf::FloatRect rect;
	bool jump;
	std::vector<Object> obj;

	void setTextureRectByState(float time);
	void Collision(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	void JumpAnimation(float time);
};