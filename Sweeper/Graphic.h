#pragma once

#include <graphics.h>
#include "AppConfig.h"
#include "ScreenDataStructure.h"

class Graphic
{
public:
	virtual ~Graphic();

	virtual void input(int& x, int& y, int& cmd) = 0;
	virtual void draw() = 0;

protected:
	Graphic();



	static Graphic* _graphicInstance;

	ScreenDataStructure* screen;

};

