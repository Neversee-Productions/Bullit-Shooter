#ifndef FIREBLAST_H
#define FIREBLAST_H

#include "Bullet.h"

namespace bullets
{
	///
	/// @brief FireBlast bullet class.
	/// @author Sebastian Kruzel
	/// 
	/// Defines the FireBlast bullet class.
	/// A derived class from bullet.
	/// 
	class FireBlast :
		public Bullet
	{
	public:
		FireBlast();
		static float getFireRate();
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
#endif // !FIREBLAST_H