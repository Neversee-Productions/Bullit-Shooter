#ifndef AI_RANGED_SHOOT_STATE_H
#define AI_RANGED_SHOOT_STATE_H

// STD Includes
// Project Includes
#include "AiRangedState.h"

namespace ai
{
	class AiRanged;

	namespace states
	{
		/// 
		/// @brief Ranged Ai's Shoot state.
		/// @author Rafael Plugge
		/// 
		/// 
		/// 
		class AiRangedShootState : public ai::states::AiRangedState
		{
		public: // Constructors/Destructor
			AiRangedShootState(ai::AiRanged * aiUnit);
			~AiRangedShootState() = default;
		public: // Public Member Functions
			virtual void enter() final override;
			virtual void update() final override;
			virtual void exit() final override;
		public: // Public Member Variables
		protected: // Protected Member Functions
		protected: // Protected Member Variables
		private: // Private Member Functions
			void updateShooting(sf::Vector2f const & aiToPlayer);
			void updateTimer();
			void shoot(sf::Vector2f const & direction);
		private: // Private Static Variables
		private: // Private Member Variables
			/// <summary>
			/// @brief Tracks how long since last fired.
			/// 
			/// 
			/// </summary>
			sf::Time m_timer;
			/// <summary>
			/// @brief Determines whether the minimum angle of shooting.
			/// 
			/// 
			/// </summary>
			float const m_MIN_ANGLE;
			sf::Time const m_FIRE_RATE;
		};
	}
}

#include "AiRanged.h"

#endif // !AI_RANGED_DEPLOY_STATE_H