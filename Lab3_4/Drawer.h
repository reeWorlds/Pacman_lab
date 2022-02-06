#pragma once

#include "includes.h"
#include "MazeGenerator.h"
#include "PathFinder.h"

class Drawer
{
	int cellSize;
	double cellScale;
	int globalWindowWidth, globalWindowHeight;

	sf::Clock clock;
	double timer;
	sf::Event event;

	sf::RenderWindow* _window;

	sf::Texture cellTexture[5], foodTexture, pacmanTexture[4];
	sf::Sprite cellSprite[5], foodSprite, pacmanSprite;

	int n, m;
	vector <vector<int> > maze;

	int pathPos;
	vector <pair<int, int> > path;
	vector <pair<int, int> > wrongCells;
	vector <pair<int, int> > unvisitedCells;

	int _mazeType, _pathType;

	bool switchEvent(sf::Event event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	void process(sf::RenderWindow& window);

	void setMaze(int mazeType);
	void setPacman(int pacmanType);

	void updatePacman(double timer);

public:

	Drawer();

	void show(int n, int m, int mazeType = 0, int playPacman = 0,
		int maxWidth = 1900, int maxHeight = 1200);
};