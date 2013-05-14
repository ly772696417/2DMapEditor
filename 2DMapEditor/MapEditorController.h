#pragma once

#include <string>

#include"SingletonHolder.h"
#include "MapData.h"
#include "Operation.h"
#include "OperationStack.h"
#include "CMyGame.h"
#include "MotionScenery.h"

using namespace std;

class MapEditorController
{
public:
	MapEditorController(void);
	~MapEditorController(void);

public:
	void NewMap(const CPoint& mapSize);

	void ChangeTerrain(const string& terrainFilePath);

	void Undo();
	void Redo();

	void drawModel(CPoint cp);

	MapData * GetMapData(){return m_pMapData;};

	const string& GetFilePath()const{ return m_editfilePath; };

	//EditorMode
	typedef enum EditorMode{ ModeSelection,ModeBrush,ModeMove };
	EditorMode GetEditorMode()const{ return m_editorMode; };
	void SetModeMove(){m_editorMode = ModeMove;};
	void SetModeSelection(){ m_editorMode = ModeSelection; };
	void SetModeBrush(const char* filePath){ m_editorMode = ModeBrush; m_editfilePath = filePath; };

	//Operations
	void InsertScenery(const CPoint& point);

	LPDIRECT3DDEVICE9 Getdevice();

public:
	CMyGame *m_myGame;

private:
	MapData *m_pMapData;
	
	EditorMode m_editorMode;

	string m_terrainFilePath;
	OperationStack m_operationStack;

	string m_editfilePath;
};

typedef SingletonHolder<MapEditorController> MapEditorControllerSingleton;

