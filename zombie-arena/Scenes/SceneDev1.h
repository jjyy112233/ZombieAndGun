#pragma once
#include "Scene.h"
#include "../Framework/ObjectPool.h"
#include <list>

class Player;
class VertexArrayObj;
class Zombie;
class Bullet;
class SpriteObj;
class Pickup;
class SceneDev1 : public Scene
{
protected:
	VertexArrayObj* background;
	Player* player;
	list<Zombie*> zombies;
	ObjectPool<Bullet> bullets;

	float itemDelay;
public:
	SceneDev1();
	virtual ~SceneDev1();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	void CreateBackground(int cols, int rows, float qWidht, float qHeight);
	void CreateZombies(int cnt);
	VertexArrayObj* GetBackground() { return background; }
	list<Zombie*>* GetZombieList() { return &zombies; }
};

