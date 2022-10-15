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
		PRINT("������ ����");
		isReload = true;
		return true;
	}

	PRINT("�̹� ������");
	return false;
}

void Gun2::Shoot(Vector2f playerPos)
{
	bulletCnt--;
	isReload = false;
	bulletDelat = initBulletDelay;
	PRINT("�� ���� ��â ��" + to_string(bulletCnt));
	Gun::Shoot(playerPos);
}

void Gun2::Update(float dt)
{
	if (!isReload && bulletCnt <= 0)
	{
		PRINT("���� ������");
		isReload = true;
	}
	if (isReload)	 //�������϶� reloadDelay�� 0�� �ɶ����� ������
	{
		bulletDelat -= dt;

		if (bulletDelat < 0.f)
		{
			bulletCnt++;
			PRINT("�����ߴ�! ���� ��â ��: " + to_string(bulletCnt));
			bulletDelat = initBulletDelay;
		}
		if (bulletCnt == MaxBulletCnt)
		{
			PRINT("������ �� �Ѿ� MAX");
			bulletDelat = initBulletDelay;
			isReload = false;
		}
	}
}

bool Gun2::GetState()
{
	return bulletCnt > 0;
}