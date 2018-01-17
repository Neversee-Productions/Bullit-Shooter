#ifndef BULLET_H
#define BULLET_H

#include "SFML\Graphics.hpp"
#include "Window.h"
#include "BulletTypes.h"
#include "Thor\Math.hpp"

namespace bullets
{
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
		virtual void update();
		virtual void draw(Window & window, const float & deltaTime);
		tinyh::c2AABB getCollisionRect();
		virtual void setActive(bool active);
		virtual void updateBox();
		virtual void setPosition(const sf::Vector2f& pos);
		void setAngle(const float& angle);
		void updateVelocityVector();
		bool isActive() const;
		virtual bool checkCircleCollision(const tinyh::c2Circle & other);
		virtual const float & getDamage() = 0;

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

		/// <summary>
		/// @brief velocity of the bullet
		/// 
		/// 
		/// </summary>
		sf::Vector2f m_velocity;

		/// <summary>
		/// @brief speed of the bullet
		/// 
		/// 
		/// </summary>
		float m_speed;

		/// <summary>
		/// @brief pi/180 convert degrees to radians
		/// 
		/// 
		/// </summary>
		static double const DEG_TO_RAD;

		/// <summary>
		/// @brief angle at which bullet fires.
		/// 
		/// 
		/// </summary>
		float m_angle;

		/// <summary>
		/// @brief constant reference to update delta time.
		/// 
		/// 
		/// </summary>
		const float & UPDATE_DT;

		sf::RectangleShape tempRect;
	};
}
#endif // !BULLET_H
