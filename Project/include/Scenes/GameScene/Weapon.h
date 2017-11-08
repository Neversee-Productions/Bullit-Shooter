#ifndef WEAPON_H
#define WEAPON_H

#include "Window.h"
#include "SFML\Graphics\RectangleShape.hpp"
#include "Bullets\BulletTypes.h"

///
/// @brief Weapon class.
/// @author Sebastian Kruzel
/// 
/// Defines the weapon class.
/// This class will create the Weapon.
/// 
class Weapon
{
public:
	Weapon(sf::Vector2f position = sf::Vector2f(0.0f, 0.0f));
	void draw(Window & window, const float & deltaTime);

	/// <summary>
	/// @brief define the weapon rectangle.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_weaponRect;

	/// <summary>
	/// @brief hold the type of the current bullet.
	/// 
	/// 
	/// </summary>
	BulletTypes m_currentBullet;
};
#endif // !WEAPON_H