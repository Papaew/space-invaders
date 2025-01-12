#include <iostream>
#include <typeinfo>
#include "SDL3/SDL.h"
#include <string>
#include <vector>

#include "entity.hpp"
#include "game.hpp"

void print(const std::string &message)
{
	std::cout << message << std::endl;
}

namespace game
{
	GameState state = {true};

	Entity unit(10.0f, 10.0f, 32.0f, 32.0f, 100.0f);

	std::vector<Entity*> enemies;

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

		for (int iy = 0; iy < 2; iy++)
		{
			for (int ix = 0; ix < 6; ix++)
			{
				Entity *e = new Entity;
				e->SetPosition(ix*50.0f,iy*50.0f);
				enemies.push_back(e);
			}
		}
		print("Game loaded!");
	}

	void update(double &dt)
	{
		// std::string msg = std::string("dt: ") + std::to_string(dt);
		// print(msg);
		const bool *keys = SDL_GetKeyboardState(NULL);
		float dirx, diry;

		dirx = (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_D]) ? 0 : (keys[SDL_SCANCODE_A]) ? -1
																: (keys[SDL_SCANCODE_D])   ? 1
																						   : 0;
		diry = (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_W]) ? 0 : (keys[SDL_SCANCODE_W]) ? -1
																: (keys[SDL_SCANCODE_S])   ? 1
																						   : 0;

		unit.Move(dirx * unit.speed * dt, diry * unit.speed * dt);
	}

	void draw(SDL_Renderer *renderer)
	{
		unit.Render(renderer);
		for (int i=0;  i<enemies.size(); i++)
		{
			enemies[i]->Render(renderer);
		}
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
