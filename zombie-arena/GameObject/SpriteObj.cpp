#include "SpriteObj.h"

SpriteObj::SpriteObj()
{
}

SpriteObj::~SpriteObj()
{
}


void SpriteObj::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void SpriteObj::SetTexture(Texture& tex)
{
	sprite.setTexture(tex);
}


void SpriteObj::SetOrigin(Origins origin)
{
	Utils::SetOrigin(sprite, origin);
}

Vector2f SpriteObj::GetSize() const
{
	FloatRect rect = sprite.getLocalBounds();

	return Vector2f(rect.width, rect.height);
}

void SpriteObj::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	sprite.setPosition(position);
}

void SpriteObj::SetTextureRect(const IntRect& rect)
{
	sprite.setTextureRect(rect);
}
void SpriteObj::SetSize(Vector2f size)
{
	auto localSize = sprite.getLocalBounds();
	sprite.setScale({ size.x / localSize.width, size.y / localSize.height });
}
const IntRect& SpriteObj::GetTextureRect() const
{
	return sprite.getTextureRect();
}

FloatRect SpriteObj::GetGlobalBounds() const
{
	auto t = sprite.getGlobalBounds();
	return sprite.getGlobalBounds();
}

