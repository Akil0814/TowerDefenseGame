#pragma once

#include "map.h"
//#include "wave.h"
#include "manager.h"

#include <SDL.h>
#include <string>
#include <cJSON.h>
#include <fstream>
#include <sstream>
#include <iostream>

class ConfigManager:public Manager<ConfigManager>
{
	friend class Manager<ConfigManager>;

public:
	struct BasicTemplate
	{

	};

public:
	ConfigManager() = default;
	~ConfigManager() = default;

private:

};