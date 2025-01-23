
#ifndef GAME_H
#define GAME_H

#include "SDL3/SDL.h"
#include <vector>
#include "entity.hpp"
#include "bullet.hpp"
#include "enemy.hpp"

namespace game
{
	struct GameState {
        bool running;
		int direction = 1;
		float speedMult = 1.0f;
		int maxEnemyCount = 0;
    };
    extern GameState state;

	extern std::vector<Enemy*> enemies;
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
}

#endif