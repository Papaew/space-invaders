#include "enemy.hpp"
#include "game.hpp"

Enemy::Enemy(float w, float h)
{
    this->x = 0.0f;
	this->y = 0.0f;
    rect.x = this->x;
	rect.y = this->y;
    rect.w = w;
	rect.h = h;
    speed = 100.0f;
    // direction = 1;
}

void Enemy::Update(double &dt)
{
    SetPosition(x + speed * game::state.direction * dt * game::state.speedMult, y);
}

Enemy::~Enemy()
{

}