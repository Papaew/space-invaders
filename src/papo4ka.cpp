#include "entity.hpp"
#include "papo4ka.hpp"
#include "SDL3/SDL.h"
#include <iostream>

// Entity::Entity()
// {
// 	x = 0.0f;
// 	y = 0.0f;
// 	rect.x = x;
// 	rect.y = y;
// 	rect.w = 30.0f;
// 	rect.h = 30.0f;
// 	speed = 100.0f;
// 	r = 0.5f, g = 1.0f, b = 0.5f;
// };

Player::Player(float posX, float posY, float w, float h, float s) : r(0.5f), g(0.5f), b(0.5f)
{
	x = posX;
	y = posY;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	speed = s;
};

void Player::SetPosition(float newX, float newY)
{
	x = newX;
	y = newY;
	rect.x = x;
	rect.y = y;
}

float Player::GetWidth()
{
	return rect.w;
}

float Player::GetHeight()
{
	return rect.h;
}

void Player::Move(float stepX, float stepY)
{
	SetPosition(x + stepX, y + stepY);
    // printf ("%.2f, %.2f , %.2f , %.2f \n", stepY , stepX , y , x);
}

void Player::SetColor(float newR, float newG, float newB)
{
	r = newR;
	g = newG;
	b = newB;
}

void Player::Render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColorFloat(renderer, r, g, b, 1.0f);
	SDL_RenderFillRect(renderer, &rect);
}

Player::~Player()
{

}