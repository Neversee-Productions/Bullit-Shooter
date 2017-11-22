#ifndef STATICSPHERE_H
#define STATICSPHERE_H

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
	class StaticSphere :
		public Bullet
	{
	public:
		StaticSphere();
		void update() override;
		void draw(Window & window, const float & deltaTime) override;
		static float getFireRate();
		void setActive(bool active) override;
		void updateCollisionCircle();
		bool checkCircleCollision(const tinyh::c2Circle & other)final override;
	private:
		/// <summary>
		/// @brief define a static constant fire rate.
		/// 
		/// 
		/// </summary>
		static const float s_FIRE_RATE;

		/// <summary>
		/// @brief determine if a pulse is triggered.
		/// 
		/// 
		/// </summary>
		bool m_pulse;

		/// <summary>
		/// @brief used to add a short delay between pulses.
		/// 
		/// 
		/// </summary>
		float m_pulseTimer;

		/// <summary>
		/// @brief defines the pulse circle.
		/// 
		/// 
		/// </summary>
		sf::CircleShape m_pulseCircle;

		/// <summary>
		/// @brief colider for the static circle.
		/// 
		/// 
		/// </summary>
		tinyh::c2Circle m_pulseCircleCollider;
	};
}
#endif // !STATICSPHERE_H


