#include "ScreenDataStructure.h"
#include <iostream>
#include <string>


ScreenDataStructure* ScreenDataStructure::_screenData = nullptr;

ScreenDataStructure* ScreenDataStructure::getScreenDataInstance()
{
	if (_screenData == nullptr)
	{
		_screenData = new ScreenDataStructure;
	}

	return _screenData;
}

void ScreenDataStructure::setData(std::vector<std::vector<int>> vec)
{
	int rows = vec.size();
	int cols = vec[0].size();

	if (rows != numOfRows || cols != numOfCols)
	{
		// throw(std::string("Error !\n [ScreenDataStructure::setData] size illegal\n"));
	}

	if (Data == nullptr)
	{
		resetData(rows ,cols);
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Data[i][j] = vec[i][j];
		}
	}

}

void ScreenDataStructure::setData(int** arrData, int rows, int cols)
{
	if (rows != numOfRows || cols != numOfCols)
	{
		// throw(std::string("Error !\n [ScreenDataStructure::setData] size illegal\n"));
		std::cout << "Error !\n [ScreenDataStructure::setData] size illegal\n" << std::endl;
		resetData(rows, cols);
	}


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Data[i][j] = arrData[i][j];
		}
	}
}

int** ScreenDataStructure::getData(int& rows, int& cols)
{
	rows = this->numOfRows;
	cols = this->numOfCols;
	return this->Data;
}

ScreenDataStructure::ScreenDataStructure()
{
	std::cout << "[ScreenDataStructure::ScreenDataStructure]" << std::endl;
	Data = nullptr;
	numOfRows = 1;
	numOfCols = 1;
	if (Data == nullptr)
	{
		resetData(numOfRows, numOfCols);
	}
}

ScreenDataStructure::~ScreenDataStructure()
{

	if (Data != nullptr)
	{
		if (Data[0] != nullptr)
		{
			for (int i = 0; i < numOfCols; i++)
			{
				delete[] Data[i];
			}
		}
		delete[] Data;
	}
}

void ScreenDataStructure::resetData(int rows, int cols)
{
	if (Data != nullptr)
	{
		if (Data[0] != nullptr)
		{
			for (int i = 0; i < numOfCols; i++)
			{
				delete[] Data[i];
			}
		}
		delete[] Data;
	}

	numOfRows = rows;
	numOfCols = cols;

	Data = new int* [numOfRows];
	for (int i = 0; i < numOfRows; i++)
	{
		Data[i] = new int[numOfCols];
		for (int j = 0; j < numOfCols; j++)
		{
			Data[i][j] = 0;
		}
	}
}
