#pragma once

class MapData;

class Operation
{
public:
	Operation(void);
	~Operation(void);

	virtual Operation* Execute(MapData &mapData) = 0;
};

