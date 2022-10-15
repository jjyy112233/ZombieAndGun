#include "SceneDev1.h"
#include "SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../Framework/SoundMgr.h"
#include "../GameObject/Player.h"
#include "../GameObject/VertexArrayObj.h"
#include "../GameObject/Zombie.h"
#include "../GameObject/Bullet.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/Pickup.h"
#include "../GameObject/Pickup.h"
#include "../GameObject/ItemGenerator.h"
#include "../Ui/UiDev1Mgr.h"

void OnCreateBullet(Bullet* bullet)
{
    SceneDev1* scene = (SceneDev1*)SCENE_MGR->GetScene(Scenes::Dev1);
    bullet->SetTexture(*RESOURCE_MGR->GetTexture("graphics/bullet.png"));
    bullet->SetZombieList(scene->GetZombieList());
    bullet->Init();
}

SceneDev1::SceneDev1() : Scene(Scenes::Dev1), background(nullptr)
{
}

SceneDev1::~SceneDev1()
{
	
}

void SceneDev1::Init()
{
	Release();

    CreateBackground(20, 10, 50.f, 50.f);
    Vector2i centerPos = FRAMEWORK->GetWindowSize() / 2;
    background->SetPos((Vector2f)centerPos);
    background->SetOrigin(Origins::MC);

	player = new Player();
    player->SetName("Player");
	player->SetTexture(*GetTexture("graphics/player.png"));
	player->SetOrigin(Origins::MC);
    player->SetBulletPool(&bullets);
    player->SetBackgound(background);
	objList.push_back(player);


    bullets.OnCreate = OnCreateBullet;
    bullets.Init();

    Texture* bulletTex = GetTexture("graphics/bullet.png");
    const auto& bulletList = bullets.GetUnuseList();
    for (auto bullet : bulletList)
    {
        bullet->SetTexture(*bulletTex);
        bullet->Reset();
        bullet->SetBackground(background);
    }
  
    ItemGenerator* itemGen = new ItemGenerator();
    itemGen->SetName("ItemGenerator");
    AddGameObject(itemGen);

    uiMgr = new UiDev1Mgr(this);
    uiMgr->Init();

    for (auto obj : objList)
    {
        obj->Init();
    }
}

void SceneDev1::Release()
{
    bullets.Release();

	Scene::Release();
	player = nullptr;
    background = nullptr;
    
    delete uiMgr;
}

void SceneDev1::Enter()
{
    for (auto obj : objList)
    {
        obj->Init();
    }

    FRAMEWORK->GetWindow().setMouseCursorVisible(false);
    FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);
    Vector2i size = FRAMEWORK->GetWindowSize();
	Vector2f centerPos(size.x * 0.5f, size.y * 0.5f);

    worldView.setSize(size.x, size.y);
    worldView.setCenter(0.f, 0.f);

    uiView.setSize(size.x, size.y);
    uiView.setCenter(centerPos);

	player->SetPos(centerPos);
    //CreateZombies(100);
    CreateZombies(50);
}

void SceneDev1::Exit()
{
    FRAMEWORK->GetWindow().setMouseCursorVisible(true);
    auto it = zombies.begin();
    while (it != zombies.end())
    {
        objList.remove(*it);
        delete* it;
        it = zombies.erase(it);
    }

    player->Reset();
    bullets.Reset();

    FindGameObj("ItemGenerator")->Reset();
    uiMgr->Reset();
}

void SceneDev1::Update(float dt)
{

	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev2);
	}
	Scene::Update(dt);


    Vector2f mousePos = InputMgr::GetMousePos();
    Vector2f mouseWroldPos = ScreenToWorld((Vector2i)mousePos);

    worldView.setCenter(player->GetPos());
    uiMgr->Update(dt);
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);
    const auto& bulletList = bullets.GetUseList();
    for (auto bullet : bulletList)
    {
        bullet->Draw(window);
    }
    uiMgr->Draw(window);
}

void SceneDev1::CreateBackground(int cols, int rows, float qWidht, float qHeight)
{

    if (background == nullptr)
    {
        background = new VertexArrayObj();
        background->SetTexture(GetTexture("graphics/background_sheet.png"));
        objList.push_back(background);
    }

    Vector2f startPos = background->GetPos();
    VertexArray& va = background->GetVA();
    va.setPrimitiveType(Quads);
    va.resize(cols * rows * 4);

    Vector2f currPos = startPos;

    Vector2f offsets[4] = { {0,0}, {qWidht,0}, {qWidht,qHeight}, {0,qHeight} };
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int quadIndex = i * cols + j;

            int texIndex = (i == 0 || i == rows - 1) || ((j == 0) || (j == cols - 1)) 
                ? 3 : (int)Utils::RandomRange(0, 3);

            for (int k = 0; k < 4; ++k)
            {
                va[quadIndex * 4 + k].position = currPos + offsets[k];
                va[quadIndex * 4 + k].texCoords = offsets[k] + Vector2f{ 0.f, texIndex * qHeight };
            }
            currPos.x += qWidht;
        }
        currPos.x = startPos.x;
        currPos.y += qHeight;
    }
}

void SceneDev1::CreateZombies(int count)
{
    auto winSize = FRAMEWORK->GetWindowSize();
    FloatRect rect(200.f, 200.f, winSize.x - 400.f, winSize.y - 400.f);
    float x, y;

    Vector2f point;

    for (int i = 0; i < count; ++i)
    {
        Zombie* zombie = new Zombie();
        zombie->SetType(
            (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes));

        zombie->Init(player);

        point.x = Utils::RandomRange(-1.0f, 1.0f);
        point.y = Utils::RandomRange(-1.0f, 1.0f);
        point = Utils::Normalize(point);
        point *= Utils::RandomRange(0.f, 500.f);
        zombie->SetPos(point);
        zombie->SetBackground(background);

        objList.push_back(zombie);
        zombies.push_back(zombie);
    }
}
