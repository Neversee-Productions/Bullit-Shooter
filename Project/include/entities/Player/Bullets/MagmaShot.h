#ifndef MAGMA_SHOT_H
#define MAGMA_SHOT_H
#include "Bullet.h"

namespace bullets
{
	///
	/// @brief MagmaShot bullet class.
	/// @author Sebastian Kruzel
	/// 
	/// Defines the MagmaShot bullet class. (aka LE PIZZA)
	/// A derived class from Bullet.
	/// This bullet explodes on impact dealing damage to all hit
	/// 
	class MagmaShot :
		public Bullet
	{
	public:
		MagmaShot();
		void update() override;
		static float getFireRate();
		void setActive(bool active) override;
		void explode(bool check);
		bool isExplosion();
		const float & getDamage() override;

		/// <summary>
		/// @brief Defines if the bullet is in an exploding state.
		/// 
		/// 
		/// </summary>
		bool m_explode;

		/// <summary>
		/// @brief define a static constant fire rate.
		/// 
		/// 
		/// </summary>
		static const float bullets::MagmaShot::s_FIRE_RATE;

		/// <summary>
		/// @brief determine rate of size change during explosion state.
		/// 
		///
		/// </summary>
		static const sf::Vector2f bullets::MagmaShot::s_SIZE_CHANGE;

		/// <summary>
		/// @brief defines default starting size.
		/// 
		/// 
		/// </summary>
		static const sf::Vector2f bullets::MagmaShot::s_DEFAULT_SIZE;

		/// <summary>
		/// @brief
		/// 
		/// 
		/// </summary>
		static float const s_MAX_SIZE;

	private:
		/// <summary>
		/// @brief defines damage.
		/// 
		/// 
		/// </summary>
		float m_damage;

	};

}

#endif // !MAGMA_SHOT_H
