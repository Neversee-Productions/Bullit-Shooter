#pragma once
#include "Scenes\GameScene\Bullets\Bullet.h"

namespace bullets
{
	///
	/// @brief empowered bullet class.
	/// @author Sebastian Kruzel
	/// 
	/// Defines the empowered bullet class.
	/// A derived class from bullet.
	/// This bullet will shoot 3 projectiles
	/// 1 straight forward and 2 at a 30 degree offset
	/// 
	class Empowered :
		public Bullet
	{
	public:
		Empowered();
		static float getFireRate();
	private:
		/// <summary>
		/// @brief define a static constant fire rate.
		/// 
		/// 
		/// </summary>
		static const float s_FIRE_RATE;
	};
}