#pragma once

#include "includes.h"

class PathFinder
{
	static double dist(int x1, int y1, int x2, int y2);

public:

	static tuple<int, int, int, int> getStartEnd(vector <vector <int> >& maze, int n, int m);

	static void gen1(vector <vector <int> >& maze, int n, int m, int stX, int stY, int enX, int enY,
		vector <pair<int, int> >& path, vector <pair<int, int> >& wrongCell,
		vector <pair<int, int> >& unvisitedCells);

	static void gen2(vector <vector <int> >& maze, int n, int m, int stX, int stY, int enX, int enY,
		vector <pair<int, int> >& path, vector <pair<int, int> >& wrongCell,
		vector <pair<int, int> >& unvisitedCells);
};