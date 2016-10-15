#include "stdafx.h"
#include "Player.h"

using namespace sf;

void start_game() 
{
	RenderWindow window(sf::VideoMode(980, 600), "111");

	//��������� �������� ��� ���������//
	Image hero_image;
	hero_image.loadFromFile("images/new hero.psd");
	Texture herotex;
	herotex.loadFromImage(hero_image);
	Player player(herotex);


	float coordinatePlayerX, coordinatePlayerY = 0;
	coordinatePlayerX = player.getplayercoordinateX();
	coordinatePlayerY = player.getplayercoordinateY();

	Clock clock;
	RectangleShape rectangle(Vector2f(32, 32));

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
		


		player.Control();
		player.Player::Update(time);
		
		window.clear(Color::White);
		window.draw(player.sprite);
		window.display();	
	}
}


int main()
{
	start_game();
	return 0;
}