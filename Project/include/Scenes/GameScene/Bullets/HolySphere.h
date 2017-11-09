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
	/// This bullet gradually gets bigger untill it reaches 2 times its size
	/// it disappears after 3 seconds
	/// 
	class HolySphere :
		public Bullet
	{
	public:
		HolySphere();
		void update() override;
		static float getFireRate();
		void setActive(bool active) override;

		/// <summary>
		/// @brief define a static constant fire rate.
		/// 
		/// 
		/// </summary>
		static const float bullets::HolySphere::s_FIRE_RATE;
	};
}
#endif // !HOLYSPHERE_H
