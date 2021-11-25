#include "Game.h"
#include <iostream>


#include "GameLevelConfig.h"
#include "ScreenDataStructure.h"

Game::Game()
{
	isOver = false;

	clk_clock = std::chrono::system_clock::now();

	GameLevel* h = new HighLevel;
	GameLevel* m = new MidelLevel;
	GameLevel* l = new LowLevel;

	g = SweeperGraphic::getSweeperGraphicInstance();

	s = Sweeper::getSweepInstance();
	s->resize(m);

	x = -1;
	y = -1;
	cmd = -1;
}

/// <summary>
/// 游戏开始 主循环
/// | 显示画面
/// | 玩家输入
/// | 游戏更新
/// </summary>
void Game::Start()
{
	while (!isOver)
	{
		clk_clock = std::chrono::system_clock::now();
		show();

		while (!input())
		{
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - clk_clock);
			if (duration.count() >= (1 * 1000000 / 24))
			{
				break;
			}
		}
		update();
	}
}


/// <summary>
/// 游戏画面输出
/// </summary>
void Game::show()
{
	/*s->printMap();
	std::cout << "-----------------------" << std::endl;
	std::vector<std::vector<int>> v = s->getMapData();
	for (auto ite : v)
	{
		for (auto i : ite)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}*/
	
	g->draw();
}

/// <summary>
/// 游戏玩家输入
/// </summary>
bool Game::input()
{
	cmd = -1;
	// int x, y, cmd;
	/*std::cout << "请输入坐标和操作\n" 
		<< "（重开一局-1， 翻开 - 0， 插入旗帜 - 1，标记问号 - 2）:";*/
	// std::cin >> x >> y >> cmd;
	g->input(x, y, cmd);
	if (cmd == -1)
	{
		return false;
	}
	return true;
}

/// <summary>
/// 游戏更新
/// </summary>
void Game::update()
{
	
	s->upDate(x, y, SweeperCommandState(cmd));
}