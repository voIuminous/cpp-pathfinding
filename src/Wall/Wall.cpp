#include "Wall.h"

Wall::Wall(sf::Vector2f size, sf::Color color, sf::Vector2f pos)
{
	this->wall.setSize(size);
	this->wall.setFillColor(color);
	this->wall.setPosition(pos);
}

Wall::Wall()
{
	this->wall.setSize(sf::Vector2f(100, 5));
	this->wall.setFillColor(sf::Color::White);
	this->wall.setPosition(400, 500);
}

void Wall::render(sf::RenderWindow& window)
{
	window.draw(this->wall);
}
