#ifndef BULLET_H
#define BULLET_H

#include "SFML\Graphics.hpp"
#include "Window.h"
#include "BulletTypes.h"
#include "Thor\Animations.hpp"
#include "Thor\Math.hpp"
#include <memory>

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

		/// <summary>
		/// @brief Determines the type of thor animator used with bullet.
		/// 
		/// 
		/// </summary>
		typedef thor::Animator<sf::RectangleShape, std::string> LoopAnimator;

		/// <summary>
		/// @brief Defines alias for bullet animation frames.
		/// 
		/// 
		/// </summary>
		typedef thor::FrameAnimation BulletFrames;

		struct Resources
		{
			/// 
			/// @author Rafael Plugge
			/// @brief Determines a pair with the animation and its id.
			/// 
			/// 
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
				std::shared_ptr<BulletFrames> m_sptrFrames = nullptr;

				/// <summary>
				/// @brief Defines shared pointer to our animation's texture.
				/// 
				/// 
				/// </summary>
				std::shared_ptr<sf::Texture> m_sptrTexture = nullptr;
			};

			/// <summary>
			/// @brief Defines a shared pointer to the bullet loop animation.
			/// 
			/// 
			/// </summary>
			std::shared_ptr<Animation> m_sptrLoopAnimation = nullptr;

			/// <summary>
			/// @brief Defines a shared pointer to the bullet impact animation.
			/// 
			/// 
			/// </summary>
			std::shared_ptr<Animation> m_sptrImpactAnimation = nullptr;
		};

	public:
		Bullet();
		virtual void update();
		virtual void draw(Window & window, const float & deltaTime);
		tinyh::c2AABB getCollisionRect();
		virtual void setActive(bool active);
		void updateBox();
		void setPosition(const sf::Vector2f& pos);
		void setAngle(const float& angle);
		void updateVelocityVector();
		bool isActive() const;
		virtual bool checkCircleCollision(const tinyh::c2Circle & other);
		const float & getDamage();

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
		/// @brief define damage of bullet.
		/// 
		/// 
		/// </summary>
		float m_damage;

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
