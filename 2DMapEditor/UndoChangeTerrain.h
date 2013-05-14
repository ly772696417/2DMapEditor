#pragma once

#include <string>
#include "operation.h"

using namespace std;

class UndoChangeTerrain :
	public Operation
{
public:
	UndoChangeTerrain( string terrainFilePath);
	~UndoChangeTerrain(void);

	virtual Operation *Execute(MapData &mapData);

private:
	string m_terrainFilePath;
};

