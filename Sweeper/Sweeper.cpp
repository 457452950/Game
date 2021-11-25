#include "Sweeper.h"

#include <iostream>
#include <queue>

#include "IntRander.h"

Sweeper* Sweeper::_instance = nullptr;

/// <summary>
/// 单例模式 私有初始化函数
/// </summary>
/// <param name="config">游戏难度类</param>
Sweeper::Sweeper(GameLevelConfig* config)
{
	// init screen
	screen = ScreenDataStructure::getScreenDataInstance();

	// init
	numOfRows = config->getMapHight();
	numOfColumns = config->getMapWidth();
	numOfMines = config->getNumOfMines();
	
	// reset size
	mapData = new int*[numOfRows];
	for (int i = 0; i < numOfRows; i++)
	{
		mapData[i] = new int[numOfColumns];
	}

	// reset size
	screenData = new int* [numOfRows];
	for (int i = 0; i < numOfRows; i++)
	{
		screenData[i] = new int[numOfColumns];
	}

	// start
	SweeperReStart();
}

/// <summary>
/// 计算当前位置周围地雷的数量
/// </summary>
/// <param name="row">行号</param>
/// <param name="col">列号</param>
/// <returns>周围地雷的数量</returns>
const int Sweeper::findNearMines(int row, int col)
{
	int num = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; ++j)
		{
			if (row + i < 0 || row + i >= numOfRows || col + j < 0 || col + j >= numOfColumns)
				continue;
			if (mapData[row+i][col+j] == 8)
			{
				num++;
			}
		}
	}

	return num;
}

/// <summary>
/// 在按到0时，将附近的所有0及其附近最多一格翻开（地雷不翻开）
/// </summary>
/// <param name="row">当前位置行号</param>
/// <param name="col">当前位置列号</param>
void Sweeper::unCoverNearGround(int row, int col)
{
	std::cout << "Sweeper::unCoverNearGround" << std::endl;

	// 采用深度优先策略
	std::queue<int> que;
	que.push(row * 1000 + col);

	while (que.size())
	{
		int val = que.front();

		int _row = val / 1000;
		int _col = val % 1000;
		que.pop();

		// 添加附近值
		if (mapData[_row][_col] == 0b0)
		{
			if (_row > 0 )
			{
				val = (_row - 1) * 1000 + _col;
				que.push(val);

				if (_col > 0)
				{
					val = (_row - 1) * 1000 + _col - 1;
					que.push(val);
				}
				if (_col < numOfColumns - 1)
				{
					val = (_row - 1) * 1000 + _col + 1;
					que.push(val);
				}
			}
			if (_row < numOfRows - 1)
			{
				val = (_row + 1) * 1000 + _col;
				que.push(val);
				if (_col > 0)
				{
					val = (_row + 1) * 1000 + _col - 1;
					que.push(val);
				}
				if (_col < numOfColumns - 1)
				{
					val = (_row + 1) * 1000 + _col + 1;
					que.push(val);
				}
			}
			if (_col > 0)
			{
				val = _row * 1000 + _col - 1;
				que.push(val);
			}
			if (_col < numOfColumns - 1)
			{
				val = _row * 1000 + _col + 1;
				que.push(val);
			}
		}// if (mapData[_row][_col] == 0b0)

		// 翻转
		mapData[_row][_col] |= 0b1;

	}// while (que.size())

}

void Sweeper::sendDataToScreen()
{
	if (mapData != nullptr)
	{
		for (int i = 0; i < numOfRows; ++i)
		{
			for (int j = 0; j < numOfColumns; j++)
			{
				switch (getBlockState(mapData[i][j]))
				{
				case SweeperShowState::Cover:
					screenData[i][j] = (int)SweeperShowState::Cover;
					break;
				case SweeperShowState::QuestMark:
					screenData[i][j] = (int)SweeperShowState::QuestMark;
					break;
				case SweeperShowState::Mine:
					screenData[i][j] = (int)SweeperShowState::Mine;
					break;
				default:
					screenData[i][j] = (int)getBlockState(mapData[i][j]);
					break;
				}
			}
		}
	}

	screen->setData(screenData, numOfRows, numOfColumns);
}

/// <summary>
/// 单例模式获取路径
/// </summary>
/// <returns>全局的唯一类对象</returns>
Sweeper* Sweeper::getSweepInstance()
{
	if (_instance == nullptr)
	{
		GameLevelConfig* m = new MidelLevelConfig;
		_instance = new Sweeper(m);
	}
	return _instance;
}

/// <summary>
/// 重设游戏难度
/// </summary>
/// <param name="config">游戏等级类</param>
void Sweeper::resize(GameLevelConfig* config)
{
	// Clean Data
	for (int i = 0; i < numOfRows; i++)
	{
		delete[] mapData[i];
		delete[] screenData[i];
	}
	delete[] mapData;
	delete[] screenData;

	// reset data
	numOfRows = config->getMapHight();
	numOfColumns = config->getMapWidth();
	numOfMines = config->getNumOfMines();
	

	// reset map
	mapData = new int* [numOfRows];
	for (int i = 0; i < numOfRows; i++)
	{
		mapData[i] = new int[numOfColumns];
	}
	screenData = new int* [numOfRows];
	for (int i = 0; i < numOfRows; i++)
	{
		screenData[i] = new int[numOfColumns];
	}

	SweeperReStart();
}

/// <summary>
/// 游戏重新开始
/// </summary>
void Sweeper::SweeperReStart()
{
	int size = numOfColumns * numOfRows;

	for (int i = 0; i < numOfRows; i++)
	{
		for (int j = 0; j < numOfColumns; j++)
		{
			mapData[i][j] = 0;
		}
	}

	IntRander ir(size, numOfMines);
	for (int i = 0; i < numOfMines; i++)
	{
		int ind = ir.getNext();
		mapData[ind / numOfColumns][ind % numOfColumns] = 0b1000;
	}
	
	for (int i = 0; i < numOfRows; i++)
	{
		for (int j = 0; j < numOfColumns; j++)
		{
			if (mapData[i][j] == 0b1000)
				continue;
			mapData[i][j] = findNearMines(i, j) << 4;

		}
	}
	sendDataToScreen();
}

/// <summary>
/// 游戏输入操作 更新  
/// </summary>
/// <param name="row">指定行</param>
/// <param name="col">指定列</param>
/// <param name="cmd">操作指令</param>
void Sweeper::upDate(int row, int col, SweeperCommandState cmd)
{
	switch (cmd)
	{
	case SweeperCommandState::cmd_UnCover:
		if (mapData[row][col] == 0x00)
		{
			unCoverNearGround(row, col);
		}
		mapData[row][col] |= 0b1;
		break;
	case SweeperCommandState::cmd_Flag:
		// mapData[row][col] |= 0b1;
		break;
	case SweeperCommandState::cmd_QuestMark:
		break;
	default:
		break;
	}

	sendDataToScreen();

}


/// <summary>
/// 游戏command命令行模式输出
/// </summary>
void Sweeper::printMap()
{
	if (mapData != nullptr)
	{
		std::cout << "0 1 2 3 4 5 6 7 8 9 " << std::endl;
		for (int i = 0; i < numOfRows; ++i)
		{
			for (int j = 0; j < numOfColumns; j++)
			{
				switch (getBlockState(mapData[i][j]))
				{
				case SweeperShowState::Cover:
					std::cout << "□";
					break;
				case SweeperShowState::QuestMark:
					std::cout << " ?";
					break;
				case SweeperShowState::Mine:
					std::cout << " *";
					break;
				default:
					std::cout << " " << (int)getBlockState(mapData[i][j]);
					break;
				}
			}
			std::cout << ": " << i << std::endl;
		}
	}
}

/// <summary>
/// 游戏command命令行模式 游戏结束画面
/// </summary>
void Sweeper::printGameOverMap()
{
	if (mapData != nullptr)
	{
		std::cout << "    0 1 2 3 4 5 6 7 8 9 " << std::endl;
		for (int i = 0; i < numOfRows; ++i)
		{
			std::cout << i << ": ";
			for (int j = 0; j < numOfColumns; j++)
			{
				
				//

			}
			std::cout << std::endl;
		}
	}
}

/// <summary>
/// 获取游戏输出画面数据接口
/// </summary>
/// <returns>std::vector<std::vector<int>></returns>
std::vector<std::vector<int>> Sweeper::getMapData()
{
	std::vector<std::vector<int>> vec;
	for (int i = 0; i < numOfRows; i++)
	{
		std::vector<int> _v;
		for (int j = 0; j < numOfColumns; j++)
		{
			_v.push_back(mapData[i][j]);
		}
		vec.push_back(_v);
	}

	return vec;
}

/// <summary>
/// 获取当前所在位置的值的对于显示输出状态
/// </summary>
/// <param name="value">所在位置的值</param>
/// <returns>状态值SweeperShowState</returns>
SweeperShowState Sweeper::getBlockState(int value)
{
	int _flag = value % 16;
	int MineVal = value / 16;
	if (_flag % 2)		// 末尾为 1 翻开状态
	{
		if (_flag == 1)
		{
			return SweeperShowState(MineVal);
		}
		else if (_flag == 0b1001)
			return SweeperShowState::Mine;
	}
	else
	{
		if (_flag == 2)
		{
			return SweeperShowState::Flag;
		}
		else if (_flag == 4)
		{
			return SweeperShowState::QuestMark;
		}
		else
		{
			return SweeperShowState::Cover;
		}
	}

}
