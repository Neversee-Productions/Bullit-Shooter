#ifndef DEATHORB_H
#define DEATHORB_H

#include "Bullet.h"

namespace bullets
{
	///
	/// @brief DeathOrb class.
	/// @author Sebastian Kruzel
	/// 
	/// Defines the Death orb bullet.
	/// This bullet can pass through enemies
	/// 
	class DeathOrb :
		public Bullet
	{
	public:
		struct Resources : Bullet::Resources
		{
			Resources()
				: Bullet::Resources()
			{
				m_sptrImpactAnimation = nullptr;
			}
		};

	public:
		DeathOrb();
		static float getFireRate();
		void update() override;
		const float & getDamage() override;
		virtual bool const & isImpact() const final override;

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

		/// <summary>
		/// @brief Defines whether death orb can impact.
		/// 
		/// 
		/// </summary>
		bool const m_IS_IMPACT;
	};
}

#endif // !DEATHORB_H