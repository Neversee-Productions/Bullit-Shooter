#ifndef DEATHORB_H
#define DEATHORB_H

#include "Bullet.h"

namespace bullets
{
	///
	/// @brief DeathOrb class.
	/// @author Sebastian Kruzel
	/// 
	/// Defines the Death orb bullet.
	/// This bullet can pass through enemies
	/// 
	class DeathOrb :
		public Bullet
	{
	public:
		DeathOrb();
		static float getFireRate();
		void update() override;
		const float & getDamage() override;

	private:
		/// <summary>
		/// @brief define a static constant fire rate.
		/// 
		/// 
		/// </summary>
		static const float s_FIRE_RATE;

		/// <summary>
		/// @brief defines damage.
		/// 
		/// 
		/// </summary>
		float m_damage;
	};
}

#endif // !DEATHORB_H