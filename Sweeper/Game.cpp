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
/// ��Ϸ��ʼ ��ѭ��
/// | ��ʾ����
/// | �������
/// | ��Ϸ����
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
/// ��Ϸ�������
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
/// ��Ϸ�������
/// </summary>
bool Game::input()
{
	cmd = -1;
	// int x, y, cmd;
	/*std::cout << "����������Ͳ���\n" 
		<< "���ؿ�һ��-1�� ���� - 0�� �������� - 1������ʺ� - 2��:";*/
	// std::cin >> x >> y >> cmd;
	g->input(x, y, cmd);
	if (cmd == -1)
	{
		return false;
	}
	return true;
}

/// <summary>
/// ��Ϸ����
/// </summary>
void Game::update()
{
	
	s->upDate(x, y, SweeperCommandState(cmd));
}