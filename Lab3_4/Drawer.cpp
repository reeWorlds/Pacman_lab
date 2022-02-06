#include "Drawer.h"

Drawer::Drawer()
{
	cellTexture[0].loadFromFile("Textures/white.png");
	cellTexture[1].loadFromFile("Textures/black.png");
	cellTexture[2].loadFromFile("Textures/green.png");
	cellTexture[3].loadFromFile("Textures/yellow.png");
	cellTexture[4].loadFromFile("Textures/light.png");

	foodTexture.loadFromFile("Textures/food.png");

	pacmanTexture[0].loadFromFile("Textures/pacman0.png");
	pacmanTexture[1].loadFromFile("Textures/pacman1.png");
	pacmanTexture[2].loadFromFile("Textures/pacman2.png");
	pacmanTexture[3].loadFromFile("Textures/pacman3.png");

	cellSprite[0].setTexture(cellTexture[0]);
	cellSprite[1].setTexture(cellTexture[1]);
	cellSprite[2].setTexture(cellTexture[2]);
	cellSprite[3].setTexture(cellTexture[3]);
	cellSprite[4].setTexture(cellTexture[4]);

	foodSprite.setTexture(foodTexture);

	pacmanSprite.setTexture(pacmanTexture[1]);
}

void Drawer::setMaze(int mazeType)
{
	if (mazeType == 0)
	{
		maze = MazeGenerator::gen1(n, m);
		_window->setTitle("Pacman maze=DSU");
	}
	else if (mazeType == 1)
	{
		maze = MazeGenerator::gen2(n, m);
		_window->setTitle("Pacman maze=DFS");
	}
	else if (mazeType == 2)
	{
		maze = MazeGenerator::gen3(n, m);
		_window->setTitle("Pacman maze=R_BFS");
	}
	else
	{
		_ASSERT(mazeType < 3);
	}
	_mazeType = mazeType;

	setPacman(0);
}

void Drawer::setPacman(int pacmanType)
{
	_ASSERT(pacmanType < 3);

	path.clear();
	wrongCells.clear();
	unvisitedCells.clear();
	pathPos = 0;

	if (pacmanType == 0)
	{
		return;
	}

	auto [stX, stY, enX, enY] = PathFinder::getStartEnd(maze, n, m);

	string name = "Pacman ";
	if (_mazeType == 0)
	{
		name += "maze=DSU ";
	}
	else if (_mazeType == 1)
	{
		name += "maze=DFS ";
	}
	else if (_mazeType == 2)
	{
		name += "maze=R_BFS ";
	}
	
	if(pacmanType == 1)
	{
		PathFinder::gen1(maze, n, m, stX, stY, enX, enY, path, wrongCells, unvisitedCells);
		name += "path=Greedy";
	}
	else
	{
		PathFinder::gen2(maze, n, m, stX, stY, enX, enY, path, wrongCells, unvisitedCells);
		name += "path=A*";
	}

	_window->setTitle(name);

	_pathType = pacmanType;

	pathPos = 0;
	pacmanSprite.setPosition(stY * cellSize, stX * cellSize);
	foodSprite.setPosition(enY * cellSize, enX * cellSize);
}

void Drawer::updatePacman(double timer)
{
	const double speed = 0.02;

	if (path.size() != 0)
	{
		if (pathPos + 1 < path.size())
		{
			timer *= speed;

			double len = (abs(path[pathPos].first * cellSize - pacmanSprite.getPosition().y) 
				+ abs(path[pathPos].second * cellSize - pacmanSprite.getPosition().x)) / cellSize;

			len += timer;

			while (len > 1.0)
			{
				len -= 1.0;
				pathPos++;
			}

			if (pathPos + 1 >= path.size())
			{
				return;
			}

			double newX = (path[pathPos].second + (path[pathPos + 1].second - path[pathPos].second) * len)
				* cellSize;
			double newY = (path[pathPos].first + (path[pathPos + 1].first - path[pathPos].first) * len)
				* cellSize;
			pacmanSprite.setPosition(newX, newY);

			if (path[pathPos].first + 1 == path[pathPos + 1].first)
			{
				pacmanSprite.setTexture(pacmanTexture[2]);
			}
			if (path[pathPos].first - 1 == path[pathPos + 1].first)
			{
				pacmanSprite.setTexture(pacmanTexture[0]);
			}
			if (path[pathPos].second + 1 == path[pathPos + 1].second)
			{
				pacmanSprite.setTexture(pacmanTexture[1]);
			}
			if (path[pathPos].second - 1 == path[pathPos + 1].second)
			{
				pacmanSprite.setTexture(pacmanTexture[3]);
			}
		}
	}
}

bool Drawer::switchEvent(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::Closed)
	{
		return false;
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
	{
		setMaze(0);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
	{
		setMaze(1);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
	{
		setMaze(2);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
	{
		setPacman(1);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5)
	{
		setPacman(2);
	}

	return true;
}

void Drawer::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);

	for (int i = 0; i < maze.size(); i++)
	{
		for (int j = 0; j < maze[i].size(); j++)
		{
			if (maze[i][j] == 0)
			{
				cellSprite[0].setPosition(j * cellSize, i * cellSize);
				window.draw(cellSprite[0]);
			}
			else
			{
				cellSprite[1].setPosition(j * cellSize, i * cellSize);
				window.draw(cellSprite[1]);
			}
		}
	}

	if (path.size() != 0)
	{
		for (auto c : path)
		{
			cellSprite[2].setPosition(c.second * cellSize, c.first * cellSize);
			window.draw(cellSprite[2]);
		}
		for (auto c : wrongCells)
		{
			cellSprite[3].setPosition(c.second * cellSize, c.first * cellSize);
			window.draw(cellSprite[3]);
		}
		for (auto c : unvisitedCells)
		{
			cellSprite[4].setPosition(c.second * cellSize, c.first * cellSize);
			window.draw(cellSprite[4]);
		}

		if (pathPos + 1 != path.size())
		{
			window.draw(foodSprite);
		}
		window.draw(pacmanSprite);
	}

	window.display();
}

void Drawer::process(sf::RenderWindow& window)
{
	timer = 0;

	while (window.isOpen())
	{
		timer += clock.getElapsedTime().asMicroseconds() / 1000.0;
		clock.restart();

		if (window.pollEvent(event))
		{
			if (!switchEvent(event, window))
			{
				window.close();
			}
		}

		if (timer > 15.0)
		{
			updatePacman(timer);

			draw(window);

			timer = 0.0;
		}
	}
}

void Drawer::show(int n, int m, int mazeType, int playPacman, int maxWidth, int maxHeight)
{
	this->n = n;
	this->m = m;

	cellSize = cellTexture[0].getSize().x;
	cellScale = 1.0;
	while ((n + 2) * cellSize > maxHeight || (m + 2) * cellSize > maxWidth)
	{
		cellSize /= 2;
		cellScale /= 2.0;
	}
	cellSprite[0].setScale(cellScale, cellScale);
	cellSprite[1].setScale(cellScale, cellScale);
	cellSprite[2].setScale(cellScale, cellScale);
	cellSprite[3].setScale(cellScale, cellScale);
	cellSprite[4].setScale(cellScale, cellScale);
	foodSprite.setScale(cellScale, cellScale);
	pacmanSprite.setScale(cellScale, cellScale);

	globalWindowWidth = (m + 2) * cellSize;
	globalWindowHeight = (n + 2) * cellSize;

	sf::RenderWindow window(sf::VideoMode(globalWindowWidth, globalWindowHeight), "Pacman");
	_window = &window;

	setMaze(mazeType);

	window.setKeyRepeatEnabled(0);

	process(window);
}