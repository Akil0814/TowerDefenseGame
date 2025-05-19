#pragma once

#include"timer.h"

#include<SDL.h>
#include<vector>
#include<functional>

class Animation
{
public:
	typedef std::function<void()> PlayCallback;

public:
	Animation()
	{
		timer.set_one_shot(false);
		timer.set_on_timeout(
			[&]()
			{
				idx_frame++;
				if (idx_frame >= rect_src_list.size())
				{
					idx_frame = is_loop ? 0 : rect_src_list.size() - 1;
					if (!is_loop && on_finished)
						on_finished();
				}
			}
		);
	}


private:
	Timer timer;
	bool is_loop = true;
	size_t idx_frame = 0;
	PlayCallback on_finished;
	SDL_Texture* texture = nullptr;
	std::vector<SDL_Rect> rect_src_list;
	int width_frame = 0;
	int height_frame = 0;


};