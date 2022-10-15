#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "../GameObject/Object.h"

using namespace sf;
using namespace std;

enum class Scenes
{
	Dev1,
	Dev2,
};

class UiMgr;
class Scene
{
protected:
	Scenes type;
	list<Object*> objList;
	//list<Object*> uiObjList;
	View worldView;
	View uiView;

	UiMgr* uiMgr;

	/*
	enum class Layer
	{
		Background, MapObject, Monsetr, Item, Player
	};
	map<Layer, list<Object*>> objList;
	// 이렇게 하고 순차적으로 랜더링 하면
	// 배경 그리고 맵 그리고 몬스터 그리고 몬스터위에 아이템 그리고 마지막에 플레이어 그릴듯

	map<Layer, map<int, list<Object*>>> objList; //이렇게 하고 순차적으로 랜더링 하면
	//랜더링 순서에다가 오브젝트마다 그리는 순서도 변경할수 있지 않을까 합미당
	*/
	
public:
	Scene(Scenes type);
	virtual ~Scene();

	virtual void Init() = 0; //생성
	virtual void Release();	 //해제

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Update(float dt);
	
	virtual void Draw(RenderWindow& window);

	Texture* GetTexture(const string path) const;

	View& GetWorldView() { return worldView; }
	View& GetUiView() { return uiView; }

	Vector2f ScreenToWorld(Vector2i screenPos);
	Vector2f ScreenToUiPosition(Vector2i screenPos);

	void AddGameObject(Object* obj);
	Object* FindGameObj(string name);
	UiMgr* GetUiMgr() { return uiMgr; }
};

