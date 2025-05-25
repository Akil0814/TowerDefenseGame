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

