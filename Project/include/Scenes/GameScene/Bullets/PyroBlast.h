#ifndef PYROBLAST_H
#define PYROBLAST_H

#include "Bullet.h"

namespace bullets 
{
	///
	/// @brief StaticSphere class.
	/// @author Sebastian Kruzel
	/// 
	/// Defines the Static sphere projectile.
	/// This projectile emits damaging pulses.
	/// 
	class PyroBlast :
		public Bullet
	{
	public:
		PyroBlast();
		void update() override;
		static float getFireRate();
		void setActive(bool active) override;
	private:
		/// <summary>
		/// @brief define a static constant fire rate.
		/// 
		/// 
		/// </summary>
		static const float s_FIRE_RATE;

		//DELETE TIME TO LIVE
		float TIMETOLIVE;

		/// <summary>
		/// @brief determine if should explode.
		/// 
		/// 
		/// </summary>
		bool m_explode;
	};
}

#endif // !PYROBLAST_H

