// #include "SDL3/SDL.h"

#ifndef BULLET_H
#define BULLET_H

#include "entity.hpp"

class Bullet : public Entity
{
public:
    //Тащим с entity
	// float x, y;
	// float r = 0.5f, g = 0.5f, b = 0.5f;
	// float speed;
	// SDL_FRect rect;
	// Entity();
	// Entity(float posX, float posY, float w, float h, float s);
	// Entity(float w, float h);
	// void SetPosition(float newX, float newY);
	// float GetWidth();
	// float GetHeight();
	// void Move(float stepX, float stepY);
	// void Render(SDL_Renderer *renderer);
	// void SetColor(float r, float g, float b);

    Bullet(float w, float h);
	void Update(double &dt);

    virtual ~Bullet();
};

#endif