#include "Gun2.h"

Gun2::Gun2(ObjectPool<Bullet>* bulletPool)
	:Gun(bulletPool),
	isAllReload(false), isReload(false), bulletDelat(1.f), initBulletDelay(1.f), bulletCnt(5), MaxBulletCnt(5)
{
}

Gun2::~Gun2()
{
}

void Gun2::Init()
{
	Reset();
}

void Gun2::Set()
{

}

void Gun2::Reset()
{
	bulletCnt = MaxBulletCnt;
	bulletDelat = initBulletDelay;
	isReload = false;
	isAllReload = false;
}

bool Gun2::Reload()
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

void Gun2::Shoot(Vector2f playerPos)
{
	bulletCnt--;
	isReload = false;
	bulletDelat = initBulletDelay;
	PRINT("샷 현재 탕창 수" + to_string(bulletCnt));
	Gun::Shoot(playerPos);
}

void Gun2::Update(float dt)
{
	if (!isReload && bulletCnt <= 0)
	{
		PRINT("강제 재장전");
		isReload = true;
	}
	if (isReload)	 //장전중일때 reloadDelay가 0이 될때까지 딜레이
	{
		bulletDelat -= dt;

		if (bulletDelat < 0.f)
		{
			bulletCnt++;
			PRINT("장전했다! 현재 탕창 수: " + to_string(bulletCnt));
			bulletDelat = initBulletDelay;
		}
		if (bulletCnt == MaxBulletCnt)
		{
			PRINT("재장전 끝 총알 MAX");
			bulletDelat = initBulletDelay;
			isReload = false;
		}
	}
}

bool Gun2::GetState()
{
	return bulletCnt > 0;
}