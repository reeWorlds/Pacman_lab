#include "MazeGenerator.h"

vector <vector <int> > MazeGenerator::gen1(int n, int m)
{
	vector <vector <int> > maze(n + 2, vector <int>(m + 2, 1));
	DSU dsu(n * m);

	vector <int > conns;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			conns.push_back(i * m + j);
		}
	}

	mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
	shuffle(conns.begin(), conns.end(), rng);
	
	for (auto pos : conns)
	{
		vector <pair<int, pair<int, int> > > neibs;
		int x = pos / m + 1;
		int y = pos % m + 1;

		if (x > 1 && maze[x - 1][y] == 0)
		{
			int num = (x - 2) * m + (y - 1);
			neibs.push_back({ dsu.getParent(num), {x - 1, y} });
		}
		if (x < n && maze[x + 1][y] == 0)
		{
			int num = x * m + (y - 1);
			neibs.push_back({ dsu.getParent(num), {x + 1, y} });
		}
		if (y > 1 && maze[x][y - 1] == 0)
		{
			int num = (x - 1) * m + (y - 2);
			neibs.push_back({ dsu.getParent(num), {x, y - 1} });
		}
		if (y < m && maze[x][y + 1] == 0)
		{
			int num = (x - 1) * m + y;
			neibs.push_back({ dsu.getParent(num), {x, y + 1} });
		}

		if (neibs.size() == 0)
		{
			maze[x][y] = 0;
		}
		else
		{
			int allDiff = 1;
			for (int i = 0; i < neibs.size(); i++)
			{
				for (int j = i + 1; j < neibs.size(); j++)
				{
					if (neibs[i].first == neibs[j].first)
					{
						allDiff = 0;
					}
				}
			}

			if (allDiff == 1)
			{
				maze[x][y] = 0;

				for (int i = 0; i < neibs.size(); i++)
				{
					int x2 = neibs[i].second.first, y2 = neibs[i].second.second;
					int pos2 = (x2 - 1) * m + (y2 - 1);

					dsu.merge(pos, pos2);
				}
			}
		}
	}

	shuffle(conns.begin(), conns.end(), rng);

	for (auto pos : conns)
	{
		vector <pair<int, pair<int, int> > > neibs;
		int x = pos / m + 1;
		int y = pos % m + 1;

		if (maze[x][y] == 0)
		{
			continue;
		}

		if (x > 1 && maze[x - 1][y] == 0)
		{
			int num = (x - 2) * m + (y - 1);
			neibs.push_back({ dsu.getParent(num), {x - 1, y} });
		}
		if (x < n && maze[x + 1][y] == 0)
		{
			int num = x * m + (y - 1);
			neibs.push_back({ dsu.getParent(num), {x + 1, y} });
		}
		if (y > 1 && maze[x][y - 1] == 0)
		{
			int num = (x - 1) * m + (y - 2);
			neibs.push_back({ dsu.getParent(num), {x, y - 1} });
		}
		if (y < m && maze[x][y + 1] == 0)
		{
			int num = (x - 1) * m + y;
			neibs.push_back({ dsu.getParent(num), {x, y + 1} });
		}

		if (neibs.size() == 0)
		{
			_ASSERT(neibs.size() == 0);
		}
		else
		{
			int cntDiff = 0;
			for (int i = 0; i < neibs.size(); i++)
			{
				for (int j = i + 1; j < neibs.size(); j++)
				{
					if (neibs[i].first != neibs[j].first)
					{
						cntDiff++;
					}
				}
			}

			if (cntDiff > 0)
			{
				maze[x][y] = 0;

				for (int i = 0; i < neibs.size(); i++)
				{
					int x2 = neibs[i].second.first, y2 = neibs[i].second.second;
					int pos2 = (x2 - 1) * m + (y2 - 1);

					dsu.merge(pos, pos2);
				}
			}
		}
	}

	return maze;
}

void MazeGenerator::g2_dfs(vector <vector <int> >& maze, int n, int m,
	int x, int y, int px, int py, mt19937& rng)
{
	if (x == 0 || x == n + 1 || y == 0 || y == m + 1)
	{
		return;
	}
	if (maze[x][y] == 0)
	{
		return;
	}

	int isOk = 1;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (maze[x + i][y + j] == 0 && (abs(x + i - px) + abs(y + j - py)) > 1)
			{
				isOk = 0;

				break;
			}
		}
	}

	if (isOk == 0)
	{
		return;
	}

	maze[x][y] = 0;

	vector <pair<int, int> > nxt;
	nxt.push_back({ x - 1, y });
	nxt.push_back({ x + 1, y });
	nxt.push_back({ x, y - 1 });
	nxt.push_back({ x, y + 1 });

	shuffle(nxt.begin(), nxt.end(), rng);

	for (auto it : nxt)
	{
		g2_dfs(maze, n, m, it.first, it.second, x, y, rng);
	}
}

vector <vector <int> > MazeGenerator::gen2(int n, int m)
{
	vector <vector <int> > maze(n + 2, vector <int>(m + 2, 1));

	mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

	g2_dfs(maze, n, m, rng() % n + 1, rng() % m + 1, -1, -1, rng);

	return maze;
}

vector <vector <int> > MazeGenerator::gen3(int n, int m)
{
	vector <vector <int> > maze(n + 2, vector <int>(m + 2, 1));

	mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

	set<pair<int, pair<pair<int, int>, pair<int, int> > > > q;

	q.insert({ (int)rng(), { {rng() % n + 1, rng() % m + 1},{-1, -1} } });

	while (q.size() > 0)
	{
		auto inf = *q.begin();
		q.erase(q.begin());

		int x = inf.second.first.first, y = inf.second.first.second;
		int px = inf.second.second.first, py = inf.second.second.second;

		if (x == 0 || x == n + 1 || y == 0 || y == m + 1)
		{
			continue;
		}
		if (maze[x][y] == 0)
		{
			continue;
		}

		int isOk = 1;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (maze[x + i][y + j] == 0 && (abs(x + i - px) + abs(y + j - py)) > 1)
				{
					isOk = 0;

					break;
				}
			}
		}

		if (isOk == 0)
		{
			continue;
		}

		maze[x][y] = 0;

		vector <pair<int, int> > nxt;
		nxt.push_back({ x - 1, y });
		nxt.push_back({ x + 1, y });
		nxt.push_back({ x, y - 1 });
		nxt.push_back({ x, y + 1 });

		shuffle(nxt.begin(), nxt.end(), rng);

		for (auto it : nxt)
		{
			q.insert({ (int)rng(),{ {it.first, it.second}, {x, y} } });
		}
	}

	return maze;
}