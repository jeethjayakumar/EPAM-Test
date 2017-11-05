/*
 * MapCodeDefn.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: jjayakumar
 */
#include <iostream>
#include <vector>
#include "MapStructDef.hpp"
using namespace std;

void calculate_path(int row, int coln, int max_row, int max_coln, TrackMatrix **tracker, int **inp_height);

// TrackMatrix method defn

void TrackMatrix::setAtl(bool flag){rchAtl = flag;}
void TrackMatrix::setPac(bool flag){rchPac = flag;}
void TrackMatrix::setVisit(bool flag){visited = flag;}

bool TrackMatrix::getPacflag(){return rchPac;}
bool TrackMatrix::getAtlflag(){return rchAtl;}
bool TrackMatrix::getVisit(){return visited;}

// Coordinate method defn
void Coordinate::setColn(int coln){	this->coln = coln;}
void Coordinate::setRow(int row){ this->row = row;}

int Coordinate::getColn(){	return coln;}
int Coordinate::getRow(){	return row;}

void setContDivide(int row, int coln, int **inp_height, vector<Coordinate>& contDivide)
{
	int i, j;
	TrackMatrix **tracker = new TrackMatrix *[row];
	Coordinate tmp_coordinates;

	for (i = 0; i < row; i++)
		tracker[i] = new TrackMatrix[coln];

	// Setting the border parameters in tracker matrix
	for (i = 0; i < row; i++)
	{
		tracker[i][0].setPac(true);
		tracker[i][coln-1].setAtl(true);
	}
	for (j = 0; j < coln; j++)
	{
		tracker[0][j].setPac(true);
		tracker[row-1][j].setAtl(true);
	}

	// Identifying the path based on input height condition and based on that we set the coordinates
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < coln; j++)
		{
			if (tracker[i][j].getVisit() == false)
				calculate_path(i, j, row, coln, tracker, inp_height);
		}
	}

	// Final output update
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < coln; j++)
		{
			if (tracker[i][j].getAtlflag() == true &&
				tracker[i][j].getPacflag() == true)
			{
				tmp_coordinates.setRow(i);
				tmp_coordinates.setColn(j);
				contDivide.push_back(tmp_coordinates);
			}
		}
	}

	// Releasing memory
	for (i = 0; i < row; i++)
		delete[] tracker[i];
	delete[] tracker;
}

void calculate_path(int row, int coln, int max_row, int max_coln, TrackMatrix **tracker, int **inp_height)
{
	tracker[row][coln].setVisit(true);
	bool rchPac, rchAtl;

	// Moving up
	if (row != 0 &&
		inp_height[row][coln] >= inp_height[row-1][coln])
	{
		if (tracker[row-1][coln].getVisit() != true)
			calculate_path(row - 1, coln, max_row, max_coln, tracker, inp_height);
		rchPac = tracker[row-1][coln].getPacflag() | tracker[row][coln].getPacflag();
		rchAtl = tracker[row-1][coln].getAtlflag() | tracker[row][coln].getAtlflag();
		tracker[row][coln].setPac(rchPac);
		tracker[row][coln].setAtl(rchAtl);
	}

	// Moving down
	if (row != (max_row - 1) &&
		inp_height[row][coln] >= inp_height[row+1][coln])
	{
		if (tracker[row+1][coln].getVisit() != true)
			calculate_path(row + 1, coln, max_row, max_coln, tracker, inp_height);
		rchPac = tracker[row+1][coln].getPacflag() | tracker[row][coln].getPacflag();
		rchAtl = tracker[row+1][coln].getAtlflag() | tracker[row][coln].getAtlflag();
		tracker[row][coln].setPac(rchPac);
		tracker[row][coln].setAtl(rchAtl);
	}

	// Moving left
	if (coln != 0 &&
		inp_height[row][coln] >= inp_height[row][coln - 1])
	{
		if (tracker[row][coln - 1].getVisit() != true)
			calculate_path(row, coln-1, max_row, max_coln, tracker, inp_height);
		rchPac = tracker[row][coln-1].getPacflag() | tracker[row][coln].getPacflag();
		rchAtl = tracker[row][coln-1].getAtlflag() | tracker[row][coln].getAtlflag();
		tracker[row][coln].setPac(rchPac);
		tracker[row][coln].setAtl(rchAtl);
	}

	// Moving right
	if (coln != (max_coln - 1) &&
		inp_height[row][coln] >= inp_height[row][coln+1])
	{
		if (tracker[row][coln+1].getVisit() != true)
			calculate_path(row, coln+1, max_row, max_coln, tracker, inp_height);
		rchPac = tracker[row][coln+1].getPacflag() | tracker[row][coln].getPacflag();
		rchAtl = tracker[row][coln+1].getAtlflag() | tracker[row][coln].getAtlflag();
		tracker[row][coln].setPac(rchPac);
		tracker[row][coln].setAtl(rchAtl);
	}
}
