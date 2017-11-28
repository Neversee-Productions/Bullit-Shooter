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
	private:
		/// <summary>
		/// @brief define a static constant fire rate.
		/// 
		/// 
		/// </summary>
		static const float s_FIRE_RATE;
	};
}


#endif // ! COMETSHOT_H
