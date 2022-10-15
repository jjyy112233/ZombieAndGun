#pragma once
#include "Gun.h"

class Gun4 : public Gun
{
private:
	bool isReload;
	float initReloadDelay;
	float reloadDelay;

	int bulletCnt;
	int MaxBulletCnt;
	float bulletDelay;
	float initBulletDelay;
	
	bool isAuto;
	const Vector2f& playerPos;
public:
	Gun4(ObjectPool<Bullet>* bulletPool, const Vector2f& playerPos);
	virtual ~Gun4();

	virtual void Init() override;
	virtual void Set() override;
	virtual void Reset() override;
	virtual bool Reload() override;
	virtual void MouseUp() override;

	virtual void Shoot(Vector2f playerPos);

	virtual void Update(float dt) override;
	virtual bool GetState() override;
};

