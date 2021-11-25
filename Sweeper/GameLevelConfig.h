#pragma once

#include "AppConfig.h"
#include <tuple>
#include <string>

class GameLevelConfig;
class HighLevelConfig;
class MidelLevelConfig;
class LowLevelConfig;

typedef GameLevelConfig		GameLevel;
typedef HighLevelConfig		HighLevel;
typedef MidelLevelConfig	MidelLevel;
typedef LowLevelConfig		LowLevel;


// 采用State模式
class GameLevelConfig
{
public:
	virtual int getMapHight() {
		return mapHight;
	}

	virtual int getMapWidth() {
		return mapWidth;
	}

	virtual int getNumOfMines() {
		return numOfMines;
	}

	virtual std::tuple<int, int> getMapSize() {
		return std::make_tuple(mapHight, mapWidth);
	}

protected:
	int mapHight;
	int mapWidth;

	int numOfMines;

	std::string LevelName;
};

/// <summary>
/// 高难度游戏设置类
/// </summary>
class HighLevelConfig : public GameLevelConfig
{
public:
	HighLevelConfig();
};


class MidelLevelConfig : public GameLevelConfig
{
public:
	MidelLevelConfig();
};

class LowLevelConfig : public GameLevelConfig
{
public:
	LowLevelConfig();
};