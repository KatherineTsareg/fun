#include "stdafx.h"
#include "Player.h"
#include "TinyXML/tinyxml.h"
#include "level.h"
#include "view.h"
#include "InitialData.h"

using namespace sf;

void start_game() 
{
	RenderWindow window(sf::VideoMode(WINDOWS_WIDTH, WINDOWS_HEIGHT), "111");
	view.reset(sf::FloatRect(0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT));

	Level lvl;
	lvl.LoadFromFile("level2.tmx");

	//генерация текстуры для персонажа//
	Image hero_image;
	hero_image.loadFromFile("images/new hero.psd");
	Texture herotex;
	herotex.loadFromImage(hero_image);
	Player player(herotex, lvl);
	

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		player.Player::Update(time);

		SetCoordinateForView(player.getplayercoordinateX(), player.getplayercoordinateY());
		window.setView(view);
		window.clear(Color::White);
		lvl.Draw(window);
		window.draw(player.sprite);
		window.display();	
	}
}


int main()
{
	start_game();
	return 0;
}