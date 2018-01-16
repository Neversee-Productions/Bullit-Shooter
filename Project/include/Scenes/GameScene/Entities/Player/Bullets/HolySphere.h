#ifndef HOLYSPHERE_H
#define HOLYSPHERE_H

#include "Bullet.h"

namespace bullets
{
	///
	/// @brief HolySphere bullet class.
	/// @author Sebastian Kruzel
	/// 
	/// Defines the HolySphere bullet class.
	/// A derived class from Bullet.
	/// This bullet gradually gets bigger untill it reaches its max size
	/// and then fades out
	/// 
	class HolySphere :
		public Bullet
	{
	public:

		/// 
		/// @author Rafael Plugge
		/// @brief HolySphere's resources.
		/// 
		/// Will resources specific to this bullet.
		/// @see Bullet::Resources
		/// 
		struct Resources : Bullet::Resources
		{
			Resources()
				: Bullet::Resources()
			{
				m_sptrImpactAnimation = nullptr;
			}
		};

	public:
		HolySphere();
		void update() override;
		static float getFireRate();
		void setActive(bool active) override;

		/// <summary>
		/// @brief how long to be active.
		/// 
		/// To be decremented when bullet reaches max size.
		/// </summary>
		float m_timeToLive;

		/// <summary>
		/// @brief define alpha of rectangle.
		/// 
		/// 
		/// </summary>
		float m_alpha;

		/// <summary>
		/// @brief define a static constant fire rate.
		/// 
		/// 
		/// </summary>
		static const float bullets::HolySphere::s_FIRE_RATE;

		/// <summary>
		/// @brief defines a static constant maximum size.
		/// 
		/// 
		/// </summary>
		static const float bullets::HolySphere::s_MAX_SIZE;

		/// <summary>
		/// @brief defines how much to grow every cycle.
		/// 
		/// 
		/// </summary>
		static const sf::Vector2f bullets::HolySphere::s_SIZE_CHANGE;

		/// <summary>
		/// @brief defines default starting size.
		/// 
		/// 
		/// </summary>
		static const sf::Vector2f bullets::HolySphere::s_DEFAULT_SIZE;

		/// <summary>
		/// @brief defines dafault time to live value.
		/// 
		/// 
		/// </summary>
		static const float bullets::HolySphere::s_DEF_TTL;

		/// <summary>
		/// @brief define how much should alpha decrease by.
		/// 
		/// 
		/// </summary>
		static const float bullets::HolySphere::s_ALPHA_DECREASE;

		/// <summary>
		/// @brief define minimum alpha before bullet becomes inactive.
		/// 
		/// 
		/// </summary>
		static const float bullets::HolySphere::s_MIN_ALPHA;

	};
}
#endif // !HOLYSPHERE_H
