
#include <iostream>
#include <string>

#include "LuaJIT/lua.hpp"
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "src/limb.hpp"
#include "src/game.hpp"

SDL_AppResult SDL_Fail()
{
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
	SDL_Quit();
    return SDL_APP_FAILURE;
}

int main()
{
	std::cout << std::endl;

	if (!SDL_SetAppMetadata("limb-SDL", LIMB_VERSION_STRING, "com.unevenbird.limb"))
	{
		return SDL_Fail();
	}

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
	{
		return SDL_Fail();
	}

	// init TTF
    if (!TTF_Init()) return SDL_Fail();

	// create a window
	std::string title = "Test Window";
    SDL_Window* window = SDL_CreateWindow(title.c_str(), 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_BORDERLESS | SDL_WINDOW_MAXIMIZED);
    if (!window) return SDL_Fail();

	// create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) return SDL_Fail();

	bool vsync = SDL_GetRenderVSync(renderer, SDL_RENDERER_VSYNC_DISABLED);
	std::cout << "Is vsync: " << std::to_string(vsync) << std::endl;

	int num_render_drivers = SDL_GetNumRenderDrivers();
	for (int i = 0; i < num_render_drivers - 1; i++)
	{
		std::string name = SDL_GetRenderDriver(i);
		std::cout << name << std::endl;
	}

	/* lua_State *L = luaL_newstate();
	if (L == NULL)
	{
		return -1;
	}

	luaL_openlibs(L);
	luaL_loadstring(L, "print(Hello from lua!)");
	lua_call(L, 0, 0);
	lua_close(L); */

	game::load(window);

	bool quit;
	SDL_Event event;

	double dt;

	

	while (game::state.running)
	{
		while (SDL_PollEvent(&event))
		{
			// switch (event.type)
			// {
			// case SDL_EVENT_QUIT:
			// 	game::state.running = false;
			// 	quit = true;
			// 	break;
			// case SDL_EVENT_KEY_DOWN:
			// 	game::OnKeyDown(event.key);
			// 	break;
			// }

			if (event.type == SDL_EVENT_QUIT)
			{
				game::state.running = false;
				quit = true;
				break;
			}
			else if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0)
			{
				game::OnKeyDown(event.key);
			}
			
			

			// if (quit)
			// 	break;
		}

		game::CalcDelta();

		double Delta = game::GetDelta();
		game::update(Delta);

		SDL_SetRenderDrawColorFloat(renderer, 0.0f, 0.0f, 0.0f, SDL_ALPHA_OPAQUE_FLOAT);
		SDL_RenderClear(renderer);
			game::draw(renderer);
			// game::drawText("shopa", renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}