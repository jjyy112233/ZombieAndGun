#include "UiDev1Mgr.h"
#include "../GameObject/SpriteObj.h"   
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneDev1.h"
#include "../Framework/InputMgr.h"
#include "../GameObject/TextObj.h"


UiDev1Mgr::UiDev1Mgr(Scene* scene)
    :UiMgr(scene), formatScore("SCORE : ")
{
}

void UiDev1Mgr::Init()
{
    UiMgr::Init();

    txtScore = new TextObj();
    txtScore->SetFont(*RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf"));
    txtScore->GetSFMLText().setCharacterSize(75);
    txtScore->GetSFMLText().setPosition({ 50,50 });
    uiObjList.push_back(txtScore);

    cursor = new SpriteObj();
    cursor->SetTexture(*RESOURCE_MGR->GetTexture("graphics/crosshair.png"));
    cursor->SetOrigin(Origins::MC);
    
    uiObjList.push_back(cursor);
    SetScore(0);
}

UiDev1Mgr::~UiDev1Mgr()
{
}

void UiDev1Mgr::SetScore(int score)
{
    txtScore->SetText(formatScore + to_string(score));
}

void UiDev1Mgr::Release()
{
    UiMgr::Release();
}

void UiDev1Mgr::Reset()
{
    UiMgr::Reset();
}

void UiDev1Mgr::Update(float dt)
{
    UiMgr::Update(dt);
    Vector2f worldPos = parentScene->ScreenToUiPosition((Vector2i)InputMgr::GetMousePos());
    cursor->SetPos(worldPos);
}

void UiDev1Mgr::Draw(RenderWindow& window)
{
    window.setView(parentScene->GetUiView());
    UiMgr::Draw(window);
}
