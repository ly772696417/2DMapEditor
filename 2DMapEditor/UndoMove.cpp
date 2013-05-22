#include "stdafx.h"
#include "UndoMove.h"
#include "Scenery.h"
#include "MapData.h"

UndoMove::UndoMove(const CPoint& moveV):m_moveV(-moveV)
{
}

UndoMove::UndoMove(const UndoMove& o):m_moveV(-o.m_moveV),m_vGUIDs(o.m_vGUIDs){

}

UndoMove::~UndoMove(void)
{
}

Operation *UndoMove::Execute(MapData &mapData){
	for (int i = 0; i < m_vGUIDs.size(); i++)
	{
		long guid = m_vGUIDs[i];
		list<Scenery *>::iterator it;
		for (it = mapData.m_sceneryList.begin();it != mapData.m_sceneryList.end();it++)
		{
			if ((*it)->GetGUID() == guid)
			{
				(*it)->Move(m_moveV);
			}
		}
	}

	return new UndoMove(*this);
}
