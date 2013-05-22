#pragma once
#include "operation.h"
class UndoInsertScenery :
	public Operation
{
public:
	UndoInsertScenery(int where);
	~UndoInsertScenery(void);

	virtual Operation* Execute(MapData &mapData);

private:
	int m_where;
};

