#pragma once

#include <vector>

class ScreenDataStructure;



class ScreenDataStructure
{
public:
	static ScreenDataStructure* getScreenDataInstance();

	/// <summary>
	/// 设置结构的大小
	/// </summary>
	/// <param name="rows"></param>
	/// <param name="cols"></param>
	void setSize(int rows, int cols) {
		numOfCols = cols;
		numOfRows = rows;
	}

	/// <summary>
	/// 从 二维vector数组 读取数据
	/// </summary>
	/// <param name="vec"></param>
	void setData(std::vector<std::vector<int>> vec);
	/// <summary>
	/// 从 int** 读取数据
	/// </summary>
	/// <param name="arrData"></param>
	/// <param name="rows"></param>
	/// <param name="cols"></param>
	void setData(int** arrData, int rows, int cols);

	int** getData(int& rows, int& cols);


private:
	ScreenDataStructure();
	~ScreenDataStructure();

	/// <summary>
	/// 初始化数据 制零
	/// </summary>
	void resetData(int rows, int cols);

private:
	static ScreenDataStructure* _screenData;

	int** Data;
	int numOfRows;
	int numOfCols;
};

