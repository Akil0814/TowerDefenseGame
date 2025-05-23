#pragma once

#include"manager.h"
#include"enemy.h"
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

	EnemyManager() {};
	~EnemyManager() {};

private:
	EnemyList enemy_list;

private:
	void process_home_collision()
	{

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
