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
			void updateState();
			bool checkState();
			void updateSpeed();
			void updatePosition();

		private: // Private member variables
			/// <summary>
			/// @brief Radius of collision circle within the charge.
			/// 
			/// 
			/// </summary>
			float const m_ATTACK_RADIUS;

			/// <summary>
			/// @brief Speed of initial charge.
			/// 
			/// 
			/// </summary>
			float const m_CHARGE_SPEED;

			/// <summary>
			/// @brief Amount by which speed is decreased per second.
			/// 
			/// 
			/// </summary>
			float const m_DECCELERATION;

			/// <summary>
			/// @brief Amount of speed that is consider low enough.
			/// 
			/// This determines how slow the ai needs to be before
			/// changing back to seek state.
			/// </summary>
			float const m_LOW_SPEED;

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