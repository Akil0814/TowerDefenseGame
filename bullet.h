#pragma once
#include"vector2.h"
#include"animation.h"

class Bullet
{
public:
	Bullet() {}
	~Bullet() {}

	void set_velocity(const Vector2& velocity)
	{
		this->velocity = velocity;

		if (can_rotated)
		{
			double radian = std::atan2(velocity.y, velocity.x);
			angle_anim_rotated = radian * 180 / 3.14159265;
		}
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	void set_damage()
	{
		this->damage = damage;
	}

protected:
	Vector2 size;
	Vector2 velocity;
	Vector2 position;

	Animation animation;
	bool can_rotated = false;

	double damage = 0;
	double damage_range = -1;

private:
	bool is_valid = true;
	bool is_collisional = true;
	double angle_anim_rotated = 0;

};

