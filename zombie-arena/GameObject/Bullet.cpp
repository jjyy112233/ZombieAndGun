#include "Bullet.h"
#include "../Framework/Utils.h"
#include "VertexArrayObj.h"
#include "Zombie.h"
#include "../Scenes/SceneMgr.h"
#include "../Scenes/SceneDev1.h"

Bullet::Bullet()
	:speed(0.f), range(0.f), dir()
{
}

Bullet::~Bullet()
{
}
void Bullet::SetBackground(VertexArrayObj* bk)
{
    background = bk;
}
//distance 가 0이면 무한으로 날라감
void Bullet::Fire(const Vector2f& pos, const Vector2f& dir, int dmg, float speed, float range)
{
	SetPos(pos);
	sprite.setRotation(Utils::Angle(dir));
	this->dir = dir;
	this->speed = speed;
	this->range = range;
    this->dmg = dmg;
}

void Bullet::SetZombieList(list<Zombie*>* list)
{
	zombies = list;
}

void Bullet::Init()
{
	SetOrigin(Origins::MC);
	SpriteObj::Init();
}

void Bullet::Release()
{
	SpriteObj::Release();
}

void Bullet::Reset()
{
	dir = Vector2f{ 1,0 };
	speed = 0.f;
	range = 0.f;
	sprite.setRotation(0.f);
	SetPos(Vector2f{ 0,0 });
	SpriteObj::Reset();
}
void Bullet::Update(float dt)
{
    SpriteObj::Update(dt);

    float border = 50.f;

    FloatRect wallBound = background->GetGlobalBounds();
    Vector2f pos;
    pos.x = Utils::Clamp(position.x, wallBound.left + border, wallBound.left + wallBound.width - border);
    pos.y = Utils::Clamp(position.y, wallBound.top + border, wallBound.top + wallBound.height - border);

    if (pos != position)
    {
        SetActive(false);
    }


    Translate(dir * speed * dt);
    range -= speed * dt;

    if (range < 0)
    {
        SetActive(false);
    }
    else
    {
        for (Zombie* zombie : *zombies)
        {
            if (zombie->GetActive())
            {
                if (GetGlobalBounds().intersects(zombie->GetGlobalBounds()))
                {
                    zombie->OnHitBullet(this);
                    SetActive(false);
                    break;
                }
            }
        }
    }
}

void Bullet::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}
