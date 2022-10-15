#include "Zombie.h"
#include "Player.h"
#include "VertexArrayObj.h"
#include "../Framework/ResourceMgr.h"

const int Zombie::TotalTypes = 3;

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::SetBackground(VertexArrayObj* bk)
{
	background = bk;
}

void Zombie::Update(float dt)
{
	SpriteObj::Update(dt);

	float border = 50.f;

	FloatRect wallBound = background->GetGlobalBounds();
	Vector2f pos;
	pos.x = Utils::Clamp(position.x, wallBound.left + border, wallBound.left + wallBound.width - border);
	pos.y = Utils::Clamp(position.y, wallBound.top + border, wallBound.top + wallBound.height - border);
	if (pos != position)
	{
		SetPos(pos);
	}
	dir = Utils::Normalize(player->GetPos() - GetPos());
	Translate(dir * speed * dt);
	float distance = Utils::Distance(player->GetPos(), GetPos());
	if (distance < speed * dt)
	{
		SetPos(player->GetPos());
	}
	else
	{
		float degree = atan2(dir.y, dir.x) * (180.f / M_PI);
		sprite.setRotation(degree);
	}
	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		player->OnHitZombie(this);
	}
}

void Zombie::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Zombie::Init(Player* player)
{
	this->player = player;
	SpriteObj::Init();
	SetOrigin(Origins::MC);
}

void Zombie::Reset()
{
	SpriteObj::Reset();
	dir = { 1,0 };
	hp = maxHp;

	SetPos(position);
}

void Zombie::SetType(Types t)
{
	type = t;

	auto resMgr = RESOURCE_MGR;
	switch (t)
	{
	case Zombie::Types::Bloater:
		SetTexture(*resMgr->GetTexture("graphics/bloater.png"));
		speed = 40;
		maxHp = 100;
		break;
	case Zombie::Types::Chaser:
		SetTexture(*resMgr->GetTexture("graphics/chaser.png"));
		speed = 70;
		maxHp = 70;
		break;
	case Zombie::Types::Crawler:
		SetTexture(*resMgr->GetTexture("graphics/crawler.png"));
		speed = 20;
		maxHp = 50;
		break;
	}
}

Zombie::Types Zombie::GetType() const
{
	return type;
}

void Zombie::OnHitBullet(Bullet* bullet)
{
	hp -= 10;
	if (hp == 0)
	{
		SetActive(false);
	}
	// 체력 감소
	// 죽음
}
