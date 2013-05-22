#pragma once
#include "operation.h"

#include <vector>
#include <list>

using namespace std;

class UndoMove :
	public Operation
{
public:
	UndoMove(const CPoint& moveV);
	UndoMove(const UndoMove& o);
	~UndoMove(void);

	virtual Operation* Execute(MapData &mapData);
	void AppendGUID(const long guid){m_vGUIDs.push_back(guid);};

private:
	CPoint m_moveV;
	vector<long> m_vGUIDs;
};

