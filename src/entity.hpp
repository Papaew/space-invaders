#include "SDL3/SDL.h"

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	float x, y;
	float r = 0.5f, g = 0.5f, b = 0.5f;
	float speed;
	SDL_FRect rect;
	Entity();
	Entity(float posX, float posY, float w, float h, float s);
	void SetPosition(float newX, float newY);
	void Move(float stepX, float stepY);
	void Render(SDL_Renderer *renderer);
	void SetColor(float r,float g, float b);
};

#endif