#pragma once

#include <vector>
#include <random>
#include <time.h>

// �����������
class IntRander
{
public:
	/// <summary>
	/// ��ʼ��
	/// </summary>
	/// <param name="rangeSize">ȡ������Χ 0 ~ rangSize</param>
	/// <param name="randSize">ȡ���������ֵ</param>
	IntRander(int rangeSize, int randSize);

	/// <summary>
	/// ��ȡ��һ�������
	/// </summary>
	/// <returns>���ֵ</returns>
	int getNext();

private:
	std::vector<int>* v;

	int rangeSize;
	int randSize;
	int currentIndex;
};

