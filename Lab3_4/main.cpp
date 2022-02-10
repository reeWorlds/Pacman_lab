#include "includes.h"

#include "MazeGenerator.h"
#include "PathFinder.h"
#include "Drawer.h"

void testPathFindingSpeed()
{
	auto maze = MazeGenerator::gen1(100, 100);
	vector <tuple<int, int, int, int> > st_en;

	for (int i = 0; i < 10000; i++)
	{
		auto [x1, y1, x2, y2] = PathFinder::getStartEnd(maze, 100, 100);
		st_en.push_back({ x1, y1, x2, y2 });
	}

	vector <pair<int, int> > path;
	vector <pair<int, int> > wrongCell;
	vector <pair<int, int> > unvisitedCells;
	
	int sumPath1 = 0, sumWrong1 = 0, sumUnvisited1 = 0;
	auto t_st1 = chrono::high_resolution_clock::now();
	for (auto it : st_en)
	{
		auto [x1, y1, x2, y2] = it;
		path.clear();
		wrongCell.clear();
		unvisitedCells.clear();

		PathFinder::gen1(maze, 100, 100, x1, y1, x2, y2, path, wrongCell, unvisitedCells);

		sumPath1 += path.size();
		sumWrong1 += wrongCell.size();
		sumUnvisited1 += unvisitedCells.size();
	}
	auto t_en1 = chrono::high_resolution_clock::now();

	int sumPath2 = 0, sumWrong2 = 0, sumUnvisited2 = 0;
	auto t_st2 = chrono::high_resolution_clock::now();
	for (auto it : st_en)
	{
		auto [x1, y1, x2, y2] = it;
		path.clear();
		wrongCell.clear();
		unvisitedCells.clear();

		PathFinder::gen2(maze, 100, 100, x1, y1, x2, y2, path, wrongCell, unvisitedCells);

		sumPath2 += path.size();
		sumWrong2 += wrongCell.size();
		sumUnvisited2 += unvisitedCells.size();
	}
	auto t_en2 = chrono::high_resolution_clock::now();

	chrono::duration<double> dur;

	cout.precision(5);
	dur = t_en1 - t_st1;
	cout << "Greedy path finder time = " << dur.count() << "\n";
	cout << "Stats: sum of paths = " << sumPath1 << ", sum of wrong cells = " << sumWrong1
		<< ", sum of unvisited cells = " << sumUnvisited1 << "\n\n";
	dur = t_en2 - t_st2;
	cout << "A* path finder time = " << dur.count() << "\n";
	cout << "Stats: sum of paths = " << sumPath2 << ", sum of wrong cells = " << sumWrong2
		<< ", sum of unvisited cells = " << sumUnvisited2 << "\n\n";

	/*
	Greedy path finder time = 3.4281
	Stats: sum of paths = 1538520, sum of wrong cells = 2958285, sum of unvisited cells = 485678

	A* path finder time = 16.667
	Stats: sum of paths = 1337880, sum of wrong cells = 13496642, sum of unvisited cells = 371721
	*/
}

int main()
{
	//testPathFindingSpeed();

	Drawer d;

	d.show(25, 40);

	return 0;
}