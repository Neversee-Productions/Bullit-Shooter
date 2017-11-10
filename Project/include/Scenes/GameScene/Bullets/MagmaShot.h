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
		void explode(bool check);

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

	};

}

#endif // !MAGMA_SHOT_H
