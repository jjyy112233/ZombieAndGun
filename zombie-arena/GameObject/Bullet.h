#pragma once
#include "../GameObject/SpriteObj.h"
#include <list>

class Zombie;
class VertexArrayObj;
class Bullet : public SpriteObj
{
protected:
	VertexArrayObj* background;
	Vector2f dir;
	float speed;
	float range;
	int dmg;

	std::list<Zombie*>* zombies;
public:
	Bullet();
	virtual ~Bullet();

	void SetBackground(VertexArrayObj* bk);
	void Fire(const Vector2f& pos, const Vector2f& dir, int dmg, float speed, float range = 0);
	void SetZombieList(list<Zombie*>* list);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

};

