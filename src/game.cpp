#include <iostream>
#include <typeinfo>
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <string>
#include <vector>
#include <cmath>

#include "entity.hpp"
#include "game.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "papo4ka.hpp"

void print(const std::string &message)
{
	std::cout << message << std::endl;
}

TTF_Font* font = TTF_OpenFont("res/courier-normal.ttf", 32);

namespace game
{
	GameState state = {true};

	// Player unit(10.0f, 10.0f, 30.0f, 30.0f, 300.0f);
	Player* unit = new Player (10.0f, 10.0f, 30.0f, 30.0f, 300.0f);


	std::vector<Enemy*> enemies;
	std::vector<Enemy*> shooters;
	std::vector<Bullet*> bullets;

	int leftborder,rightborder;
	bool needToShiftDown = false;

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
		leftborder = 100; 
		rightborder = windowWidth- 100;

		int enemyCol = 11, enemyRow = 5;
		int Gap = 50;
		float enemyWidth = 30.0f;
		float enemyHeight = 30.0f;
		float totalEntitiesWidth = enemyWidth * enemyCol + Gap * (enemyCol-1);
		float totalEntitiesHeight = enemyHeight * enemyRow + Gap * (enemyRow-1);
		float offsetX = (windowWidth-totalEntitiesWidth)*0.5f;
		float offsetY = (windowHeight-totalEntitiesHeight)*0.1f;

		for (int iy = 0; iy < enemyRow; iy++)
		{
			for (int ix = 0; ix < enemyCol; ix++)
			{
				Enemy *e = new Enemy(enemyWidth,enemyHeight);
				float x = ix*(enemyWidth+Gap);
				float y = iy*(enemyHeight+Gap);
				e->SetPosition(x+offsetX,y+offsetY);
				enemies.push_back(e);
			}
		}

		state.maxEnemyCount = enemies.size();

		unit->SetPosition(windowWidth/2-unit->rect.w/2,windowHeight-offsetY-unit->rect.h);
		
		print("Game loaded!");
	}

	void update(double &dt)
	{	
		state.coolDown -= dt;
		// std::string msg = std::string("dt: ") + std::to_string(dt);
		// print(msg);
		const bool *keys = SDL_GetKeyboardState(NULL);
		float dirx, diry;

		dirx = (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_D]) ? 0 : (keys[SDL_SCANCODE_A]) ? -1 : (keys[SDL_SCANCODE_D]) ? 1 : 0;
		// diry = (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_W]) ? 0 : (keys[SDL_SCANCODE_W]) ? -1 : (keys[SDL_SCANCODE_S]) ? 1 : 0;

		unit->Move(dirx * unit->speed * dt, 0.0f);
		// printf ("%.2f , %.2f \n", unit.speed*dt, diry);

		if (needToShiftDown)
		{
			state.direction *= -1;
			shiftEnemiesDown();
		}

		for (int i = enemies.size()-1; i >= 0; i--)
		{
			enemies[i]->Update(dt); //Обновляем
			if ( enemies[i]->x > rightborder || enemies[i]->x < leftborder)
			{
				needToShiftDown = true;
			}
		}


		for (int i = bullets.size()-1; i >= 0; i--)
		{
			bullets[i]->Update(dt); //Обновляем
			if (bullets[i]->y <= 0.0f-bullets[i]->rect.h || !bullets[i]->isAlive)
			{
				DestroyBullet(i);
			}
		}

		if (state.coolDown > 0) return;
		for (int i = enemies.size()-1; i >= 0; i--)
		{
			SDL_FRect collider;
			collider.w = enemies[i]->rect.w;
			collider.h = enemies[i]->rect.h*1000;
			collider.x = enemies[i]->rect.x;
			collider.y = enemies[i]->rect.y;
			bool found = false;

			for (int g = enemies.size()-1; g >= 0; g--)
			{
				if (i == g) continue; 
				
				if (collision(enemies[g]->rect,collider))
				{
					found = true;
					break;
				}
			}

			if (!found)
			{
				shooters.push_back(enemies[i]);
			}
			
		}
		shooters[SDL_rand(shooters.size()-1)]->Shoot();

		shooters.clear();
		state.coolDown = 2.0f;

	}

	void draw(SDL_Renderer *renderer)
	{
		unit->Render(renderer);

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
			TTF_CloseFont(font);
			break;
		case SDLK_SPACE:
			Bullet *b = new Bullet(10.0f,20.0f,-1);
			b->SetPosition(unit->x + (unit->rect.w - b->rect.w) / 2, unit->y - b->rect.h);
			b->SetColor(1.0f,0.0f,0.0f);
			bullets.push_back(b);
			break;
			// Bullet *b = new Bullet(20.0f,20.0f);
			// b->SetPosition(unit.x + (unit.rect.w - b->rect.w) / 2, unit.y - b->rect.h);
			// b->SetColor(1.0f,0.0f,0.0f);
			// bullets.push_back(b);
			// break;
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

	void DestroyBullet (int i)
	{
		delete bullets[i];
		bullets.erase(bullets.begin()+i);
	}
	
	void DestroyEnemy (int i)
	{
		delete enemies[i];
		enemies.erase(enemies.begin()+i);
		state.speedMult = pow (1.05f,state.maxEnemyCount - enemies.size());
	}

	void DestroyPlayer ()
	{
		delete unit;
	}
	
	void shiftEnemiesDown()
	{
		for (int i = enemies.size()-1; i >= 0; i--)
		{
			enemies[i]->Move(0.0f,30.0f);
			enemies[i]->Update(dt);
		}
		needToShiftDown = false;
	}
	
	bool collision(SDL_FRect &r1,SDL_FRect &r2)
	{
		return (r1.x < r2.x + r2.w && r1.x + r1.w > r2.x && 
			r1.y < r2.y + r2.h && r1.y + r1.h > r2.y);
	}

	void drawText(std::string text, SDL_Renderer *renderer)
	{
		// //txt shish
		// SDL_Color White = {200, 200, 200};
		// std::string txt = "lake = ocean";
        // SDL_Surface* surface = TTF_RenderText_Blended(font, txt.c_str(), txt.size(), White); // TODO: destroy surface?
        // SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); // ! Crashed on/before? shutdown from thisline's mem alloc??? 
        // SDL_DestroySurface(surface);
		// int width = 0;
		// int height = 0;
		// // height = TTF_GetFontHeight(font); // даня вумный
		// TTF_GetStringSize(font, txt.c_str(), txt.size(), &width, &height);
        // SDL_FRect dstRect{100, 100, width, height}; // x, y, w, h
        // SDL_RenderTexture(renderer, texture, NULL, &dstRect);
        // SDL_DestroyTexture(texture); // ? Is this safe to do here ? who knows?

		
	}
}
