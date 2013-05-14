#include "stdafx.h"
#include "UndoChangeTerrain.h"

#include "MapData.h"
#include "MapEditorController.h"


UndoChangeTerrain::UndoChangeTerrain(string terrainFilePath) 
{
	m_terrainFilePath = terrainFilePath;
}


UndoChangeTerrain::~UndoChangeTerrain(void)
{
}


Operation *UndoChangeTerrain::Execute(MapData &mapData){
	string currentTerrainPath = mapData.GetTerrainFilePath();
	mapData.ChangeTerrain(m_terrainFilePath);
	return new UndoChangeTerrain(currentTerrainPath);
}