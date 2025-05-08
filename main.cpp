#define SDL_MAIN_HANDLED

#include"game_manager.h"

int main(int argc,char** argv)
{
	GameManager* instance = GameManager::instance();
	return instance->run(argc, argv);
}