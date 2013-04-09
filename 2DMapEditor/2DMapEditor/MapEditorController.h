#pragma once

#include"SingletonHolder.h"

class MapEditorController
{
public:
	MapEditorController(void);
	~MapEditorController(void);
};

typedef SingletonHolder<MapEditorController> MapEditorControllerSingleton;

