#include "IntRander.h"
#include <iostream>

/// <summary>
/// 初始化
/// </summary>
/// <param name="rangeSize">取参数范围 0 ~ rangSize</param>
/// <param name="randSize">取出随机数数值</param>
IntRander::IntRander(int rangeSize, int randSize)
{
	srand(time(0));
	v = new std::vector<int>(rangeSize, 0);
	this->rangeSize = rangeSize;
	this->randSize = randSize;

	currentIndex = rangeSize - 1;

	for (int i = 0; i < rangeSize; ++i)
	{
		(*v)[i] = i;
	}

	for (int i = 0; i < randSize; i++)
	{
		int index = rand() % (currentIndex+1);
		// std::cout << "index:" << index << std::endl;
		std::swap((*v)[index], (*v)[currentIndex]);
		currentIndex--;
	}
}

/// <summary>
/// 获取下一个随机数
/// </summary>
/// <returns>随机值</returns>
int IntRander::getNext()
{
	if (currentIndex == rangeSize)
	{
		return -1;	// if return -1 the random is over
	}
	return (*v)[++currentIndex];
}
