#pragma once
#include "manager.h"
#include"timer.h"
#include"config_manager.h"

class WaveManager:public Manager<WaveManager>
{
	friend class Manager<WaveManager>;
public:
	WaveManager()
	{
		static const std::vector<Wave>& wave_list = ConfigManager::instance()->wave_list;

		timer_start_wave.set_one_shot(true);
		timer_start_wave.set_wait_time(wave_list[0].interval);
		timer_start_wave.set_on_timeout(
			[&]() 
			{
				is_wave_started = true;
				timer_spawn_enemy.set_wait_time(wave_list[idx_wave].spawn_event_list[0].interval);
				timer_spawn_enemy.restart();
			});

		timer_spawn_enemy.set_one_shot(true);
		timer_spawn_enemy.set_on_timeout([&]()
			{

			});


	}
	~WaveManager()
	{

	}

private:

	int idx_wave = 0;
	int idx_spawn_event = 0;
	Timer timer_start_wave;
	Timer timer_spawn_enemy;

	bool is_wave_started = false;
	bool is_spawned_last_enemy = false;


};

