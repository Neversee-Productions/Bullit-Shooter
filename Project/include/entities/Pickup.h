#ifndef PICKUP_H
#define PICKUP_H

#include <string>
#include <memory>
#include "SFML\Graphics.hpp"
#include "Thor\Animations.hpp"
#include "Player\Bullets\BulletTypes.h"
#include "tinyheaders\tinyc2.h"
#include "system\Window.h"

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

		/// 
		/// @author Sebastian Kruzel
		/// @brief define the pickup effect.
		/// 
		/// 
		/// 
		struct Effect
		{
			struct Texture
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

			struct Animation
			{
				/// <summary>
				/// @brief Defines the ID of the animation.
				/// 
				/// 
				/// </summary>
				std::string m_id = "";

				/// <summary>
				/// @brief Defines the duration of the animation.
				/// 
				/// 
				/// </summary>
				sf::Time m_duration;

				/// <summary>
				/// @brief Defines the origin of the animation frames.
				/// 
				/// 
				/// </summary>
				sf::Vector2f m_origin;

				/// <summary>
				/// @brief Defines shared pointer to our animation's frames.
				/// 
				/// 
				/// </summary>
				std::shared_ptr<thor::FrameAnimation> m_sptrFrames = nullptr;

				/// <summary>
				/// @brief Defines shared pointer to our animation's texture.
				/// 
				/// 
				/// </summary>
				std::shared_ptr<sf::Texture> m_sptrTexture = nullptr;
			};

			/// <summary>
			/// 
			/// </summary>
			Texture m_texture;

			/// <summary>
			/// 
			/// </summary>
			Animation m_animation;
		};

		Effect m_effect;
	};
	Pickup();
	Pickup(std::shared_ptr<Resources> resources,sf::Vector2f position, sf::Vector2f size, BulletTypes const & pickupType);
	void update();
	void draw(Window & window, const float & deltaTime);
	void spawn(sf::Vector2f const & position, sf::Vector2f const & size, BulletTypes const & pickupType);
	void setRightPosition(sf::Vector2f pos);
	void setLeftPosition(sf::Vector2f pos);
	sf::Vector2f const & getRightPosition() const;
	sf::Vector2f const & getLeftPosition() const;
	void setSize(sf::Vector2f size);
	sf::Vector2f const getSize() const;
	void setRightVelocity(sf::Vector2f vel);
	void setLeftVelocity(sf::Vector2f vel);
	bool const isActive() const;
	void setActive(bool active);
	void setEffectAlpha(float alpha);
	void fadeOutEffect();

private:
	/// <summary>
	/// @brief Define shared pointer to resources.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<Resources> m_resources;

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
	/// @brief defines the sprite that effect is applied onto.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_effectSprite;

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

	/// <summary>
	/// @brief defines the thor animator.
	/// 
	/// 
	/// </summary>
	thor::Animator<sf::Sprite, std::string> m_animator;
};

#endif // !PICKUP_H