#include "stdafx.h"
#include "MapEditorController.h"

IMPLEMENT_SERIAL(MapEditorController,CObject,1)

MapEditorController::MapEditorController(void) : m_terrainFilePath("")
{
	m_pMapData = new MapData();
	m_myGame = new CMyGame();
	m_isGameInit=false;
}


MapEditorController::~MapEditorController(void)
{
}

void MapEditorController::NewMap(const CPoint& mapSize)
{
	if (m_pMapData != NULL)
	{
		delete m_pMapData;
		m_pMapData=NULL;
	}
	if (m_myGame!=NULL)
	{
		delete m_myGame;
		m_myGame=NULL;
	}
	m_pMapData = new MapData();
	m_myGame = new CMyGame();
	m_operationStack.Clear();
}

void MapEditorController::DataInit()
{
	MapData * mapData=MapEditorControllerSingleton::Instance().GetMapData();
	for (list<Scenery *>::iterator it=mapData->m_sceneryList.begin(); it!=mapData->m_sceneryList.end() ; it++)
	{
		CRect rect=(*it)->GetRect(*mapData);
		if ( typeid(**it)==typeid(Scenery) )
		{
			(*it)->m_lpd3ddev=MapEditorControllerSingleton::Instance().Getdevice();
			(*it)->LoadTexture();

		}else{
			MotionScenery * ms=dynamic_cast<MotionScenery *>( (*it) );		
			ms->LoadTexture(MapEditorControllerSingleton::Instance().Getdevice());
		}

	}
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
<<<<<<< HEAD
=======
}

void MapEditorController::Serialize(CArchive& ar)
{
	
	if (ar.IsStoring())
	{		
		ar<<CString(m_terrainFilePath.c_str())<<(int)m_editorMode;
	}else{
		Release();
		CString cs;
		int mode;
		ar>>cs>>mode;
		m_terrainFilePath=cs.GetString();
		m_editorMode=(EditorMode)mode;
		m_myGame=new CMyGame();
		
	}
	m_pMapData->Serialize(ar);
	
}

void MapEditorController::Release()
{
	if(m_myGame!=NULL)
		delete m_myGame;
	m_myGame=NULL;
>>>>>>> 2fa49e79e8b8ac815a1ec394e72454683f0f69c0
}