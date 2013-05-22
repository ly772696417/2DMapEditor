// MapData.cpp : 实现文件
//

#include "stdafx.h"
#include "2DMapEditor.h"
#include "MapData.h"

#include "UndoChangeTerrain.h"
#include "UndoDeleteSeletion.h"
#include "UndoInsertScenery.h"
#include "UndoMove.h"
#include "RedoDeleteSelection.h"
#include "RedoInsertScenery.h"
#include "MotionScenery.h"

const size_t BlockSize=64;
// MapData

MapData::MapData(const string& terrainName,size_t xLength,size_t yLength):
	m_xlength(xLength),
	m_yLength(yLength),
	m_totMoveV(0,0)
{
	if ("" == terrainName)
	{
		m_terrainFilePath = "gres\\terrain\\terrain_1.BMP";
	}
	m_offest=0;
}

MapData::~MapData()
{
}


// MapData 成员函数

Operation *MapData::ChangeTerrain(const string& terrainFilePath)
{
	UndoChangeTerrain *pTerrainOperation = new UndoChangeTerrain(m_terrainFilePath);
	
	m_terrainFilePath = terrainFilePath;
	
	return pTerrainOperation;
}

Operation *MapData::InsertScenery(const string& filePath,const CPoint& point,LPDIRECT3DDEVICE9 d3ddev)
{
	Scenery *p;
	string ext = GetExt(filePath);
	if (ext == ".bmp" || ext == ".BMP")
	{
		p = new Scenery(filePath.c_str(),point,d3ddev);
	}
	else
	{
		p = new MotionScenery(filePath,point,d3ddev);
	}

	Operation *pOperation = new UndoInsertScenery(p->GetGUID());
	list<Scenery*>::iterator it;
	for (it = m_sceneryList.begin();it!= m_sceneryList.end();it++)
	{
		if ((*it)->GetPos().y > p->GetPos().y)
		{
			m_sceneryList.insert(it,1,p);
			return pOperation;
		}
		
	}
	m_sceneryList.push_back(p);
	return pOperation;
	
}

Operation *MapData::DeleteSelection()
{
	UndoDeleteSeletion *pUndoDeleteSelection = new UndoDeleteSeletion();
	list<Scenery *>::iterator it = m_sceneryList.begin();
	while (it != m_sceneryList.end())
	{
		list<Scenery *>::iterator nt = ++it;
		it--;
		if ((*it)->IsSeleted())
		{
			pUndoDeleteSelection->AppendScenery(**it);
			delete *it;
			m_sceneryList.erase(it);
		}
		it = nt;
	}
	return pUndoDeleteSelection;

}

void MapData::SetOffest(CPoint offest,const CRect & rect)
{
	m_offest=offest;
	if(m_offest.x<0) m_offest.x=0;
	if(m_offest.y<0) m_offest.y=0;
	if(m_offest.y>m_yLength*BlockSize-rect.Height()) m_offest.y=m_yLength*BlockSize-rect.Height();
	if(m_offest.x>m_xlength*BlockSize-rect.Width()) m_offest.x=m_xlength*BlockSize-rect.Width();
}

Operation * MapData::MoveMode(CPoint moveVec,bool isLastMove)
{
	UndoMove * oper=NULL;
	m_totMoveV += moveVec;
	if (isLastMove)
	{
		oper = new UndoMove(m_totMoveV);
		m_totMoveV = CPoint(0,0);
	}
	

	list<Scenery*>::iterator it;
	for (it=m_sceneryList.begin();it!=m_sceneryList.end();it++)
	{
		if ( (*it)->IsSeleted() )
		{
			(*it)->positon_update(moveVec);
			if (isLastMove)
			{
				oper->AppendGUID((*it)->GetGUID());
			}
			
		}
	}
	return oper;
}

CPoint MapData::MapPoint2ScreenPoint( const CPoint& pt ) const
{
	return pt - m_offest;
}

CPoint MapData::ScreenPoint2MapPoint( const CPoint& pt ) const
{
	return pt + m_offest;
}