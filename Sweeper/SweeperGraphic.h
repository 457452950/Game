#pragma once
#include "Graphic.h"
#include "AppConfig.h"

#define OFFSET_Y 30
#define OFFSET_X 30


class SweeperGraphic :
    public Graphic
{
public:
    static Graphic* getSweeperGraphicInstance();

    void input(int& x, int& y, int& cmd);

    void draw();

private:
    int row2y(int row);
    int col2x(int col);

    int y2row(int y);
    int x2col(int x);

    SweeperGraphic();

    void drawBackGround();
    void drawCover(int x, int y);
    void drawFlag(int x, int y);
    void drawMine(int x, int y);
    void drawNumber0(int x, int y);
    void drawNumber1(int x, int y);
    void drawNumber2(int x, int y);
    void drawNumber3(int x, int y);
    void drawNumber4(int x, int y);
    void drawNumber5(int x, int y);
    void drawNumber6(int x, int y);

    int numOfRows;
    int numOfCols;


    IMAGE img_Flag;
    IMAGE img_Cover;
    IMAGE img_Mine;

    IMAGE img_Number0;
    IMAGE img_Number1;
    IMAGE img_Number2;
    IMAGE img_Number3;
    IMAGE img_Number4;
    IMAGE img_Number5;
    IMAGE img_Number6;
    IMAGE img_Number7;
    IMAGE img_Number8;
};

