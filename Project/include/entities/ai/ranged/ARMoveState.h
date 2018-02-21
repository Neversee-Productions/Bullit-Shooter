#ifndef AI_RANGED_MOVE_STATE_H
#define AI_RANGED_MOVE_STATE_H

// Project Includes
#include "AiRangedState.h"

namespace ai
{
	class AiRanged;

	namespace states
	{
		/// 
		/// @author Rafael Plugge
		/// @brief Ranged Ai's Move State.
		/// 
		/// 
		/// 
		class AiRangedMoveState : public AiRangedState
		{
		public: // Constructors/Destructor
			AiRangedMoveState(AiRanged * aiUnit);
			~AiRangedMoveState() = default;

		public: // Public Member Functions
			virtual void enter() final override;
			virtual void update() final override;
			virtual void exit() final override;
		public: // Public Member Variables
		protected: // Protected Member Functions
		protected: // Protected Member Variables
		private: // Private Member Functions
			void updateState(sf::Vector2f const & aiToDeploy);
		private: // Private Static Variables
			/// <summary>
			/// @brief Defines the max speed of the ai.
			/// 
			/// 
			/// </summary>
			static float const s_MAX_SPEED;
			/// <summary>
			/// @brief Defines the max turn rate of the ai.
			/// 
			/// 
			/// </summary>
			static float const s_MAX_TURN_RATE;
			/// <summary>
			/// @brief Defines the minimum distance that is required before leaving this state.
			/// 
			/// 
			/// </summary>
			static float const s_MIN_DISTANCE;
		private: // Private Member Variables
		};
	}
}

#include "AiRanged.h"

#endif // !AI_RANGED_MOVE_STATE_H