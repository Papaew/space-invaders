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

	Entity unit(10.0f, 10.0f, 100.0f, 100.0f, 300.0f);

	std::vector<Entity*> enemies;

	std::vector<Entity*> bullets;

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

	void load(SDL_Window *window)
	{
		state.running = true;

		int windowWidth, windowHeight;
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);

		int enemyCol = 7, enemyRow = 3;
		int Gap = 50;
		float entityWidth = 100.0f;
		float entityHeight = 100.0f;
		float totalEntitiesWidth = entityWidth * enemyCol + Gap * (enemyCol-1);
		float totalEntitiesHeight = entityHeight * enemyRow + Gap * (enemyRow-1);
		float offsetX = (windowWidth-totalEntitiesWidth)*0.5f;
		float offsetY = (windowHeight-totalEntitiesHeight)*0.1f;

		for (int iy = 0; iy < enemyRow; iy++)
		{
			for (int ix = 0; ix < enemyCol; ix++)
			{
				Entity *e = new Entity;
				float x = ix*(entityWidth+Gap);
				float y = iy*(entityHeight+Gap);
				e->SetPosition(x+offsetX,y+offsetY);
				enemies.push_back(e);
			}
		}

		unit.SetPosition(windowWidth/2-unit.rect.w/2,windowHeight-offsetY-unit.rect.h);

		print("Game loaded!");
	}

	void update(double &dt)
	{
		// std::string msg = std::string("dt: ") + std::to_string(dt);
		// print(msg);
		const bool *keys = SDL_GetKeyboardState(NULL);
		float dirx, diry;

		dirx = (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_D]) ? 0 : (keys[SDL_SCANCODE_A]) ? -1 : (keys[SDL_SCANCODE_D]) ? 1 : 0;
		diry = (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_W]) ? 0 : (keys[SDL_SCANCODE_W]) ? -1 : (keys[SDL_SCANCODE_S]) ? 1 : 0;

		unit.Move(dirx * unit.speed * dt, diry * unit.speed * dt);
		
		for (int i=0; i<bullets.size(); i++)
		{
			bullets[i]->Update(dt);
		}
	}

	void draw(SDL_Renderer *renderer)
	{
		unit.Render(renderer);

		for (int i=0;  i<enemies.size(); i++)
		{
			enemies[i]->Render(renderer);
		}

		for (int i=0;  i<bullets.size(); i++)
		{
			bullets[i]->Render(renderer);
		}
	}

	void OnKeyDown(SDL_KeyboardEvent keyEvent)
	{
		switch (keyEvent.key)
		{
		case SDLK_ESCAPE:
			state.running = false;
			break;
		case SDLK_SPACE:
			Entity *b = new Entity(20.0f,20.0f);
			b->SetPosition(unit.x + (unit.rect.w - b->rect.w) / 2, unit.y - b->rect.h);
			b->SetColor(1.0f,0.0f,0.0f);
			bullets.push_back(b);
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
