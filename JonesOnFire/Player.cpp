#include "Player.h"

using namespace std;
using namespace sf;

Player::Player(Texture & texture, Level & lvl)
	: speed(0.1f)
	, score(0)
	, currentFrame(0)
	, currentFrameJump(0)
	, state(STAY)
	, dy(0)
	, onGround(true)
{
	Object p = lvl.GetObject("hero");
	x = (float)p.rect.left;
	y = (float)p.rect.top;
	rect = sf::FloatRect(0, 0, w, h);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));
	dx = speed;
	obj = lvl.GetAllObjects();
}

void Player::Control()
{
	if ((Keyboard::isKeyPressed(Keyboard::Left)) & (state != JUMP))
	{
		state = LEFT;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Right))& (state != JUMP))
	{
		state = RIGHT;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround))
	{
		state = JUMP;
	}
	if (Keyboard::isKeyPressed(Keyboard::X))
	{
		isShoot = true;
	}
}

void Player::setTextureRectByState(float time)
{
	currentFrame += 0.005 * time;
	if (currentFrame > 6) currentFrame -= 6;
	switch (state)
	{
	case (LEFT):
		dx = -speed;
		sprite.setTextureRect(IntRect(w * int(currentFrame), 2 * h, w, h));
		break;
	case (RIGHT):
		dx = speed;
		sprite.setTextureRect(IntRect(w * int(currentFrame), h, w, h));
		break;
	case (STAY):
		break;
	case (JUMP):
		dy = -1.f;
		dx = 0.2f;
		onGround = false;
		break;
	}
		
}

void Player::JumpAnimation(float time)
{
	if (!onGround)
	{
		currentFrameJump += 0.006 * time;
		if (currentFrameJump > 2) currentFrameJump = 0;
		if (dx >= 0)
		{
			sprite.setTextureRect(IntRect(140 * int(currentFrameJump), 3 * h, 140, h));
			
		}
		else if (dx < 0)
		{
			sprite.setTextureRect(IntRect(140 * int(currentFrameJump), 4 * h, 140, h));
		}
	}
	
}

void Player::Update(float time)
{
	Control();
	setTextureRectByState(time);
	JumpAnimation(time);
	state = STAY;
	
	if (!onGround)
	{
		dy += time * 0.0015f;
	}
	x += dx * time;
	checkCollisionWithMap(dx, 0);
	y += dy * time;
	checkCollisionWithMap(0, dy);
	sprite.setPosition(x, y);
	dy += 0.0015 * time;
	dx = 0;
}

FloatRect Player::GetRect()
{
	return FloatRect( x, y, w, h );
}


void Player::Collision(float time)//�-��� �������������� � ������
{
	for (int i = 0; i < obj.size(); i++)//���������� �� ��������
		if (GetRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			if (obj[i].name == "solid")//���� ��������� �����������
			{
				if (dy > 0) //���� �� ��� ����,
				{
					y = obj[i].rect.top - h;//�� �������� ���������� ����� ���������.
					onGround = true;
				}
				if (dy < 0)
					y = obj[i].rect.top + obj[i].rect.height;//���������� � ������� �����. dy<0, ������ �� ���� �����
				if (dx > 0)
					x = obj[i].rect.left - w; // ���� ���� ������, �� ���������� � ����� �����(������ 0) ����� ������ ���������
				if (dx < 0)
					x = obj[i].rect.left + obj[i].rect.width;//���������� ���� �����
			}
		}
}

void Player::checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
{
	for (int i = 0; i < obj.size(); i++)//���������� �� ��������
		if (GetRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{			
			if (obj[i].name == "solid")//���� ��������� �����������
			{
				if (Dy > 0) //���� �� ��� ����,
				{
					y = obj[i].rect.top - h;//�� �������� ���������� ����� ���������.
					dy = 0;
					onGround = true;
				}
				if (Dy < 0)
				{
					y = obj[i].rect.top + obj[i].rect.height;//���������� � ������� �����. dy<0, ������ �� ���� �����
					dy = 0;
				}
				if (Dx > 0)
					x = obj[i].rect.left - w; // ���� ���� ������, �� ���������� � ����� �����(������ 0) ����� ������ ���������
				if (Dx < 0)
					x = obj[i].rect.left + obj[i].rect.width;//���������� ���� �����
			}
			else if (obj[i].name == "bonus")
			{
				obj.erase(obj.begin() + i);
				score += BONUS_SCORE;
			}
			else if (obj[i].name == "enemy")
			{

			}
			else { onGround = false; }
		}
}

