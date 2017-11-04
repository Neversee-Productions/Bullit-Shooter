#ifndef BULLET_H
#define BULLET_H

#include "SFML\Graphics.hpp"
#include "Window.h"
#include "BulletTypes.h"

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
	Bullet(sf::Vector2f position, BulletTypes type);
	virtual void update() abstract;
	void draw(Window & window, const float & deltaTime);
	tinyh::c2AABB getCollisionRect();
	void setActive(bool active);
	void updateBox();
	void setPosition(const sf::Vector2f& pos);
	bool isActive() const;
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

	/// <summary>
	/// @brief define the bullet type.
	/// 
	/// 
	/// </summary>
	BulletTypes m_type;

	/// <summary>
	/// @brief the collision box of bullet.
	/// 
	/// 
	/// </summary>
	tinyh::c2AABB m_bulletC2Rect;

};
#endif // !BULLET_H
