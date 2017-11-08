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

	/// <summary>
	/// @brief Represents the ship.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_shipRect;
};

#endif SHIP_H