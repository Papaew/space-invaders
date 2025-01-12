#include "SDL3/SDL.h"

namespace game
{
	struct GameState {
        bool running;
		
    };
    extern GameState state;

	void load();
	void update(double &dt);
	void draw(SDL_Renderer *renderer);
	void CalcDelta();
	double GetDelta();
	void OnKeyDown(SDL_KeyboardEvent keyEvent);
}