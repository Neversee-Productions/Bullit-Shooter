#ifndef  BULLETSTANDARD_H
#define BULLETSTANDARD_H

#include "Bullet.h"

namespace bullets
{

	///
	/// @brief standard bullet class.
	/// @author Sebastian Kruzel
	/// 
	/// Defines the standard bullet class.
	/// A derived class from bullet.
	/// 
	class Standard :
		public Bullet
	{
	public:
		Standard();
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
#endif // ! BULLETSTANDARD_H