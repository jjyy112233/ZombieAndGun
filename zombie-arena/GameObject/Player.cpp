#include "Player.h"
#include "../Framework//Framework.h"
#include "../Framework/InputMgr.h"
#include "Bullet.h"
#include <iostream>
#include "Gun1.h"
#include "Gun2.h"
#include "Gun3.h"
#include "Gun4.h"
#include "Pickup.h"
#include "VertexArrayObj.h"
#include <algorithm>
#include "Zombie.h"
#include "../Scenes/SceneMgr.h"
#include "../Ui/UiDev1Mgr.h"


Player::Player()
	: speed(200), bulletPool(nullptr), velocity(Vector2f{ 0,0 }), accelation(200.f), deaccelation(200.f), gunIdx(0)
{
}

Player::~Player()
{
}

void Player::SetBulletPool(ObjectPool<Bullet>* bulletPool)
{
	this->bulletPool = bulletPool;
}
void Player::SetBackgound(VertexArrayObj* bk)
{
	background = bk;
}
void Player::Init()
{
	SpriteObj::Init();
	gunIdx = 2;
	SetOrigin(Origins::MC);
	guns.push_back(new Gun1(bulletPool));
	guns.push_back(new Gun2(bulletPool));
	guns.push_back(new Gun3(bulletPool, position));
	guns.push_back(new Gun4(bulletPool, position));

	scene = SCENE_MGR->GetCurrentScene();
	uiMgr = scene->GetUiMgr();
}

void Player::Reset()
{
	SpriteObj::Reset();
	direction = { 1.0f, 0.0f };
	velocity = { 0,0 };
}

void Player::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::B))
	{
		((UiDev1Mgr*)uiMgr)->SetScore(Utils::RandomRange(0, 100));
	}
	SpriteObj::Update(dt);

	Scene* scene = SCENE_MGR->GetCurrentScene();

	Vector2i mousePos = (Vector2i)InputMgr::GetMousePos();
	Vector2f look = Utils::Normalize(scene->ScreenToWorld(mousePos) - GetPos());

	float degree = Utils::Angle(look);
	sprite.setRotation(degree);

	direction.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	direction.y = InputMgr::GetAxisRaw(Axis::Vertical);

	// 가속
	velocity += direction * accelation * dt;
	if (Utils::Magnitude(velocity) > speed)
	{
		velocity = Utils::Normalize(velocity) * speed;
	}

	if (direction.x == 0.f)
	{
		if (velocity.x > 0.f)
		{
			velocity.x -= deaccelation * dt;
			if (velocity.x < 0.f)
				velocity.x = 0.f;
		}
		if (velocity.x < 0.f)
		{
			velocity.x += deaccelation * dt;
			if (velocity.x > 0.f)
				velocity.x = 0.f;
		}
	}

	if (direction.y == 0.f)
	{
		if (velocity.y > 0.f)
		{
			velocity.y -= deaccelation * dt;
			if (velocity.y < 0.f)
				velocity.y = 0.f;
		}
		if (velocity.y < 0.f)
		{
			velocity.y += deaccelation * dt;
			if (velocity.y > 0.f)
				velocity.y = 0.f;
		}
	}

	Translate(velocity * dt);
	
	//벽 충돌
	FloatRect wallBound = background->GetGlobalBounds();

	Vector2f pos;
	float border = 50.f;
	pos.x = Utils::Clamp(position.x, wallBound.left + border, wallBound.left + wallBound.width - border);
	pos.y = Utils::Clamp(position.y, wallBound.top + border, wallBound.top + wallBound.height - border);

	if (pos != position)
	{
		SetPos(pos);
		velocity = Vector2f{ 0.f, 0.f };
	}

	if (InputMgr::GetKeyDown(Keyboard::B))
	{
		gunIdx = (gunIdx + 1) % guns.size(); 
		//총 바꿀때 이전 총 리로드 시간 초기화 추가하기. 재장전중에 스왑하면 재장전 다시 돌아갈때 재장전 다시 시작하게
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::R))
	{
		guns[gunIdx]->Reload();
	}
	if (bulletPool!= nullptr && InputMgr::GetMouseButtonDown(Mouse::Button::Left))
	{
		if (guns[gunIdx]->GetState())
		{
			guns[gunIdx]->Shoot(GetPos());
		}
		else
		{
			PRINT("못쏴!");
		}
	}
	if (InputMgr::GetMouseButtonUp(Mouse::Button::Left))
	{
		guns[gunIdx]->MouseUp();
	}
	guns[gunIdx]->Update(dt);
	bulletPool->Update(dt);
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Player::OnPickupItem(Pickup* item)
{
	switch (item->GetType())
	{

	case Pickup::Types::Ammo:
		speed += 1000.f;
		//ammo += item->GetValue();
		break;
	case Pickup::Types::Health:
		speed += 1000.f;
		//health += item->GetValue();
		break;

	default:
		break;
	}

	item->SetActive(false);
}

void Player::OnHitZombie(Zombie* zombie)
{
	
}
