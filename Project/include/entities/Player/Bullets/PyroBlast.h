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
		void explode(bool check);
		bool isExplosion();
		const float & getDamage() override;
		virtual bool checkCircleCollision(const tinyh::c2Circle & other) final override;
		virtual bool checkAABBCollision(const tinyh::c2AABB & other) final override;

	private:
		void updateExplosionCircle();

		/// <summary>
		/// @brief define a static constant fire rate.
		/// 
		/// 
		/// </summary>
		static const float s_FIRE_RATE;

		/// <summary>
		/// @brief determine if should explode.
		/// 
		/// 
		/// </summary>
		bool m_explode;

		/// <summary>
		/// @brief defines damage.
		/// 
		/// 
		/// </summary>
		float m_damage;

		/// <summary>
		/// @brief defines the collsiion circle of the explosion.
		/// 
		/// 
		/// </summary>
		tinyh::c2Circle m_explosionCircleCollider;
	};
}

#endif // !PYROBLAST_H

