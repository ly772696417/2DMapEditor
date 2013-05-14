#pragma once

#include "Operation.h"
#include <vector>

using namespace std;

class OperationStack
{
public:
	OperationStack(void);
	~OperationStack(void);

	void Undo(MapData& mapData);
	void Redo(MapData& mapData);
	void Ondo(Operation *pOperation);

	void Clear();

private:
	vector<Operation*> m_undo,m_redo;

	void ClearUndoStack();
	void ClearRedoStack();
};

