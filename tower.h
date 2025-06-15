#pragma once
#include"vector2.h"
#include"animation.h"
#include"tower_type.h"
#include"bullet_manager.h"

class Tower
{
public:
	Tower();
	~Tower();


protected:
	Vector2 size;

	Animation anim_idle_up;
	Animation anim_idle_down;
	Animation anim_idle_left;
	Animation anim_idle_right;

	Animation anim_fire_up;
	Animation anim_fire_down;
	Animation anim_fire_left;
	Animation anim_fire_right;

	TowerType tower_type =TowerType::Archer;

	double fire_speed = 0;
	BulletType bullet_type = BulletType::Arrow;

private:
	Timer timer_fire;
	Vector2 position;
	bool can_fire = true;


};