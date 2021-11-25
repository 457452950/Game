#include "Sweeper.h"

#include <iostream>
#include <queue>

#include "IntRander.h"

Sweeper* Sweeper::_instance = nullptr;

/// <summary>
/// ����ģʽ ˽�г�ʼ������
/// </summary>
/// <param name="config">��Ϸ�Ѷ���</param>
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
/// ���㵱ǰλ����Χ���׵�����
/// </summary>
/// <param name="row">�к�</param>
/// <param name="col">�к�</param>
/// <returns>��Χ���׵�����</returns>
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
/// �ڰ���0ʱ��������������0���丽�����һ�񷭿������ײ�������
/// </summary>
/// <param name="row">��ǰλ���к�</param>
/// <param name="col">��ǰλ���к�</param>
void Sweeper::unCoverNearGround(int row, int col)
{
	std::cout << "Sweeper::unCoverNearGround" << std::endl;

	// ����������Ȳ���
	std::queue<int> que;
	que.push(row * 1000 + col);

	while (que.size())
	{
		int val = que.front();

		int _row = val / 1000;
		int _col = val % 1000;
		que.pop();

		// ��Ӹ���ֵ
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

		// ��ת
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
/// ����ģʽ��ȡ·��
/// </summary>
/// <returns>ȫ�ֵ�Ψһ�����</returns>
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
/// ������Ϸ�Ѷ�
/// </summary>
/// <param name="config">��Ϸ�ȼ���</param>
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
/// ��Ϸ���¿�ʼ
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
/// ��Ϸ������� ����  
/// </summary>
/// <param name="row">ָ����</param>
/// <param name="col">ָ����</param>
/// <param name="cmd">����ָ��</param>
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
/// ��Ϸcommand������ģʽ���
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
					std::cout << "��";
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
/// ��Ϸcommand������ģʽ ��Ϸ��������
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
/// ��ȡ��Ϸ����������ݽӿ�
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
/// ��ȡ��ǰ����λ�õ�ֵ�Ķ�����ʾ���״̬
/// </summary>
/// <param name="value">����λ�õ�ֵ</param>
/// <returns>״ֵ̬SweeperShowState</returns>
SweeperShowState Sweeper::getBlockState(int value)
{
	int _flag = value % 16;
	int MineVal = value / 16;
	if (_flag % 2)		// ĩβΪ 1 ����״̬
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
