#pragma once

#ifndef WALL_H
#define WALL_H

#include <memory>
#include <fstream>
#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class Wall
{
public:
	Wall(sf::Vector2f size, sf::Color color, sf::Vector2f pos);
	Wall();

	//void setSize(sf::Vector2f size);
	//void setPos(sf::Vector2f pos);

	void render(sf::RenderWindow& window);

private:
	// PRIVATE VARIABLES
	sf::RectangleShape wall;
};

#endif
