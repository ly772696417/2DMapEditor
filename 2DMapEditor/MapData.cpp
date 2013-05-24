// MapData.cpp : 实现文件
//

#include "stdafx.h"
#include "2DMapEditor.h"
#include "MapData.h"

const size_t BlockSize=64;
// MapData
IMPLEMENT_SERIAL(MapData,CObject,1)
MapData::MapData(const string& terrainName,size_t xLength,size_t yLength):
	m_xlength(xLength),
	m_yLength(yLength)
{
	if ("" == terrainName)
	{
		m_terrainFilePath = "gres\\terrain\\terrain_1.BMP";
	}
	m_offest=0;
}

MapData::~MapData()
{
	Release();
}


// MapData 成员函数

Operation *MapData::ChangeTerrain(const string& terrainFilePath)
{
	UndoChangeTerrain *pTerrainOperation = new UndoChangeTerrain(m_terrainFilePath);
	
	m_terrainFilePath = terrainFilePath;
	
	return pTerrainOperation;
}

Operation *MapData::InsertScenery(const string& filePath,const CPoint& point)
{
	return NULL;
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
	Operation * oper=new NullOperation();
	list<Scenery*>::iterator it;
	for (it=m_sceneryList.begin();it!=m_sceneryList.end();it++)
	{
		if ( (*it)->IsSeleted() )
		{
			(*it)->positon_update(moveVec);
		}
	}
	return oper;
}

void MapData::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar<<CString(m_terrainFilePath.c_str())<<m_xlength<<m_yLength<<m_offest;
		ar<<m_sceneryList.size();
		list<Scenery *>::iterator it;
		for (it=m_sceneryList.begin();it!=m_sceneryList.end();++it)
		{
			if (typeid(**it)==typeid(Scenery))
				ar<<CString("Scenery");
			else
				ar<<CString("MotionScenery");
			(*it)->Serialize(ar);
		}
		
	}else{
		Release();
		CString cs;
		ar>>cs>>m_xlength>>m_yLength>>m_offest;
		m_terrainFilePath=cs.GetString();
		int nsize;
		ar>>nsize;
		Scenery * scenery;
		while(nsize--){
			CString cs;
			ar>>cs;
			if (cs=="Scenery")
				scenery=new Scenery();
			else
				scenery=new MotionScenery();
			scenery->Serialize(ar);
			m_sceneryList.push_back(scenery);
		}

	}
}

void MapData::Release()
{
	list<Scenery *>::iterator it;
	for (it=m_sceneryList.begin();it!=m_sceneryList.end();++it)
	{
		delete (*it);
	}
	m_sceneryList.clear();
}