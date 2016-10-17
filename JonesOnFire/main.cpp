#include "stdafx.h"
#include "Game.h"


int main()
{
	RenderWindow window(sf::VideoMode(WINDOWS_WIDTH, WINDOWS_HEIGHT), "EVERSPACE");
	view.reset(sf::FloatRect(0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT));
	
	Textures textures;
	InitTextures(textures);
	ObjectsOfTheWorld worldObj;

	GameRunning(window, textures, worldObj);
	return 0;
}