// MapData.cpp : 实现文件
//

#include "stdafx.h"
#include "2DMapEditor.h"
#include "MapData.h"

const size_t BlockSize=64;
// MapData

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