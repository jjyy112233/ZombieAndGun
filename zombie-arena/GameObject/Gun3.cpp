#include "Gun3.h"

Gun3::Gun3(ObjectPool<Bullet>* bulletPool, const Vector2f& playerPos)
    :Gun(bulletPool), isFire(false), bulletCount(10), firecount(3), initFireCnt(3),playerPos(playerPos),
    bulletDelay(0.1f), FireDelay(0.4f), delay(0.f), reloadDelay(1.f), initReloadDelay(1.f), maxBulletCount(10)
{

}

Gun3::~Gun3()
{
}

void Gun3::Init()
{
    Reset();

}

void Gun3::Set()
{
}

void Gun3::Reset()
{
    firecount = initFireCnt;
    isFire = false;
    bulletCount = 30;
    FireDelay = 0.4f;
    bulletDelay = 0.1f;
    delay = 0.f;
}

bool Gun3::Reload()
{
    if (!isReload)
    {
        PRINT("재장전 시작");
        isReload = true;
        return true;
    }

    PRINT("이미 장전중");
    return false;
}

void Gun3::Shoot(Vector2f playerPos)
{
    isFire = true;
    delay = 0.f;
}

void Gun3::Update(float dt)
{
    if (!isReload && bulletCount <= 0)
    {
        PRINT("강제 재장전 시작");
        isReload = true;
        firecount = initFireCnt;
        delay = FireDelay;
        isFire = false;
    }
    if (isReload && reloadDelay > 0.f)	 //장전중일때 reloadDelay가 0이 될때까지 딜레이
    {
        reloadDelay -= dt;
    }
    else if (reloadDelay < 0.f) //딜레이 끝나면 재장전 끝! 
    {
        PRINT("재장전 완료");
        isReload = false;
        delay = 0.f;
        firecount = initFireCnt;
        isFire = false;
        reloadDelay = initReloadDelay;
        bulletCount = maxBulletCount;
    }

    if (!isReload && isFire)
    {
        delay -= dt;
        if (delay < 0.f)
        {
            if (firecount == 0 || bulletCount == 0)
            {
                PRINT("이제 쏴도 됩니다");
                firecount = initFireCnt;
                isFire = false;
            }
            else if (firecount > 0 && bulletCount > 0)
            {
                bulletCount--;
                firecount--;
                Gun::Shoot(playerPos);
                PRINT("빵!");

                delay = (firecount == 0) ? FireDelay : bulletDelay;
                if(firecount == 0)
                    PRINT("바로 쏘지 못합니다");
            }
        }
    }
}

bool Gun3::GetState()
{
    return !isReload && !isFire;
}
