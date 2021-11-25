#pragma once
#include "AppConfig.h"
#include <chrono>

#include "Sweeper.h"
#include "SweeperGraphic.h"


class Game
{
public:
	Game();

	/// <summary>
	/// ��Ϸ��ʼ ��ѭ��
	/// | ��ʾ����
	/// | �������
	/// | ��Ϸ����
	/// </summary>
	void Start();

	/// <summary>
	/// ��Ϸ�������
	/// </summary>
	void show();
	/// <summary>
	/// ��Ϸ�������
	/// </summary>
	bool input();
	/// <summary>
	/// ��Ϸ����
	/// </summary>
	void update();

private:
	/// <summary>
	/// ��Ϸ�������
	/// </summary>
	bool isOver;

	Sweeper* s;
	int x;
	int y;
	int cmd;

	Graphic* g;

	std::chrono::system_clock::time_point clk_clock;
};

