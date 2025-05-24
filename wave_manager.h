#pragma once
#include "manager.h"
#include"timer.h"

class WaveManager:public Manager<WaveManager>
{
	friend class Manager<WaveManager>;
public:
	WaveManager()
	{

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

