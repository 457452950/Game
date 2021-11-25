#pragma once

#include <vector>

class ScreenDataStructure;



class ScreenDataStructure
{
public:
	static ScreenDataStructure* getScreenDataInstance();

	/// <summary>
	/// ���ýṹ�Ĵ�С
	/// </summary>
	/// <param name="rows"></param>
	/// <param name="cols"></param>
	void setSize(int rows, int cols) {
		numOfCols = cols;
		numOfRows = rows;
	}

	/// <summary>
	/// �� ��άvector���� ��ȡ����
	/// </summary>
	/// <param name="vec"></param>
	void setData(std::vector<std::vector<int>> vec);
	/// <summary>
	/// �� int** ��ȡ����
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
	/// ��ʼ������ ����
	/// </summary>
	void resetData(int rows, int cols);

private:
	static ScreenDataStructure* _screenData;

	int** Data;
	int numOfRows;
	int numOfCols;
};

