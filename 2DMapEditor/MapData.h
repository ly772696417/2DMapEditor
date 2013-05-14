#pragma once

#include <string>
#include <list>
#include "Operation.h"
#include "UndoChangeTerrain.h"
#include "Scenery.h"

using namespace std;

// MapData ÃüÁîÄ¿±ê

class MapData : public CObject
{
public:
	MapData(const string& terrainName = "",size_t xLength = 64,size_t yLength = 64);
	virtual ~MapData();

private:
	string m_terrainFilePath;
	size_t m_xlength,m_yLength;
	CPoint m_offest;
public:
	string GetTerrainFilePath()const { return m_terrainFilePath; };
	CPoint GetOffest() { return m_offest; };
	size_t getWidth() { return m_xlength; };
	size_t getHeight() { return m_yLength; };
	void   SetOffest(CPoint offest,const CRect & rect );

public:
	Operation *ChangeTerrain(const string& terrainFilePath);
	Operation *InsertScenery(const string& filePath,const CPoint& point);

public:
	list<Scenery *> m_sceneryList;
};


