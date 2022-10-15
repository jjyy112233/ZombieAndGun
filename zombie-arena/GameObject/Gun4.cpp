#include "Gun4.h"

Gun4::Gun4(ObjectPool<Bullet>* bulletPool, const Vector2f& playerPos)
	:Gun(bulletPool), playerPos(playerPos), isReload(false), reloadDelay(2.f), bulletDelay(0.1f),
	bulletCnt(10), MaxBulletCnt(10), initBulletDelay(0.1f), isAuto(false), initReloadDelay(2.f)
{
}

Gun4::~Gun4()
{
}

void Gun4::Init()
{
	Reset();
}

void Gun4::Set()
{
}

void Gun4::Reset()
{
	bulletCnt = MaxBulletCnt;
	reloadDelay = initReloadDelay;
	bulletDelay = initBulletDelay;
	isReload = false;
	isAuto = false;
}

bool Gun4::Reload()
{
	if (!isReload)
	{
		PRINT("재장전 시작");
		isReload = true;
		reloadDelay = initReloadDelay;
		return true;
	}

	PRINT("이미 장전중");
	return false;
}

void Gun4::MouseUp()
{
	isAuto = false;
}

void Gun4::Shoot(Vector2f playerPos)
{
	isAuto = true;
}

void Gun4::Update(float dt)
{
	if (!isReload && bulletCnt <= 0)
	{
		PRINT("강제 재장전 시작");
		isReload = true;
	}
	if (isReload && reloadDelay > 0.f)	 //장전중일때 reloadDelay가 0이 될때까지 딜레이
	{
		reloadDelay -= dt;
	}
	else if (reloadDelay < 0.f) //딜레이 끝나면 재장전 끝! 
	{
		PRINT("재장전 완료");
		isReload = false;
		reloadDelay = initReloadDelay;
		bulletCnt = MaxBulletCnt;
	}

	if (isAuto && !isReload)
	{
		bulletDelay -= dt;
		if (bulletDelay < 0)
		{
			PRINT("빵!");
			bulletDelay = initBulletDelay;
			bulletCnt--;
			Gun::Shoot(playerPos);
		}
	}
}

bool Gun4::GetState()
{
    return true;
}
