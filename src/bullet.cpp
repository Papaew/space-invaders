#include "bullet.hpp"
#include "game.hpp"
// #include "SDL3/SDL.h"

Bullet::Bullet(float w, float h)
{
	x = 0.0f;
	y = 0.0f;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	speed = 100.0f;
	r = 0.5f, g = 0.5f, b = 0.5f;
};

void Bullet::Update(double &dt)
{
	SetPosition(x,y+(-1 * speed * dt));
    
    
    
}

Bullet::~Bullet()
{

}