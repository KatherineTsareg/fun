#pragma once
#include "stdafx.h"
#include "enemy.h"

const size_t WINDOWS_WIDTH = 980;
const size_t WINDOWS_HEIGHT = 600;
const int BONUS_SCORE = 20;

typedef enum Direction{ RIGHT,LEFT, UP, DOWN };

struct Textures
{
	sf::Texture bonus1, bonus2;
	sf::Texture hero, enemy;
};

struct ObjectsOfTheWorld
{
	float bonusCurrentFrame = 0;
	//std::vector<Enemy> enemies;
	
};

