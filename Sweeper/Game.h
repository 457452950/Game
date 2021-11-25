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
	/// 游戏开始 主循环
	/// | 显示画面
	/// | 玩家输入
	/// | 游戏更新
	/// </summary>
	void Start();

	/// <summary>
	/// 游戏画面输出
	/// </summary>
	void show();
	/// <summary>
	/// 游戏玩家输入
	/// </summary>
	bool input();
	/// <summary>
	/// 游戏更新
	/// </summary>
	void update();

private:
	/// <summary>
	/// 游戏结束标记
	/// </summary>
	bool isOver;

	Sweeper* s;
	int x;
	int y;
	int cmd;

	Graphic* g;

	std::chrono::system_clock::time_point clk_clock;
};

