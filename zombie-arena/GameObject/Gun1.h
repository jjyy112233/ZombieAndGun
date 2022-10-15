#pragma once
#include "Gun.h"
class Gun1 :  public Gun
{
protected:
	bool isReload;
	float reloadDelay;

	float bulletCnt;
	float MaxBulletCnt;
	float initReloadDelay;
public:
	Gun1(ObjectPool<Bullet>* bulletPool);
	virtual ~Gun1();
	virtual void Init();
	virtual void Set();
	virtual void Reset();

	virtual bool Reload();
	virtual void Shoot(Vector2f playerPos);

	virtual void Update(float dt);
	virtual bool GetState();
};

