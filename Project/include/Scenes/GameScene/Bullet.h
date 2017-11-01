#ifndef BULLET_H
#define BULLET_H

#include "SFML\Graphics.hpp"
#include "Window.h"

///
/// @brief Bullet class.
/// @author Sebastian Kruzel
/// 
/// Defines the abstract bullet.
/// This is a base class of all bullets.
/// 
class Bullet
{
public:
	Bullet();
	Bullet(sf::Vector2f position);
	virtual void update() abstract;
	void draw(Window & window, const float & deltaTime);

protected:
	/// <summary>
	/// @brief represents the position.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_position;

	/// <summary>
	/// @brief represents the bullet rectangle.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_bulletRect;

	/// <summary>
	/// @brief defines if the bullet is active or dead.
	/// 
	/// 
	/// </summary>
	bool m_active;
};
#endif // !BULLET_H
