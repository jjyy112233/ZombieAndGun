#pragma once
#include "../GameObject/Object.h"

class SpriteObj;
class TextObj;
struct Present
{
	string name;
	SpriteObj* itemImage;
	TextObj* Price;
};

class Market : public Object
{
private:
	const int maxSelling;
	SpriteObj* background;
	SpriteObj* ActiveButton;

	vector<Present> itemList;

	bool isShopping;
public:
	Market();
	~Market();
	virtual void Init();

	virtual void Release();
	virtual void Reset();

	virtual void SetPos(const Vector2f& pos);

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};


