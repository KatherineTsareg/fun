#ifndef weap_h
#define weap_h
#include <SFML/Graphics.hpp>
#include "level.h"
#include "InitialData.h"

using namespace sf;

class Weapons {
private:
	float x, y;
public:
	bool life;
	float dx = 0;
	float dy = 0;
	int w, h;
	float speed = 0.2f;
	IntRect rect;
	Direction dir;
	Texture texture;
	Sprite sprite;
	std::vector<Object> obj;
	Weapons(Texture & texture, Player & hero, Level &lvl, float time) {
		rect = { 25, hero.getplayercoordinateX() * 12 * 4 + 12, w , h };
		sprite.setOrigin((float)w / 2.0f, (float)h / 2.0f);
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		x = hero.getplayercoordinateX();
		y = hero.getplayercoordinateY;
		dir = hero.state;
		speed = 0.4f;
		life = true;
		obj = lvl.GetObjects("solid");
	}
	void Weapons::Update(float time, FloatRect const& heroRect);
	void Weapons::interactionWithMap();
	FloatRect Weapons::GetRect();
};

#endif
