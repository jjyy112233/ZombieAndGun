#include "ItemGenerator.h"
#include "../Framework/Utils.h"
#include "../Scenes/SceneMgr.h"
#include "../Scenes/SceneDev1.h"
#include "Player.h"
#include "Pickup.h"

ItemGenerator::ItemGenerator()
	: createIntervalMin(2.f), createIntervalMax(3.f),
	  createInterval(0.f), createTimer(0.f), radius(300.f), createMax(100)
{
}

ItemGenerator::~ItemGenerator()
{
}

void ItemGenerator::Reset()
{
	Object::Reset();
	itemList.clear();
	createTimer = 0.f;
	createInterval = Utils::RandomRange(createIntervalMin, createIntervalMax);
}

void ItemGenerator::Update(float dt)
{
	createTimer += dt;
	if (createTimer > createInterval)
	{
		int count = Utils::RandomRange(1, createMax + 1);
		for(int i = 0 ; i < count; i++)
		Generate();

		createTimer = 0.f;
		createInterval = Utils::RandomRange(createIntervalMin, createIntervalMax);
	}
}

void ItemGenerator::Generate()
{
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	Pickup::Types itemType = (Pickup::Types)Utils::RandomRange(0, (int)Pickup::Types::Count);


	Pickup* item = new Pickup();

	item->SetType(itemType);
	item->SetValue(10);
	item->SetPlayer((Player*)currScene->FindGameObj("Player"));
	item->Init();
	Vector2f center = ((Player*)currScene->FindGameObj("Player"))->GetPos();

	bool success = false;
	int count = 0;
	while (!success && count < 100)
	{
		success = true;
		Vector2f pos = center + Utils::RandAreaPoint() * radius;
		item->SetPos(pos);
		for (auto* i: itemList)
		{
			if (i->GetActive() &&  i->GetGlobalBounds().intersects(item->GetGlobalBounds()))
			{
				success = false;
				count++;
			}
		}
	}

	itemList.push_back(item);
	currScene->AddGameObject(item);
}
