#pragma once
#include "operation.h"
#include "Scenery.h"
#include <vector>
#include <list>

using namespace std;

class UndoDeleteSeletion :
	public Operation
{
public:
	UndoDeleteSeletion(void);
	~UndoDeleteSeletion(void);

	virtual Operation* Execute(MapData &mapData);
	void AppendScenery(const Scenery& scenery);

private:
	vector<Scenery> m_vDeleted;
};

