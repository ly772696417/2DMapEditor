#include "stdafx.h"
#include "UndoDeleteSeletion.h"
#include "RedoDeleteSelection.h"
#include "MapData.h"


UndoDeleteSeletion::UndoDeleteSeletion(void)
{
}


UndoDeleteSeletion::~UndoDeleteSeletion(void)
{
}

Operation* UndoDeleteSeletion::Execute(MapData &mapData)
{
	list<Scenery*>::iterator it;
	for (it = mapData.m_sceneryList.begin();it != mapData.m_sceneryList.end();it++)
	{
		(*it)->Selete(false);
	}
	for(size_t i = 0;i<m_vDeleted.size();i++){
		mapData.m_sceneryList.push_back(new Scenery(m_vDeleted[i]));
	}

	Operation *p = new RedoDeleteSelection();

	return p;
}

void UndoDeleteSeletion::AppendScenery(const Scenery& scenery){
	m_vDeleted.push_back(scenery);
}