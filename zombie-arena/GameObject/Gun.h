#pragma once
#include "Object.h"
#include "../Framework/ObjectPool.h"

class Bullet;
class Gun : public Object
{
	ObjectPool<Bullet>* bulletPool;

public:
	Gun(ObjectPool<Bullet>* bulletPool);
	virtual ~Gun() {};
	virtual void Init() = 0;
	virtual void Set() = 0;
	virtual void Reset() = 0;
	virtual bool Reload() = 0;
	virtual void Shoot(Vector2f playerPos);
	virtual void MouseUp();
	virtual void Update(float dt) = 0;
	virtual bool GetState() = 0;
};

