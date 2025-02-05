#include "SDL3/SDL.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	float x, y;
	float r = 0.5f, g = 0.5f, b = 0.5f;
	float speed;
	bool isAlive = true;
	SDL_FRect rect;
	Player(float posX, float posY, float w, float h, float s);
	void SetPosition(float newX, float newY);
	float GetWidth();
	float GetHeight();
	void Move(float stepX, float stepY);
	void Render(SDL_Renderer *renderer);
	void SetColor(float r, float g, float b);
	~Player();
};

#endif