#ifndef NAPALMSPHERE_H
#define NAPALMSPHERE_H

#include "Bullet.h"
namespace bullets
{
	///
	/// @brief NapalmSphere class.
	/// @author Sebastian Kruzel
	/// 
	/// Defines a Napalm Shpere.
	/// This bullet remains on impact for 3 seconds causing damage
	/// to everything that hits it.
	/// 
	class NapalmSphere :
		public Bullet
	{
	public:
		NapalmSphere();
		static float getFireRate();
		void update() override;
		void setActive(bool active) override;
		void explode(bool check);
		const float & getDamage() override;

	private:
		/// <summary>
		/// @brief define a static constant fire rate.
		/// 
		/// 
		/// </summary>
		static const float s_FIRE_RATE;

		/// <summary>
		/// @brief determine a default size.
		/// 
		/// 
		/// </summary>
		static const sf::Vector2f s_DEFAULT_SIZE;

		/// <summary>
		/// @brief determine the cloud size.
		/// 
		/// 
		/// </summary>
		static const sf::Vector2f s_CLOUD_SIZE;

		/// <summary>
		/// @brief defines if bullet is to explode.
		/// 
		/// 
		/// </summary>
		bool m_explode;
		
		/// <summary>
		/// @brief determine how long the bullet was stationary.
		/// 
		/// 
		/// </summary>
		float m_timeAlive;

		/// <summary>
		/// @brief defines damage.
		/// 
		/// 
		/// </summary>
		float m_damage;
	};
}

#endif // !NAPALMSPHERE_H
