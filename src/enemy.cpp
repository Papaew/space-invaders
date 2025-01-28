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
    speed = 70.0f;
}

void Enemy::Update(double &dt)
{
    SetPosition(x + speed * game::state.direction * dt * game::state.speedMult, y);
}

void Enemy::Shoot()
{
    Bullet *b = new Bullet(10.0f,20.0f,1);
    b->SetPosition(x + (rect.w - b->rect.w) / 2, y + b->rect.h + 10);
    b->SetColor(1.0f,0.0f,0.0f);
    game::bullets.push_back(b);
}

Enemy::~Enemy()
{

}
