#include <iostream>
#include <typeinfo>
#include "SDL3/SDL.h"
#include <string>

#include "game.hpp"

void print(const std::string &message)
{
	std::cout << message << std::endl;
}

class Entity
{
public:
	float x, y;
	float speed;
	SDL_FRect rect;

	Entity()
	{
		x = 0.0f;
		y = 0.0f;
		rect.x = x;
		rect.y = y;
		rect.w = 32.0f;
		rect.h = 32.0f;
		speed = 100.0f;
	};

	Entity(float posX, float posY, float w, float h, float s)
	{
		x = posX;
		y = posY;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		speed = s;
	};

	void SetPosition(float newX, float newY)
	{
		x = newX;
		y = newY;
		rect.x = x;
		rect.y = y;
	}

	void Move(float stepX, float stepY)
	{
		SetPosition(x+stepX, y+stepY);
	}
};

namespace game
{
	GameState state = { true };

	Entity unit(10.0f, 10.0f, 32.0f, 32.0f, 100.0f);

	double dt;

	Uint64 old_time = 0, now_time = SDL_GetPerformanceCounter();
	double freq = SDL_GetPerformanceFrequency();
	void CalcDelta()
	{
		old_time = now_time;
		now_time = SDL_GetPerformanceCounter();
		dt = (double)((now_time - old_time) * 1'000 / freq) * 0.001;
	}

	double GetDelta()
	{
		return dt;
	}

	void load()
	{
		state.running = true;

		print("Game loaded!");
	}

	void update(double &dt)
	{
		// std::string msg = std::string("dt: ") + std::to_string(dt);
		// print(msg);
		const bool *keys = SDL_GetKeyboardState(NULL);
		float dirx, diry;

		dirx = (keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_LEFT]) ? 0 : (keys[SDL_SCANCODE_LEFT]) ? -1 : (keys[SDL_SCANCODE_RIGHT]) ? 1 : 0;
		diry = (keys[SDL_SCANCODE_DOWN] && keys[SDL_SCANCODE_UP]) ? 0 : (keys[SDL_SCANCODE_UP]) ? -1 : (keys[SDL_SCANCODE_DOWN]) ? 1 : 0;

		unit.Move(dirx*unit.speed*dt, diry*unit.speed*dt);
	}

	void draw(SDL_Renderer *renderer)
	{
		SDL_SetRenderDrawColorFloat(renderer, 0.5f, 0.5f, 0.0f, 1.0f);
		SDL_RenderFillRect(renderer, &unit.rect);
	}

	void OnKeyDown(SDL_KeyboardEvent keyEvent)
	{
		switch (keyEvent.key)
		{
		case SDLK_ESCAPE:
			state.running = false;
			break;
		}
		/*	switch (keyEvent.key)
		{
		case SDLK_DOWN:
			Character.rect.y=Character.rect.y+Character.speed;
			break;
		case SDLK_UP:
			Character.rect.y=Character.rect.y-Character.speed;
			break;
		}
		switch (keyEvent.key)
		{
		case SDLK_RIGHT:
			Character.rect.x=Character.rect.x+Character.speed;
			break;
		case SDLK_LEFT:
			Character.rect.x=Character.rect.x-Character.speed;
			break;
		}*/
	}

}
