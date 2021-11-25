#include "GameLevelConfig.h"
#include <iostream>

/// <summary>
/// ���Ѷ���Ϸ������
/// </summary>
HighLevelConfig::HighLevelConfig()
{
    mapHight = HIGH_LEVEL_MAP_SIZE_HIGHT;
    mapWidth = HIGH_LEVEL_MAP_SIZE_WIDTH;
    numOfMines = HIGN_LEVEL_MINE_NUMBER;

    LevelName = "HIGH";
}



MidelLevelConfig::MidelLevelConfig()
{
    mapHight = MIDEL_LEVEL_MAP_SIZE;
    mapWidth = MIDEL_LEVEL_MAP_SIZE;
    numOfMines = MIDEL_LEVEL_MINE_NUMBER;

    LevelName = "MIDEL";
}

LowLevelConfig::LowLevelConfig()
{
    mapHight = LOW_LEVEL_MAP_SIZE;
    mapWidth = LOW_LEVEL_MAP_SIZE;
    numOfMines = LOW_LEVEL_MINE_NUMBER;

    LevelName = "LOW";
}
