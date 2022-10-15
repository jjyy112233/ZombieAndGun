#pragma once
#include "Gun.h"
class Gun3 : public Gun
{
protected:
    bool isReload;
    bool isFire;

    int bulletCount;
    int maxBulletCount;

    int firecount;
    int initFireCnt;

    float reloadDelay;
    float initReloadDelay;

    float delay;
    float bulletDelay;
    float FireDelay;
    const Vector2f& playerPos;

public:
    Gun3(ObjectPool<Bullet>* bulletPool, const Vector2f& playerPos);
    virtual ~Gun3();
    virtual void Init() override;
    virtual void Set() override;
    virtual void Reset() override;
    virtual bool Reload() override;
    virtual void Shoot(Vector2f playerPos) override;
    virtual void Update(float dt) override;
    virtual bool GetState() override;
};

