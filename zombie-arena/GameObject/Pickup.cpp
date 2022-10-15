#include "Pickup.h"
#include "Player.h"
#include "../Framework/ResourceMgr.h"

Pickup::Pickup() : type(Types::None), value(0), player(nullptr), time(3.f)
{
}

Pickup::~Pickup()
{
}

void Pickup::SetPlayer(Player* p)
{
	player = p;
}

void Pickup::SetType(Types t)
{
	type = t;
	time = 3.f;
	switch (type)
	{
	case Pickup::Types::None:
		break;
	case Pickup::Types::Ammo:
		SetTexture(*RESOURCE_MGR->GetTexture("graphics/ammo_icon.png"));
		SetOrigin(Origins::MC);
		break;
	case Pickup::Types::Health:
		SetTexture(*RESOURCE_MGR->GetTexture("graphics/health_pickup.png"));
		SetOrigin(Origins::MC);
		break;
	default:
		break;
	}
}

void Pickup::SetValue(int v)
{
	value = v;
}

Pickup::Types Pickup::GetType()
{
	return type;
}

int Pickup::GetValue()
{
	return value;
}

void Pickup::Update(float dt)
{
	time -= dt;
	if (time < 0.f)
	{
		SetActive(false);
		time = 3.f;
	}
	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		SetActive(false);
		player->OnPickupItem(this);
	}


	SpriteObj::Update(dt);
}
