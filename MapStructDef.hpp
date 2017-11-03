/*
 * MapStructDef.hpp
 *
 *  Created on: Nov 3, 2017
 *      Author: jjayakumar
 */
#include <vector>
#ifndef MAPSTRUCTDEF_HPP_
#define MAPSTRUCTDEF_HPP_

// TrackMatrix
class TrackMatrix
{
	bool rchPac;
	bool rchAtl;
	bool visited;

public:
	TrackMatrix() : rchPac(false), rchAtl(false), visited(false){}
	void setPac(bool flag);
	void setAtl(bool flag);
	void setVisit(bool flag);
	bool getPacflag();
	bool getAtlflag();
	bool getVisit();

};

class Coordinate
{
	int row;
	int coln;

public:
	Coordinate():row(0), coln(0){}
	void setRow(int row);
	void setColn(int coln);
	int getRow();
	int getColn();

};

void setContDivide(int row, int coln, int **inp_height, std::vector<Coordinate> &contDivide);

#endif /* MAPSTRUCTDEF_HPP_ */
