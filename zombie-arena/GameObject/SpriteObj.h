#pragma once
#include "Object.h"
#include "../Framework/Utils.h"

class SpriteObj :public Object
{
protected:
	Sprite sprite;

public:
	SpriteObj();
	virtual ~SpriteObj();

	virtual void Draw(RenderWindow& window) override;

	void SetTexture(Texture& tex);
	void SetOrigin(Origins origin);
	Vector2f GetSize()const;

	virtual void SetPos(const Vector2f& pos) override;
	void SetTextureRect(const IntRect& rect);
	void SetSize(Vector2f size);

	const IntRect& GetTextureRect()const;

	 FloatRect GetGlobalBounds() const;

};

