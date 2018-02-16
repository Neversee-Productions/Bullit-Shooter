#ifndef SHIELD_H
#define SHIELD_H

#include "SFML\Graphics\CircleShape.hpp"
#include "system\Window.h"
///
/// @brief Shield class.
/// @author Sebastian Kruzel
/// 
/// Defines the shield class.
/// This class will create the shield which is like the players health.
/// 
class Shield
{
public:
	Shield(sf::Vector2f position, float radius);
	void update();
	void draw(Window & window, const float & deltaTime);
	void setPosition(sf::Vector2f pos);
	void decrementShield(float dmg);
	const sf::CircleShape& getCircleShape();
	const tinyh::c2Circle& getCollisionCircle();
	const float& getHealth();
	bool const & isInvulnerable();

private:

	/// <summary>
	/// @brief Define position on screen.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_position;

	/// <summary>
	/// @brief Defines the shape.
	/// 
	/// 
	/// </summary>
	sf::CircleShape m_circle;

	/// <summary>
	/// @brief Defines health of the shield.
	/// 
	/// 
	/// </summary>
	float m_health;

	/// <summary>
	/// @brief check mark for vulnerability.
	/// 
	/// 
	/// </summary>
	bool m_invulnerable;

	/// <summary>
	/// @brief Define frames to be invurnerable.
	/// 
	/// 
	/// </summary>
	static const float INVULNERABILITY_FRAMES;

	/// <summary>
	/// @brief Define time that invulnerability was active.
	/// 
	/// 
	/// </summary>
	float m_invulnTimer;

	/// <summary>
	/// @brief Defines the collision circle of the shield.
	/// 
	/// 
	/// </summary>
	tinyh::c2Circle m_collisionCircle;
};

#endif // !SHIELD_H