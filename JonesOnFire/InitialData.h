#pragma once
#include "stdafx.h"
#include "enemy.h"

const size_t WINDOWS_WIDTH = 980;
const size_t WINDOWS_HEIGHT = 600;
const int BONUS_SCORE = 20;

typedef enum Direction{ STAY, LEFT, RIGHT, JUMP, FALL, SHOOT };
enum direct{ isleft, isright };

struct Textures
{
	sf::Texture bonus1, bonus2;
	sf::Texture hero, enemy;
	sf::Texture weapon, bang;
};

struct ObjectsOfTheWorld
{
	float bonusCurrentFrame = 0;
	size_t level = 1;
	bool newLevel = false;
};

