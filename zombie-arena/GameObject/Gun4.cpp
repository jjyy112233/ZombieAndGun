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
		PRINT("������ ����");
		isReload = true;
		reloadDelay = initReloadDelay;
		return true;
	}

	PRINT("�̹� ������");
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
		PRINT("���� ������ ����");
		isReload = true;
	}
	if (isReload && reloadDelay > 0.f)	 //�������϶� reloadDelay�� 0�� �ɶ����� ������
	{
		reloadDelay -= dt;
	}
	else if (reloadDelay < 0.f) //������ ������ ������ ��! 
	{
		PRINT("������ �Ϸ�");
		isReload = false;
		reloadDelay = initReloadDelay;
		bulletCnt = MaxBulletCnt;
	}

	if (isAuto && !isReload)
	{
		bulletDelay -= dt;
		if (bulletDelay < 0)
		{
			PRINT("��!");
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
