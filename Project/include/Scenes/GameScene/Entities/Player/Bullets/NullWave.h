#ifndef NULLWAVE_H
#define NULLWAVE_H

#include "Bullet.h"

namespace bullets
{
	class NullWave :
		public Bullet
	{
	public:
		NullWave();
		void update() override;
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
#endif // !NULLWAVE_H


