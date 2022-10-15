#include "Gun1.h"

Gun1::Gun1(ObjectPool<Bullet>* bulletPool)
	:Gun(bulletPool),
	isReload(false), reloadDelay(3.f), initReloadDelay(3.f), bulletCnt(5), MaxBulletCnt(5)
{
}

Gun1::~Gun1()
{
}

void Gun1::Init()
{
	Reset();
}

void Gun1::Set()
{

}

void Gun1::Reset()
{
	bulletCnt = MaxBulletCnt;
	reloadDelay = initReloadDelay;
	isReload = false;
}

bool Gun1::Reload()
{
	if (!isReload)
	{
		isReload = true;
		return true;
	}

	return false;
}

void Gun1::Shoot(Vector2f playerPos)
{
	bulletCnt--;
	Gun::Shoot(playerPos);
}

void Gun1::Update(float dt)
{
	if (!isReload && bulletCnt <= 0)
	{
		isReload = true;
	}
	if (isReload && reloadDelay > 0.f)	 //�������϶� reloadDelay�� 0�� �ɶ����� ������
	{
		reloadDelay -= dt;
	}
	else if (reloadDelay < 0.f) //������ ������ ������ ��! 
	{
		isReload = false;
		reloadDelay = initReloadDelay;
		bulletCnt = MaxBulletCnt;
	}
}

bool Gun1::GetState()
{
	return !isReload;
}
