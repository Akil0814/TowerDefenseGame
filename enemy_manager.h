#pragma once

#include"manager.h"
#include"enemy.h"
#include"config_manager.h"
#include"home_manager.h"

#include <vector>
#include<SDL.h>

class EnemyManager:public Manager<EnemyManager>
{
	friend class Manager<EnemyManager>;
public:
	typedef std::vector<Enemy*>EnemyList;
public:
	void on_update(double delta)
	{
		for (Enemy* enemy : enemy_list)
			enemy->on_update(delta);

		process_bullet_collision();
		process_home_collision();
	}

	void on_render(SDL_Renderer* renderer)
	{
		for (Enemy* enemy : enemy_list)
			enemy->on_render(renderer);
	}

	EnemyManager()=default;
	~EnemyManager()
	{
		for (Enemy* enemy : enemy_list)
			delete enemy;
	}

private:
	EnemyList enemy_list;

private:
	void process_home_collision()
	{
		static const SDL_Point& idx_home = ConfigManager::instance()->map.get_idx_home();
		static const SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;
		static const Vector2 position_home_tile =
		{
			(double)rect_tile_map.x + idx_home.x * SIZE_TILE,
			(double)rect_tile_map.y + idx_home.y * SIZE_TILE
		};

		for (Enemy* enemy : enemy_list) 
		{
			if (enemy->can_remove())continue;

			const Vector2& position = enemy->get_position();

			if (position.x >= position_home_tile.x && position.y >= position_home_tile.y
				&& position.x <= position_home_tile.x + SIZE_TILE && position.y <= position_home_tile.y + SIZE_TILE)
			{
				enemy->make_invalid();
				HomeManager::instance()->decrease_hp(enemy->get_damage());
			}
		}

	}

	void process_bullet_collision()
	{

	}

	void remove_invalid_enemy()
	{
		enemy_list.erase(std::remove_if(enemy_list.begin(), enemy_list.end(),
			[](const Enemy* enemy)
			{
				bool deletable = enemy->can_remove();
				if (deletable)
					delete enemy;
				return deletable;
			}), enemy_list.end());
	}
};
