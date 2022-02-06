#pragma once

#include "includes.h"
#include "DSU.h"

class MazeGenerator
{
	static void g2_dfs(vector <vector <int> >& maze, int n, int m,
		int x, int y, int px, int py, mt19937& rng);

public:

	// DSU
	static vector <vector <int> > gen1(int n, int m);

	// DFS
	static vector <vector <int> > gen2(int n, int m);

	// randomized BFS
	static vector <vector <int> > gen3(int n, int m);

};