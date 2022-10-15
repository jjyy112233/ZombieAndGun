#pragma once
#include "SpriteObj.h"

class Player;
class Bullet;
class VertexArrayObj;

class Zombie : public SpriteObj
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};
	static const int TotalTypes;

protected:
	Types type;

	Vector2f dir;
	float speed;

	int maxHp;
	int hp;

	Player* player;
	VertexArrayObj* background;
public:
	Zombie();
	~Zombie();

	void SetBackground(VertexArrayObj* bk);

	void Init(Player* player);
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetType(Types t);
	Types GetType() const;

	void OnHitBullet(Bullet* bullet);
};

