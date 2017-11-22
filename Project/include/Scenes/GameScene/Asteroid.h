#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "SFML\Graphics.hpp"
#include "Window.h"
#include <stdlib.h>

///
/// @brief An asteroid entity class.
/// @author Sebastian Kruzel
/// 
/// This class will
/// 
class Asteroid
{
public:
	Asteroid();
	void update();
	void draw(Window & window, const float & deltaTime);
	void setVelocity(sf::Vector2f vel);
	void setActive(bool active);
	void updateCollisionCircle();
	void generateRandomVel();
	void generateRandomPos();
	void reuseAsteroid();
	void updateWindowCollisions();
	tinyh::c2Circle getCollisionCircle();
	void decrementHealth(float dmg);

private:
	/// <summary>
	/// @brief define rectangle to draw texture on.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_rectangle;

	/// <summary>
	/// @brief define asteroid shape.
	/// 
	/// 
	/// </summary>
	sf::CircleShape m_circle;

	/// <summary>
	/// @brief define the velocity of asteroid.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_velocity;

	/// <summary>
	/// @brief define the (central) position of the asteroid.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_position;

	/// <summary>
	/// @brief define if the asteroid is active.
	/// 
	/// 
	/// </summary>
	bool m_active;

	/// <summary>
	/// @brief define the collision circle.
	/// 
	/// 
	/// </summary>
	tinyh::c2Circle m_collisionCircle;

	/// <summary>
	/// @brief window collision box.
	/// 
	/// 
	/// </summary>
	tinyh::c2AABB m_windowC2Rect;

	/// <summary>
	/// @brief Define the health.
	/// 
	/// 
	/// </summary>
	float m_health;
};

#endif // !ASTEROIDS_H
