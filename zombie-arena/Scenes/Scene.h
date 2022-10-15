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
	// �̷��� �ϰ� ���������� ������ �ϸ�
	// ��� �׸��� �� �׸��� ���� �׸��� �������� ������ �׸��� �������� �÷��̾� �׸���

	map<Layer, map<int, list<Object*>>> objList; //�̷��� �ϰ� ���������� ������ �ϸ�
	//������ �������ٰ� ������Ʈ���� �׸��� ������ �����Ҽ� ���� ������ �չ̴�
	*/
	
public:
	Scene(Scenes type);
	virtual ~Scene();

	virtual void Init() = 0; //����
	virtual void Release();	 //����

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

