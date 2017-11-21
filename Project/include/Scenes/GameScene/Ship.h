#ifndef SHIP_H
#define SHIP_H

#include "SFML\Graphics\RectangleShape.hpp"
#include "Window.h"

///
/// @brief Ship class.
/// @author Sebastian Kruzel
/// 
/// Defines the ship class.
/// 
class Ship
{
public:
	Ship();
	void draw(Window & window, const float & deltaTime);
	void moveUp();
	void moveDown();
	void update();
	const sf::Vector2f & getShipRect();

private:
	/// <summary>
	/// @brief Represents the ship.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_shipRect;

	/// <summary>
	/// @brief define players speed.
	/// 
	/// 
	/// </summary>
	float m_speed;

	/// <summary>
	/// @brief define position.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_position;
};

#endif SHIP_H