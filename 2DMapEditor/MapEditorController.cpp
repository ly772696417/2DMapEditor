#include "stdafx.h"
#include "MapEditorController.h"


MapEditorController::MapEditorController(void) : m_terrainFilePath("")
{
	m_pMapData = new MapData();
	m_myGame = new CMyGame();
}


MapEditorController::~MapEditorController(void)
{
}

void MapEditorController::ChangeTerrain(const string& terrainFilePath)
{
	m_terrainFilePath = terrainFilePath;
	Operation *pOperation = m_pMapData->ChangeTerrain(m_terrainFilePath);
	m_operationStack.Ondo(pOperation);
	m_myGame->m_isTerrainChanged=true;
	

}

void MapEditorController::Undo()
{
	m_operationStack.Undo(*m_pMapData);
}


void MapEditorController::Redo()
{
	m_operationStack.Redo(*m_pMapData);
}

void MapEditorController::NewMap(const CPoint& mapSize)
{
	if (m_pMapData != NULL)
	{
		delete m_pMapData;
	}
	m_pMapData = new MapData(m_terrainFilePath,mapSize.x,mapSize.y);
	m_operationStack.Clear();
}

//Operations
void MapEditorController::InsertScenery(const CPoint& point)
{
	//Operation *pOperation = m_pMapData-
}

void MapEditorController::drawModel(CPoint cp)
{
	Scenery * scenery;
	string ext=GetExt(m_editfilePath);
	if (ext==".mo")
	{
		scenery=new MotionScenery(m_editfilePath,cp+m_pMapData->GetOffest(),Getdevice());
	}else{
		scenery=new Scenery(m_editfilePath.c_str(),cp+m_pMapData->GetOffest(),Getdevice());
	}
	m_pMapData->m_sceneryList.push_back(scenery);
};

LPDIRECT3DDEVICE9 MapEditorController::Getdevice()
{
	LPDIRECT3DDEVICE9 device=NULL;
	device=m_myGame->myDirectx.d3ddev;
	return device;
}

void MapEditorController::CheackIsSel(CRect rect)
{
	for (list<Scenery *>::iterator it=m_pMapData->m_sceneryList.begin(); it!=m_pMapData->m_sceneryList.end() ; it++)
	{
		if ( RectIntersect(rect,(*it)->GetRect(*m_pMapData)) )
		{
			(*it)->Selete(true);
		}else
			(*it)->Selete(false);
	}
	
}

bool MapEditorController::CheackIsMove(CPoint pt)
{
	list<Scenery *> scenery=m_pMapData->m_sceneryList;
	list<Scenery*>::iterator it;
	for (it=scenery.begin();it!=scenery.end();it++)
	{
		CRect rect=(*it)->GetRect(*m_pMapData);
		if (rect.PtInRect(pt) && (*it)->IsSeleted()) return true;
			
	}
	return false;
}

void MapEditorController::MoveMode(CPoint moveVec)
{
	m_pMapData->MoveMode(moveVec,true);
}