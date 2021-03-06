#include "stdafx.h"
#include "RedoInsertScenery.h"
#include "MapData.h"


RedoInsertScenery::RedoInsertScenery(const Scenery& scenery):m_scenery(scenery)
{
}


RedoInsertScenery::~RedoInsertScenery(void)
{
}

Operation* RedoInsertScenery::Execute(MapData &mapData){
	mapData.m_sceneryList.push_back(new Scenery(m_scenery));
}
