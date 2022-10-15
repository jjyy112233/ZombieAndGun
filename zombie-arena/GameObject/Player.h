#pragma once
#include "SpriteObj.h"
#include "../Framework/ObjectPool.h"
#include "Gun.h"

class Bullet;
class Pickup;
class VertexArrayObj;
class Zombie;
class Scene;
class UiMgr;

class Player : public SpriteObj
{
protected:
	Vector2f look;
	Vector2f direction;	// 이동 방향, 단위 벡터
	Vector2f prevDirection;	// 이동 방향, 단위 벡터
	float speed;
	Vector2f velocity;
	float accelation;
	float deaccelation;
	ObjectPool<Bullet>* bulletPool;
	VertexArrayObj* background;

	vector<Gun*> guns;
	int gunIdx;

	Scene* scene;
	UiMgr* uiMgr;

public:
	Player();	
	virtual ~Player();
	
	void SetBulletPool(ObjectPool<Bullet>* bulletPool);
	void SetBackgound(VertexArrayObj* bk);
	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void OnPickupItem(Pickup* item);
	void OnHitZombie(Zombie* zombie);

};

