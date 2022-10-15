#pragma once
#include "Object.h"
#include <list>

class Pickup;
class ItemGenerator : public Object
{
protected:
	float createIntervalMin;
	float createIntervalMax;
	float createInterval;
	float createTimer;

	int createMax;

	float radius;
	list<Pickup*> itemList;

public:
	ItemGenerator();
	~ItemGenerator();

	virtual void Reset();
	virtual void Update(float dt);
	virtual void Generate();
};

