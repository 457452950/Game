#include "SweeperGraphic.h"
#include <iostream>

Graphic* SweeperGraphic::getSweeperGraphicInstance()
{
	if (_graphicInstance == nullptr)
	{
		_graphicInstance = new SweeperGraphic();
	}
	return _graphicInstance;
}

void SweeperGraphic::input(int& row, int& col, int& cmd)
{
	int x = 0, y = 0;
	while (cmd == -1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.mkLButton)
			{
				x = msg.x;
				y = msg.y;
				cmd = 1;
				while (msg.mkLButton)
				{
					msg = GetMouseMsg();
				}
			}
			else if (msg.mkRButton)
			{
				x = msg.x;
				y = msg.y;
				cmd = 2;
				while (msg.mkRButton)
				{
					msg = GetMouseMsg();
				}
			}
			col = x2col(x);
			row = y2row(y);
			if (col < 0 || col >= numOfCols || row < 0 || row >= numOfRows)
			{
				cmd = -1;
			}
		}
	}
}

void SweeperGraphic::draw()
{
	drawBackGround();
	int** data = screen->getData(numOfRows, numOfCols);

	// std::cout << numOfRows << numOfCols << std::endl;
	for (int i = 0; i < numOfRows; i++)
	{
		for (int j = 0; j < numOfCols; j++)
		{
			int x = col2x(j);
			int y = row2y(i);

			switch (data[i][j])
			{
			case 0:
				drawNumber0(x, y);
				break;		
			case 1:			
				drawNumber1(x, y);
				break;		
			case 2:			
				drawNumber2(x, y);
				break;		
			case 3:			
				drawNumber3(x, y);
				break;		
			case 4:			
				drawNumber4(x, y);
				break;		
			case 5:			
				drawNumber5(x, y);
				break;

			case 10:
				drawCover(x, y);
				break;
			case 11:
				drawFlag(x, y);
				break;

			case 13:
				drawMine(x, y);
				break;

			default:
				break;
			}
		}
	}

}

int SweeperGraphic::row2y(int row)
{
	return row * 25 + OFFSET_Y;
}

int SweeperGraphic::col2x(int col)
{
	return col * 25 + OFFSET_X;
}

int SweeperGraphic::y2row(int y)
{
	return (y - OFFSET_Y) / 25;
}

int SweeperGraphic::x2col(int x)
{
	return (x - OFFSET_X) / 25;
}

SweeperGraphic::SweeperGraphic()
{
	numOfRows = 0;
	numOfCols = 0;

	loadimage(&img_Cover, _T("Image/Cover.png"));
	loadimage(&img_Flag, _T("Image/flag.png"));
	loadimage(&img_Mine, _T("Image/Mine.png"));

	loadimage(&img_Number0, _T("Image/0.png"));
	loadimage(&img_Number1, _T("Image/1.png"));
	loadimage(&img_Number2, _T("Image/2.png"));
	loadimage(&img_Number3, _T("Image/3.png"));
	loadimage(&img_Number4, _T("Image/4.png"));
	loadimage(&img_Number5, _T("Image/5.png"));

}

void SweeperGraphic::drawBackGround()
{
	setfillcolor(RGB(95, 100, 102));
	fillrectangle(0, 0, SCREEN_WIDTH, SCREEN_HIGHT);
}

void SweeperGraphic::drawCover(int x, int y)
{
	putimage(x, y, &img_Cover);
}

void SweeperGraphic::drawFlag(int x, int y)
{
	putimage(x, y, &img_Flag);
}

void SweeperGraphic::drawMine(int x, int y)
{
	putimage(x, y, &img_Mine);
}

void SweeperGraphic::drawNumber0(int x, int y)
{
	putimage(x, y, &img_Number0);
}

void SweeperGraphic::drawNumber1(int x, int y)
{
	putimage(x, y, &img_Number1);
}

void SweeperGraphic::drawNumber2(int x, int y)
{
	putimage(x, y, &img_Number2);
}

void SweeperGraphic::drawNumber3(int x, int y)
{
	putimage(x, y, &img_Number3);
}

void SweeperGraphic::drawNumber4(int x, int y)
{
	putimage(x, y, &img_Number4);
}

void SweeperGraphic::drawNumber5(int x, int y)
{
	putimage(x, y, &img_Number5);
}

void SweeperGraphic::drawNumber6(int x, int y)
{
	putimage(x, y, &img_Number6);
}