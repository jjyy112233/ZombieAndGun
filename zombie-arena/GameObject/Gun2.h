#pragma once
#include "Gun.h"
class Gun2 : public Gun
{
protected:
	bool isAllReload;
	bool isReload;
	float bulletDelat;

	float bulletCnt;
	float MaxBulletCnt;
	float initBulletDelay;
public:
	Gun2(ObjectPool<Bullet>* bulletPool);
	virtual ~Gun2();
	virtual void Init();
	virtual void Set();
	virtual void Reset();

	virtual bool Reload();
	virtual void Shoot(Vector2f playerPos);

	virtual void Update(float dt);
	virtual bool GetState();
};

