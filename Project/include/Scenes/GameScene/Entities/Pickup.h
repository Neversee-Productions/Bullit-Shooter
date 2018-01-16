#ifndef PICKUP_H
#define PICKUP_H

#include <string>
#include <memory>
#include "SFML\Graphics.hpp"
#include "Player\Bullets\BulletTypes.h"
#include "tinyheaders\tinyc2.h"
#include "Window.h"

///
/// @brief Pickup class.
/// @author Sebastian Kruzel
/// 
/// Defines the pickup class.
/// This class will create a pickup that upgrades to new weapon.
/// 
class Pickup
{

public:
	///
	/// @author Sebastian Kruzel
	/// @brief Define resources for the pickup
	/// 
	/// 
	///
	struct Resources
	{
		/// 
		/// @author Sebastian Kruzel
		/// @brief determine which specific pickup this is.
		/// 
		/// 
		///
		struct IndividualPickup
		{
			/// <summary>
			/// @brief id of the pickup.
			/// 
			/// 
			/// </summary>
			std::string m_id = "";

			/// <summary>
			/// @brief define texture of the pickup.
			/// 
			/// 
			/// </summary>
			std::shared_ptr<sf::Texture> m_texture;

			/// <summary>
			/// @brief size of this pickup.
			/// 
			/// 
			/// </summary>
			sf::Vector2f m_size;

			/// <summary>
			/// @brief origin point of this pickup.
			/// 
			/// 
			/// </summary>
			sf::Vector2f m_origin;
		};

		/// <summary>
		/// @brief represents all types of pickups.
		/// 
		/// 
		/// </summary>
		std::map<BulletTypes,IndividualPickup> m_pickups;
	};
	Pickup();
	Pickup(/*std::shared_ptr<sf::Texture> texture,*/sf::Vector2f position, sf::Vector2f size);
	void update();
	void draw(Window & window, const float & deltaTime);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f const getPosition() const;
	void setSize(sf::Vector2f size);
	sf::Vector2f const getSize() const;
	void setVelocity(sf::Vector2f vel);


private:
	/// <summary>
	/// @brief define texture.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<sf::Texture> m_texture;

	/// <summary>
	/// @brief define position on screen.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_position;

	/// <summary>
	/// @brief size of the pickup.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_size;

	/// <summary>
	/// @brief origin of the texture.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_origin;

	/// <summary>
	/// @brief define the collision circle.
	/// 
	/// 
	/// </summary>
	tinyh::c2Circle m_collisionCircle;

	/// <summary>
	/// @brief define if pickup has been picked up.
	/// 
	/// 
	/// </summary>
	bool m_isPickedUp;

	/// <summary>
	/// @brief rectangle to draw that represents the pickup.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_rectangle;

	/// <summary>
	/// @brief define velocity.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_velocity;
};

#endif // !PICKUP_H