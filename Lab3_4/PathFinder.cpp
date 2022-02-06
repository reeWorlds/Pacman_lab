#include "PathFinder.h"

double PathFinder::dist(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
	//return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

tuple<int, int, int, int> PathFinder::getStartEnd(vector <vector <int> >& maze, int n, int m)
{
	mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

	int stX, stY, enX, enY;

	while (true)
	{
		stX = rng() % n + 1;
		stY = rng() % m + 1;

		if (maze[stX][stY] == 0)
		{
			break;
		}
	}

	while (true)
	{
		enX = rng() % n + 1;
		enY = rng() % m + 1;

		if (maze[enX][enY] == 0 && (stX != enX || stY != enY))
		{
			break;
		}
	}

	return { stX, stY, enX, enY };
}

void PathFinder::gen1(vector <vector <int> >& maze, int n, int m, int stX, int stY, int enX, int enY,
	vector <pair<int, int> >& path, vector <pair<int, int> >& wrongCell,
	vector <pair<int, int> >& unvisitedCells)
{
	map <pair<int, int>, pair<int, int> > parent;
	set <pair<pair<double, int>, pair<int, int> > > inf;

	mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

	parent[{stX, stY}] = { -1, -1 };
	inf.insert({ {dist(stX, stY, enX, enY), rng()}, {stX, stY} });

	while (parent.count({ enX, enY }) == 0)
	{
		auto [x, y] = inf.begin()->second;
		inf.erase(inf.begin());

		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				if (abs(dx) + abs(dy) != 1)
				{
					continue;
				}

				int tx = x + dx, ty = y + dy;

				if (maze[tx][ty] == 0 && parent.count({ tx, ty }) == 0)
				{
					parent[{tx, ty}] = { x, y };
					if (tx != enX || ty != enY)
					{
						inf.insert({ {dist(tx, ty, enX, enY), rng() }, {tx, ty} });
					}
				}
			}
		}
	}

	set <pair<int, int> > pathS, unvisitedS;
	pair<int, int> pos = { enX, enY };

	while (pos != make_pair(-1, -1))
	{
		path.push_back(pos);
		pathS.insert(pos);

		pos = parent[pos];
	}

	for (auto it : inf)
	{
		unvisitedCells.push_back(it.second);
		unvisitedS.insert(it.second);
	}

	reverse(path.begin(), path.end());

	for (auto c : parent)
	{
		if (pathS.find(c.first) == pathS.end() && unvisitedS.find(c.first) == unvisitedS.end())
		{
			wrongCell.push_back(c.first);
		}
	}
}

void PathFinder::gen2(vector <vector <int> >& maze, int n, int m, int stX, int stY, int enX, int enY,
	vector <pair<int, int> >& path, vector <pair<int, int> >& wrongCell,
	vector <pair<int, int> >& unvisitedCells)
{
	set <pair<pair<double, int>, pair<int, int> > > inf;
	map <pair<int, int>, int> type;
	map <pair<int, int>, int> dst;

	mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

	type[{stX, stY}] = 1;
	dst[{stX, stY}] = 0;
	inf.insert({ {dist(stX, stY, enX, enY), rng()}, {stX, stY} });

	while (dst.count({ enX, enY }) == 0)
	{
		auto [x, y] = inf.begin()->second;
		int myDst = dst[{x, y}];
		type[{x, y}] = 2;
		inf.erase(inf.begin());

		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				if (abs(dx) + abs(dy) != 1)
				{
					continue;
				}

				int tx = x + dx, ty = y + dy;

				if (maze[tx][ty] == 0 && (dst.count({ tx, ty }) == 0 || dst[{tx, ty}] > myDst + 1))
				{
					dst[{tx, ty}] = myDst + 1;
					type[{tx, ty}] = 1;
					if (tx != enX || ty != enY)
					{
						inf.insert({ {dist(tx, ty, enX, enY) + myDst + 1, rng() }, {tx, ty} });
					}
					else
					{
						type[{tx, ty}] = 2;
					}
				}
			}
		}
	}

	pair<int, int> pos = { enX, enY };
	path.push_back(pos);
	type[pos] = 3;

	while (pos != make_pair(stX, stY))
	{
		int myDst = dst[pos];
		vector <pair<int, int> > prNeibs;

		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				if (abs(dx) + abs(dy) != 1)
				{
					continue;
				}

				if (dst.count({ pos.first + dx, pos.second + dy }) != 0
					&& dst[{pos.first + dx, pos.second + dy}] == myDst - 1)
				{
					prNeibs.push_back({ pos.first + dx, pos.second + dy });
				}
			}
		}

		pos = prNeibs[rng() % prNeibs.size()];

		path.push_back(pos);
		type[pos] = 3;
	}

	reverse(path.begin(), path.end());

	for (auto c : type)
	{
		if (c.second == 1)
		{
			unvisitedCells.push_back(c.first);
		}
		else if (c.second == 2)
		{
			wrongCell.push_back(c.first);
		}
	}
}