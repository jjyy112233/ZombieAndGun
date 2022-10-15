#include "Gun.h"
#include "Bullet.h"
#include "../Framework/InputMgr.h"
#include "../Scenes/SceneMgr.h"

Gun::Gun(ObjectPool<Bullet>* bulletPool)
	:bulletPool(bulletPool)
{
}

void Gun::Shoot(Vector2f playerPos)
{
	Scene* scene = SCENE_MGR->GetCurrentScene();

	Vector2i mousePos = (Vector2i)InputMgr::GetMousePos();
	Vector2f lookDir = Utils::Normalize(scene->ScreenToWorld(mousePos) - playerPos);

	Vector2f startPos = playerPos + lookDir * 23.f;
	Vector2f bulletDir = Utils::Normalize(scene->ScreenToWorld(mousePos) - startPos);
	Bullet* bullet = bulletPool->Get();
	bullet->Fire(startPos, bulletDir, 100, 1000, 1000);
}

void Gun::MouseUp()
{
}
