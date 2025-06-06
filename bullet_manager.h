#pragma once
#include"bullet.h"
#include"manager.h"

#include<vector>

class BulletManager:public Manager<BulletManager>
{
	friend class Manager<BulletManager>;

public:
	BulletManager()
	{

	}
	~BulletManager()
	{

	}

private:

};
