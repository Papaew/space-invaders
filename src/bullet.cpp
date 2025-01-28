#include "bullet.hpp"
#include "game.hpp"
// #include "SDL3/SDL.h"
#include <iostream>

Bullet::Bullet(float w, float h, int direction)
{
	this->x = 0.0f;
	this->y = 0.0f;
	rect.x = this->x;
	rect.y = this->y;
	rect.w = w;
	rect.h = h;
	speed = 400.0f;
	r = 0.5f, g = 0.5f, b = 0.5f;
	this->direction = direction;
};

void Bullet::Update(double &dt)
{
	SetPosition(x,y+(direction * speed * dt));
    
    for (int i=0;  i<game::enemies.size(); i++)
	{
		Entity *e = game::enemies[i];
		if (game::collision(e->rect,this->rect))
		{
			this->isAlive = false;
			game::DestroyEnemy(i);
		}
	}
}

Bullet::~Bullet()
{

}