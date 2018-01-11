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
		void hit() override;
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
#endif // ! BULLETSTANDARD_H