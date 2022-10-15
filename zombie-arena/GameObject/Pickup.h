#pragma once
#include "SpriteObj.h"

class Player;
class Pickup : public SpriteObj
{
public:
	enum class Types
	{
		None = -1,
		Ammo,
		Health,
		Count
	};
protected:
	Types type;
	int value;
	Player* player;
	float time = 10.f;
public:
	Pickup();
	~Pickup();

	void SetPlayer(Player* p);
	void SetType(Types t);
	void SetValue(int v);

	Types GetType();
	int GetValue();

	virtual void Update(float dt) override;
};

