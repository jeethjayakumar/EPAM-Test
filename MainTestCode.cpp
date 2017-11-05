/*
 * MainTestCode.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: jjayakumar
 */
#include<iostream>
#include<vector>
using namespace std;

#include "MapStructDef.hpp"

int main()
{
	int **height = new int *[5];
	int i, j;
	vector<Coordinate> contDivide;
	vector<Coordinate> :: iterator it;

	cout<< " Enter height matrix: (Press Enter key after entering each element in matrix)";
	for (i = 0; i < 5; i++)
	{
		cout<<"Row "<<i + 1<<" : "<<endl;
		height[i] = new int [5];
		for (j = 0; j < 5; j ++)
		{
			cin>>height[i][j];
		}
	}
	setContDivide(5, 5, height, contDivide);

	// Printing the output
	cout<<"Coordinates: ";
	for (it = contDivide.begin(); it != contDivide.end(); it++)
	{
		cout<<"("<<it->getRow()<<","<<it->getColn()<<") ";
	}

	for (i = 0; i < 5; i++)
		delete[] height[i];
	delete[] height;

	return 0;
}
