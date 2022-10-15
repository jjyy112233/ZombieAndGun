#include "Market.h"
#include "../Framework/Framework.h"
#include "../GameObject/SpriteObj.h";
#include "../GameObject/TextObj.h";
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"
#include "../Scenes/SceneMgr.h"
#include "../Scenes/SceneDev1.h"

Market::Market()
	:isShopping(false), maxSelling(4)
{
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/100sizeImage.png"));
	background->SetOrigin(Origins::MR);
	ActiveButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/100sizeImage.png"));
}

Market::~Market()
{
}

void Market::Init()
{

	Reset();
}

void Market::Release()
{
}

void Market::Reset()
{
	isShopping = false;
}

void Market::SetPos(const Vector2f& pos)
{
}

void Market::Update(float dt)
{
}

void Market::Draw(RenderWindow& window)
{
}
