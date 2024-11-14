#pragma once

#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <memory>
#include <fstream>
#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include "../Node/Node.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "../Wall/Wall.h"

class SystemState
{
public:
	// CONSTRUCTOR
	SystemState();

	// ACCESSORS
	const bool running() const;

	// PUBLIC FUNCTIONS
	void pollEvents();
	void update();
	void render();

	void getFastestPath();
	void updateWalls();

private:
	// PRIVATE VARIABLES
	std::unique_ptr<sf::RenderWindow> window;
	sf::VideoMode videoMode;
	sf::Event ev;
	
	int map[12][16] =
	{
		{0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 3, 0, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 2, 0, 0},
		{0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0},
		{0, 2, 0, 0, 0, 2, 0, 2, 2, 2, 2, 2, 0, 2, 0, 0},
		{0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 0, 2, 0, 0},
		{0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 2, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
		{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	std::vector<Wall> walls;
	std::vector<sf::CircleShape> pois;

	// PRIVATE FUNCTIONS
	std::vector<std::pair<int, int>> reconstructPath(Node* endNode);

	std::pair<int, int> getStartPosition();
	std::pair<int, int> getEndPosition();

	bool isValidMove(int x, int y);

	void initVariables();
	void initWindow();
};

#endif
