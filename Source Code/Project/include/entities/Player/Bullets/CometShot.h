#ifndef  COMETSHOT_H
#define COMETSHOT_H

#include "Bullet.h"
namespace bullets
{
	///
	/// @brief CometShot class.
	/// @author Sebastian Kruzel
	/// 
	/// Defines a Comet shot.
	/// This bullet applies a knockback to enemies.
	/// 
	class CometShot :
		public Bullet
	{
	public:
		CometShot();
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

	public:
		/// <summary>
		/// @brief define how much to knock back.
		/// 
		/// 
		/// </summary>
		static const float s_KNOCK_BACK;

	private:

		/// <summary>
		/// @brief defines damage.
		/// 
		/// 
		/// </summary>
		float m_damage;
	};
}


#endif // ! COMETSHOT_H
