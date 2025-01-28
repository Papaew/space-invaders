#include "entity.hpp"
#include "SDL3/SDL.h"
#include <iostream>

Entity::Entity()
{
	x = 0.0f;
	y = 0.0f;
	rect.x = x;
	rect.y = y;
	rect.w = 30.0f;
	rect.h = 30.0f;
	speed = 100.0f;
	r = 0.5f, g = 1.0f, b = 0.5f;
};

Entity::Entity(float posX, float posY, float w, float h, float s) : r(0.5f), g(0.5f), b(0.5f)
{
	x = posX;
	y = posY;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	speed = s;
};

void Entity::SetPosition(float newX, float newY)
{
	x = newX;
	y = newY;
	rect.x = x;
	rect.y = y;
}

float Entity::GetWidth()
{
	return rect.w;
}

float Entity::GetHeight()
{
	return rect.h;
}

void Entity::Move(float stepX, float stepY)
{
	SetPosition(x + stepX, y + stepY);
}

void Entity::SetColor(float newR, float newG, float newB)
{
	r = newR;
	g = newG;
	b = newB;
}

void Entity::Render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColorFloat(renderer, r, g, b, 1.0f);
	SDL_RenderFillRect(renderer, &rect);
}

Entity::~Entity()
{

}