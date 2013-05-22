#pragma once
#include "operation.h"
class RedoDeleteSelection :
	public Operation
{
public:
	RedoDeleteSelection(void);
	~RedoDeleteSelection(void);

	virtual Operation* Execute(MapData &mapData);
};

