#pragma once

#include <vector>
#include <random>
#include <time.h>

// 随机数制造类
class IntRander
{
public:
	/// <summary>
	/// 初始化
	/// </summary>
	/// <param name="rangeSize">取参数范围 0 ~ rangSize</param>
	/// <param name="randSize">取出随机数数值</param>
	IntRander(int rangeSize, int randSize);

	/// <summary>
	/// 获取下一个随机数
	/// </summary>
	/// <returns>随机值</returns>
	int getNext();

private:
	std::vector<int>* v;

	int rangeSize;
	int randSize;
	int currentIndex;
};

