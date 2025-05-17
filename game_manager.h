#pragma once

#include"manager.h"
#include"config_manager.h"
#include"resources_manager.h"

#include<SDL.h>
#include <SDL_ttf.h>//字体库
#include <SDL_mixer.h>//音频库
#include <SDL_image.h>//图像库
#include <SDL2_gfxPrimitives.h>

class GameManager :public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:
	int run(int argc, char** argv)
	{

		Uint64 last_counter = SDL_GetPerformanceCounter();
		const Uint64 counter_freq = SDL_GetPerformanceFrequency();//获取高性能计数器的频率

		while (!is_quit)
		{
			while (SDL_PollEvent(&event))
				on_input();

			Uint64 current_counter = SDL_GetPerformanceCounter();//实现动态延时
			double delta = (double)(current_counter - last_counter) / counter_freq;
			last_counter = current_counter;

			if (delta * 1000 < 1000.0 / 60)
				SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));

			on_update(delta);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			on_render();

			SDL_RenderPresent(renderer);
		}

		return 0;
	}

protected:
	GameManager()
	{
		init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 Error");
		init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG),u8"SDL_img Error");
		init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer Error");
		init_assert(!TTF_Init(), u8"SDL_ttf Error");
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

		ConfigManager* config = ConfigManager::instance();
		init_assert(config->map.load("map.csv"), u8"加载游戏地图失败");
		init_assert(config->load_level_config("level.json"), u8"加载关卡配置失败！");
		init_assert(config->load_game_config("config.json"), u8"加载游戏配置失败！");

		SDL_Window* window = SDL_CreateWindow(config->basic_template.window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			config->basic_template.window_width, config->basic_template.window_height, SDL_WINDOW_SHOWN);//创建窗口
		init_assert(window,u8"SDL_CreateWindow Error");

		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);//硬件加速 垂直同步 目标纹理
		init_assert(renderer, u8"SDL_CreateRenderer Error");

		init_assert(ResourcesManager::instance()->load_from_file(renderer), u8"加载游戏资源失败！");

		init_assert(generate_tile_map_texture(), u8"生成瓦片地图纹理失败！");
	}

	~GameManager()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}
private:
	SDL_Event event;
	bool is_quit = false;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Texture* tex_tile_map = nullptr;

private:
	void init_assert(bool flag, const char* err_msg)
	{
		if (flag)
			return;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"Game Start Error", err_msg, window);
		exit(-1);
	}

	void on_input()
	{

	}

	void on_update(double delta)
	{

	}

	void on_render()
	{

	}

	bool generate_tile_map_texture()
	{
		const Map& map = ConfigManager::instance()->map;
		const TileMap& tile_map = map.get_tile_map();
		SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;
		SDL_Texture* tex_tile_set = ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Tileset)->second;

		int width_tex_tile_set, height_tex_tile_set;
		SDL_QueryTexture(tex_tile_set, nullptr, nullptr, &width_tex_tile_set, &height_tex_tile_set);
		int num_tile_single_line = (int)std::ceil((double)width_tex_tile_set / SIZE_TILE);//ceil向上取整

		int width_tex_tile_map, height_tex_tile_map;
		width_tex_tile_map = (int)map.get_width() * SIZE_TILE;
		height_tex_tile_map = (int)map.get_height() * SIZE_TILE;

		tex_tile_map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, width_tex_tile_map, height_tex_tile_map);
		if (!tex_tile_map) return false;

		ConfigManager* config = ConfigManager::instance();
		rect_tile_map.x = (config->basic_template.window_width - width_tex_tile_map) / 2;

		return true;
	}
};