
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "SDL3/SDL.h"
#include <vector>
#include "entity.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "papo4ka.hpp"

namespace game
{
	struct GameState {
        bool running;
		int direction = 1; //enemy
		float speedMult = 1.0f; //enemy
		int maxEnemyCount = 0;
		float coolDown = 0;
		int playerLives = 3; 
    };
    extern GameState state;

	extern std::vector<Enemy*> enemies;
	extern std::vector<Enemy*> shooters;
	extern std::vector<Bullet*> bullets;

	void load(SDL_Window *window);
	void update(double &dt);
	void shiftEnemiesDown();
	void draw(SDL_Renderer *renderer);
	void CalcDelta();
	double GetDelta();
	void OnKeyDown(SDL_KeyboardEvent keyEvent);
	void DestroyBullet (int index);
	void DestroyEnemy (int index);
	bool collision(SDL_FRect &r1,SDL_FRect &r2);
	void drawText(std::string text, SDL_Renderer *renderer);
}

#endif