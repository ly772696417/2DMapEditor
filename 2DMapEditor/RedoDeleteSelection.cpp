#include "stdafx.h"
#include "RedoDeleteSelection.h"
#include "MapData.h"


RedoDeleteSelection::RedoDeleteSelection(void)
{
}


RedoDeleteSelection::~RedoDeleteSelection(void)
{
}

Operation* RedoDeleteSelection::Execute(MapData &mapData)
{
	return mapData.DeleteSelection();
}

