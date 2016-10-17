#include "stdafx.h"
#include "Player.h"
#include "TinyXML/tinyxml.h"
#include "level.h"
#include "view.h"
#include "InitialData.h"
#include "weapons.h"

using namespace sf;
using namespace std;


void InitTextures(Textures & structure)
{
	Image hero_image;
	hero_image.loadFromFile("images/new hero.psd");
	structure.hero.loadFromImage(hero_image);

	Image bonus_image;
	bonus_image.loadFromFile("images/bonus.png");
	structure.bonus1.loadFromImage(bonus_image);

	Image enemy_image;
	enemy_image.loadFromFile("images/enemy.psd");
	structure.enemy.loadFromImage(enemy_image);
}

void InitEnemiesList(Level & lvl, ObjectsOfTheWorld & obj, Textures & texture, std::vector<Enemy> & enemies)
{
	vector<Object> enemiesList = lvl.GetObjects("enemy");
	for (auto i : enemiesList)
	{
		enemies.push_back(Enemy(texture.enemy, lvl, i.rect.left, i.rect.top, i.rect.width, i.rect.height));
	}
}

void EntitiesIntersection(ObjectsOfTheWorld &game, vector<Enemy> &enemies, vector<Weapons> &weapons)
{
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
	{
		for (auto weapon = weapons.begin(); weapon != weapons.end(); weapon++)
		{
			if (enemy->GetRect().intersects(weapon->GetRect()))
			{
				/////////// ÏÅÐÅÑÅ×ÅÍÈÅ ÂÐÀÃÀ Ñ ÏÓËÅÉ È ÓÌÅÍÜØÅÍÈÅ ÆÈÇÍÈ /////////////////
				weapon->life = false;
				enemy->health -= 40;
			}
		}
	}
}

void DrawListObjects(RenderWindow & window, float time, std::vector<Object> const& list, std::string const& name, Texture & texture, int left, int top, float & currentFrame)
{
	currentFrame += 0.01f * time;
	if (currentFrame > 6) currentFrame = 0;
	for (auto obj : list)
	{
		if (obj.name == name)
		{
			Sprite spr;
			spr.setTexture(texture);
			spr.setTextureRect(IntRect(left + (int)currentFrame * obj.rect.width, top, obj.rect.width, obj.rect.height));
			spr.setPosition(obj.rect.left, obj.rect.top);
			window.draw(spr);
		}
	}
}

void DrawAllObjects(RenderWindow & window, Level & lvl, Player & hero, ObjectsOfTheWorld & worldObj, Textures & textures, float time, std::vector<Enemy> & enemies)
{
	for (Enemy &enemy : enemies)
	{
		enemy.Update(time);
	}
	window.clear(Color::White);
	lvl.Draw(window);
	DrawListObjects(window, time, hero.obj, "bonus", textures.bonus1, 0, 0, worldObj.bonusCurrentFrame);
	window.draw(hero.sprite);

	for (Enemy enemy : enemies)
	{
		window.draw(enemy.sprite);
	}
	window.display();
}

void StartGame(RenderWindow & window, Textures & textures)
{
	std::vector<Enemy> enemies;
	Level lvl;
	lvl.LoadFromFile("level1.tmx");
	Player player(textures.hero, lvl);
	ObjectsOfTheWorld worldObj;
	
	InitEnemiesList(lvl, worldObj, textures, enemies);
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
		DrawAllObjects(window, lvl, player, worldObj, textures, time, enemies);
	}
}

int main()
{
	RenderWindow window(sf::VideoMode(WINDOWS_WIDTH, WINDOWS_HEIGHT), "EVERSPACE");
	view.reset(sf::FloatRect(0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT));
	
	Textures textures;
	InitTextures(textures);

	StartGame(window, textures);
	return 0;
}