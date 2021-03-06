#pragma once
#include "operation.h"

#include "Scenery.h"

class RedoInsertScenery :
	public Operation
{
public:
	RedoInsertScenery(const Scenery& scenery);
	~RedoInsertScenery(void);

	virtual Operation* Execute(MapData &mapData);

private:
	Scenery m_scenery;
};

