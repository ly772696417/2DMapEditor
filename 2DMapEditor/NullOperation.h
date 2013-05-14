#pragma once
#include "operation.h"
class NullOperation :
	public Operation
{
public:
	NullOperation(void);
	~NullOperation(void);

	virtual Operation* Execute(MapData &mapData) { return new NullOperation; };
};

