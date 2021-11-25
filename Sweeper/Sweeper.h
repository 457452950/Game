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
/// ����ģʽ��ȡ·��
/// </summary>
/// <returns>ȫ�ֵ�Ψһ�����</returns>
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
	/// ������Ϸ�Ѷ�
	/// </summary>
	/// <param name="config">��Ϸ�ȼ���</param>
	void resize(GameLevelConfig* config);
	/// <summary>
	/// ��Ϸ���¿�ʼ
	/// </summary>
	void SweeperReStart();

	/// <summary>
	/// ��Ϸ������� ����  
	/// </summary>
	/// <param name="row">ָ����</param>
	/// <param name="col">ָ����</param>
	/// <param name="cmd">����ָ��</param>
	void upDate(int row, int col, SweeperCommandState);

	/// <summary>
	/// ��Ϸcommand������ģʽ���
	/// </summary>
	void printMap();
	/// <summary>
	/// ��Ϸcommand������ģʽ ��Ϸ��������
	/// </summary>
	void printGameOverMap();

	/// <summary>
	/// ��ȡ��Ϸ����������ݽӿ�
	/// </summary>
	/// <returns>std::vector<std::vector<int>></returns>
	std::vector<std::vector<int>> getMapData();
	/// <summary>
	/// ��ȡ��ǰ����λ�õ�ֵ�Ķ�����ʾ���״̬
	/// </summary>
	/// <param name="value">����λ�õ�ֵ</param>
	/// <returns>״ֵ̬SweeperShowState</returns>
	SweeperShowState getBlockState(int value);

private:
	/// <summary>
	/// ����ģʽ ˽�г�ʼ������
	/// </summary>
	/// <param name="config">��Ϸ�Ѷ���</param>
	Sweeper(GameLevelConfig* config);

	/// <summary>
	/// ���㵱ǰλ����Χ���׵�����
	/// </summary>
	/// <param name="row">�к�</param>
	/// <param name="col">�к�</param>
	/// <returns>��Χ���׵�����</returns>
	const int findNearMines(int row, int col);

	/// <summary>
	/// �ڰ���0ʱ��������������0���丽�����һ�񷭿������ײ�������
	/// </summary>
	/// <param name="row">��ǰλ���к�</param>
	/// <param name="col">��ǰλ���к�</param>
	void unCoverNearGround(int row, int col);

private:
	/// <summary>
	/// ɨ��������Ŀ
	/// </summary>
	int numOfRows;
	/// <summary>
	/// ɨ��������Ŀ
	/// </summary>
	int numOfColumns;

	/// <summary>
	/// �ܵ�����Ŀ
	/// </summary>
	int numOfMines;

	/// <summary>
	/// ��ͼ��Ϣָ��
	/// </summary>
	int** mapData;

	ScreenDataStructure* screen;

private:
	/// <summary>
	/// ȫ��ΨһSweeper����
	/// </summary>
	static Sweeper* _instance;


private:
	void sendDataToScreen();

	int** screenData;
};




