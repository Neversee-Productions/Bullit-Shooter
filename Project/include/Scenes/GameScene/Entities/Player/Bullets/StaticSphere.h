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
		void init(std::shared_ptr<Resources> sptrResources);
		void update() override;
		void draw(Window & window, const float & deltaTime) override;
		static float getFireRate();
		void setActive(bool active) override;
		const float & getDamage() override;
		void updateCollisionCircle();
		bool checkCircleCollision(const tinyh::c2Circle & other)final override;
		void setPosition(const sf::Vector2f & pos) final override;

	private:
		void setAnimation(std::string const & animationId) final override;

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
		/// @brief defines damage.
		/// 
		/// 
		/// </summary>
		float m_damage;

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

		/// <summary>
		/// @brief thor animator alias for our stasis animation.
		/// 
		/// 
		/// </summary>
		typedef thor::Animator<sf::CircleShape, std::string> StasisAnimator;

		/// <summary>
		/// @brief unique pointer to our loop thor animator.
		/// 
		/// Thor animator using our sfml rectangle shape as the
		/// template type for the animated type and std::string as the
		/// key for accessing the several animations the animator can play.
		/// 
		/// This animator will play our loop animation on the statis circle Shape.
		/// </summary>
		std::unique_ptr<StasisAnimator> m_uptrStasisAnimator;
	};
}
#endif // !STATICSPHERE_H


