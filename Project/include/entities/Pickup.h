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
			/// @brief scale of this pickup.
			/// 
			/// 
			/// </summary>
			sf::Vector2f m_scale;

			/// <summary>
			/// @brief origin point of this pickup.
			/// 
			/// 
			/// </summary>
			sf::Vector2f m_origin;

			/// <summary>
			/// @brief Texture source rectangle.
			/// 
			/// 
			/// </summary>
			sf::IntRect m_frame;
		};

		/// <summary>
		/// @brief Alias for map of individual pickups.
		/// 
		/// 
		/// </summary>
		typedef std::map<BulletTypes, IndividualPickup> PickupMap;

		/// <summary>
		/// @brief represents all types of pickups.
		/// 
		/// 
		/// </summary>
		PickupMap m_pickups;
	};
	Pickup();
	Pickup(std::shared_ptr<Resources> resources,sf::Vector2f position, sf::Vector2f size, BulletTypes const & pickupType);
	void update();
	void draw(Window & window, const float & deltaTime);
	void setRightPosition(sf::Vector2f pos);
	void setLeftPosition(sf::Vector2f pos);
	sf::Vector2f const getRightPosition() const;
	sf::Vector2f const & getLeftPosition() const;
	void setSize(sf::Vector2f size);
	sf::Vector2f const getSize() const;
	void setRightVelocity(sf::Vector2f vel);
	void setLeftVelocity(sf::Vector2f vel);
	bool const isActive() const;
	void setActive(bool active);


private:
	/// <summary>
	/// @brief define texture.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<sf::Texture> m_texture;

	/// <summary>
	/// @brief define position on screen of right sprite.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_rightPosition;

	/// <summary>
	/// @brief define position on screen of left sprite.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_leftPosition;

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
	bool m_active;

	/// <summary>
	/// @brief sprite to draw that represents the pickup.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_rightSprite;

	/// <summary>
	/// @brief sprite to draw that represents the pickup.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_leftSprite;

	/// <summary>
	/// @brief define velocity.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_rightVelocity;

	/// <summary>
	/// @brief define velocity of the left pickup.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_leftVelocity;
};

#endif // !PICKUP_H