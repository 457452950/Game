#include "IntRander.h"
#include <iostream>

/// <summary>
/// ��ʼ��
/// </summary>
/// <param name="rangeSize">ȡ������Χ 0 ~ rangSize</param>
/// <param name="randSize">ȡ���������ֵ</param>
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
/// ��ȡ��һ�������
/// </summary>
/// <returns>���ֵ</returns>
int IntRander::getNext()
{
	if (currentIndex == rangeSize)
	{
		return -1;	// if return -1 the random is over
	}
	return (*v)[++currentIndex];
}
