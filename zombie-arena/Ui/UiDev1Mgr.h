#pragma once
#include "UiMgr.h"

class SpriteObj;
class Scene;
class TextObj;
class UiDev1Mgr : public UiMgr
{
protected:
	string formatScore; //"SCORE : %d"
	TextObj* txtScore;
	
	SpriteObj* cursor;
public:
	UiDev1Mgr(Scene* scnene);
	virtual void Init();
	virtual ~UiDev1Mgr();

	void SetScore(int score);
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

};

