#pragma once

#include <string>
#include <list>
#include "Operation.h"
#include "NullOperation.h"
#include "Scenery.h"

using namespace std;

// MapData ÃüÁîÄ¿±ê

class MapData : public CObject
{

	friend class Operation;
	friend class UndoInsertScenery;
	friend class UndoChangeTerrain;
	friend class UndoDeleteSeletion;
	friend class UndoMove;
	friend class RedoDeleteSelection;
	friend class RedoInsertScenery;

public:
	MapData(const string& terrainName = "",size_t xLength = 64,size_t yLength = 64);
	virtual ~MapData();

private:
	string m_terrainFilePath;
	size_t m_xlength,m_yLength;
	CPoint m_offest;
	CPoint m_totMoveV;
public:
	string GetTerrainFilePath()const { return m_terrainFilePath; };
	CPoint GetOffest() { return m_offest; };
	size_t getWidth() { return m_xlength; };
	size_t getHeight() { return m_yLength; };
	void   SetOffest(CPoint offest,const CRect & rect );
	
	CPoint	MapPoint2ScreenPoint( const CPoint& pt ) const;
	CPoint	ScreenPoint2MapPoint( const CPoint& pt ) const;
public:
	Operation *ChangeTerrain(const string& terrainFilePath);
	Operation *InsertScenery(const string& filePath,const CPoint& point,LPDIRECT3DDEVICE9 d3ddev);
	Operation *MoveMode(CPoint moveVec,bool isLastMove);
	Operation *DeleteSelection();
public:
	list<Scenery *> m_sceneryList;
};


