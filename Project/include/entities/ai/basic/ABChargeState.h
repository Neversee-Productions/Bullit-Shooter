#ifndef AI_BASIC_ATTACK_STATE_H
#define AI_BASIC_ATTACK_STATE_H

// Project Includes
#include "AiBasic.h"
#include "AiBasicState.h"

namespace ai
{
	// Forward referencing
	class AiBasic;

	namespace states
	{

		/// 
		/// @author Rafael Plugge
		/// @brief Defines the attack state for the Basic Ai.
		/// @extends AiBasicState
		/// 
		/// 
		class AiBasicChargeState : public AiBasicState
		{
		public: // Constructors/Destructor
			AiBasicChargeState(AiBasic & aiUnit);
			~AiBasicChargeState() = default;

		public: // Public Member Functions
			virtual void enter() final override;
			virtual void update() final override;
			virtual void draw(Window & window, float const & deltaTime) final override;
			virtual void exit() final override;

		private: // Private member functions
			void updateCollision();

		private: // Private member variables
			/// <summary>
			/// @brief Radius of collision circle within the charge.
			/// 
			/// 
			/// </summary>
			float const m_ATTACK_RADIUS;

			/// <summary>
			/// @brief Amount by which speed is decreased per second.
			/// 
			/// 
			/// </summary>
			float const m_DECCELERATION;

			/// <summary>
			/// @brief Defines the attack collision.
			/// 
			/// 
			/// </summary>
			tinyh::c2Circle m_attackCollision;

			/// <summary>
			/// @brief Allows for rendering of our attack collision.
			/// 
			/// 
			/// </summary>
			sf::CircleShape m_attackHitShape;

		};

		/// <summary>
		/// @brief Alias for Basic Ai Charge State.
		/// 
		/// 
		/// </summary>
		typedef AiBasicChargeState Charge;

	}
}

#include "AiBasic.h"

#endif // !AI_BASIC_ATTACK_STATE_H