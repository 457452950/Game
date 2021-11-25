#include "Graphic.h"

Graphic* Graphic::_graphicInstance = nullptr;


Graphic::Graphic()
{
	initgraph(SCREEN_WIDTH, SCREEN_HIGHT, EW_NOMINIMIZE | EW_SHOWCONSOLE);

	screen = ScreenDataStructure::getScreenDataInstance();
}

Graphic::~Graphic()
{
	closegraph();
}
