#include "stdafx.h"
#include "OperationStack.h"


OperationStack::OperationStack(void)
{
}


OperationStack::~OperationStack(void)
{
	Clear();
}

void OperationStack::Clear()
{
	ClearRedoStack();
	ClearUndoStack();
}

void OperationStack::ClearRedoStack()
{
	for (size_t i = 0;i<m_redo.size();i++)
	{
		delete m_redo[i];
	}
	m_redo.clear();
}

void OperationStack::ClearUndoStack()
{
	for (size_t i = 0;i<m_undo.size();i++)
	{
		delete m_undo[i];
	}
	m_undo.clear();
}

void OperationStack::Undo(MapData& mapData)
{
	if (0 == m_undo.size())
	{
		return;
	}

	Operation *pUndo = m_undo[m_undo.size() - 1];
	Operation *pRedo = pUndo->Execute(mapData);
	m_redo.push_back(pRedo);
	delete pUndo;
	m_undo.pop_back();
}

void OperationStack::Redo(MapData& mapData)
{
	if(0 == m_redo.size())
	{
		return;
	}

	Operation *pRedo = m_redo[m_redo.size() - 1];
	Operation *pUndo = pRedo->Execute(mapData);
	m_undo.push_back(pUndo);
	delete pRedo;
	m_redo.pop_back();
}

void OperationStack::Ondo(Operation *pOperation)
{
	m_undo.push_back(pOperation);
}