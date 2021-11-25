#pragma once
#include <vector>
#include "AppConfig.h"
#include "GameLevelConfig.h"
#include "ScreenDataStructure.h"

enum class SweeperShowState
{
	Zero = 0,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,

	Cover = 10,
	Flag = 11,
	QuestMark = 12,
	Mine = 13
};

enum class SweeperCommandState
{
	cmd_UnCover = 1,
	cmd_Flag = 2,
	cmd_QuestMark = 3,
};


class Sweeper
{
public:
	/// <summary>
/// 单例模式获取路径
/// </summary>
/// <returns>全局的唯一类对象</returns>
	static Sweeper* getSweepInstance();
	~Sweeper()
	{
		for (int i = 0; i < numOfRows; i++)
		{
			delete[] mapData[i];
		}
		delete[] mapData;
	}

public:
	/// <summary>
	/// 重设游戏难度
	/// </summary>
	/// <param name="config">游戏等级类</param>
	void resize(GameLevelConfig* config);
	/// <summary>
	/// 游戏重新开始
	/// </summary>
	void SweeperReStart();

	/// <summary>
	/// 游戏输入操作 更新  
	/// </summary>
	/// <param name="row">指定行</param>
	/// <param name="col">指定列</param>
	/// <param name="cmd">操作指令</param>
	void upDate(int row, int col, SweeperCommandState);

	/// <summary>
	/// 游戏command命令行模式输出
	/// </summary>
	void printMap();
	/// <summary>
	/// 游戏command命令行模式 游戏结束画面
	/// </summary>
	void printGameOverMap();

	/// <summary>
	/// 获取游戏输出画面数据接口
	/// </summary>
	/// <returns>std::vector<std::vector<int>></returns>
	std::vector<std::vector<int>> getMapData();
	/// <summary>
	/// 获取当前所在位置的值的对于显示输出状态
	/// </summary>
	/// <param name="value">所在位置的值</param>
	/// <returns>状态值SweeperShowState</returns>
	SweeperShowState getBlockState(int value);

private:
	/// <summary>
	/// 单例模式 私有初始化函数
	/// </summary>
	/// <param name="config">游戏难度类</param>
	Sweeper(GameLevelConfig* config);

	/// <summary>
	/// 计算当前位置周围地雷的数量
	/// </summary>
	/// <param name="row">行号</param>
	/// <param name="col">列号</param>
	/// <returns>周围地雷的数量</returns>
	const int findNearMines(int row, int col);

	/// <summary>
	/// 在按到0时，将附近的所有0及其附近最多一格翻开（地雷不翻开）
	/// </summary>
	/// <param name="row">当前位置行号</param>
	/// <param name="col">当前位置列号</param>
	void unCoverNearGround(int row, int col);

private:
	/// <summary>
	/// 扫雷总行数目
	/// </summary>
	int numOfRows;
	/// <summary>
	/// 扫雷总列数目
	/// </summary>
	int numOfColumns;

	/// <summary>
	/// 总地雷数目
	/// </summary>
	int numOfMines;

	/// <summary>
	/// 地图信息指针
	/// </summary>
	int** mapData;

	ScreenDataStructure* screen;

private:
	/// <summary>
	/// 全局唯一Sweeper对象
	/// </summary>
	static Sweeper* _instance;


private:
	void sendDataToScreen();

	int** screenData;
};




