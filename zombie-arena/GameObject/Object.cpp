#include "Object.h"

int Object::objCount = 0;

Object::Object() : isDevMode(false)
{
    id = ++objCount;
}

Object::~Object()
{
    Release();
}

int Object::GetObjId() const
{
    return id;
}

void Object::SetActive(bool active)
{
    enabled = active;
}

bool Object::GetActive() const
{
    return enabled;
}

void Object::Init()
{
    hitbox.setFillColor(Color::Red);
    Reset();
}

void Object::Release()
{
}

void Object::Reset()
{
    enabled = true;
}

void Object::SetPos(const Vector2f& pos)
{
    position = pos;
    hitbox.setPosition(position);
}

const Vector2f& Object::GetPos() const
{
    return position;
}

void Object::Update(float dt)
{
}

void Object::Draw(RenderWindow& window)
{
    if (isDevMode)
    {
        window.draw(hitbox);
    }
}

void Object::SetHitBox(const FloatRect rect)
{
    Vector2f hitboxPos = GetPos();
    hitbox.setPosition(hitboxPos);
    hitbox.setSize({ rect.width, rect.height });

}

void Object::Translate(const Vector2f& delta)
{
    SetPos(position + delta);
}

