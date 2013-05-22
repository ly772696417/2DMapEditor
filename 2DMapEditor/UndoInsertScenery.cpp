#include "stdafx.h"
#include "UndoInsertScenery.h"
#include "RedoInsertScenery.h"
#include "MapData.h"

UndoInsertScenery::UndoInsertScenery(int where):m_where(where)
{
}


UndoInsertScenery::~UndoInsertScenery(void)
{
}

Operation* UndoInsertScenery::Execute(MapData &mapData)
{
	list<Scenery *>::iterator it;
	for (it = mapData.m_sceneryList.begin();it!=mapData.m_sceneryList.end();it++)
	{
		if ((*it)->GetGUID() == m_where)
		{
			Operation *pAns = new RedoInsertScenery(**it);
			delete *it;
			mapData.m_sceneryList.erase(it);
			return pAns;
		}
	}

	return new NullOperation;
}