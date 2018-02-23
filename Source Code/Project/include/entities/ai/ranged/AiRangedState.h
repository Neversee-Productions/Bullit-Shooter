#ifndef AI_RANGED_STATE_H
#define AI_RANGED_STATE_H

// STD Includes
#include <random>
// Project Includes
#include "entities\ai\AiBaseState.h"

namespace ai
{
	class AiRanged;

	namespace states
	{
		/// 
		/// @brief Base Ai Ranged State.
		/// 
		/// Defines the base for all ai ranged states.
		/// 
		class AiRangedState : public AiBaseState
		{
		public: // Constructors/Destructor
			AiRangedState(AiRanged * aiUnit);
			~AiRangedState() = default;

		public: // Public Member Functions
			virtual void draw(Window & window, float const & deltaTime) override;
		public: // Public Member Variables
		protected: // Protected Member Functions
			float clamp(float const & value, float const & min, float const & max) const;
			bool checkState(sf::Vector2f const & aiToDeploy, float const & minDistance);
			void updateSpeed(sf::Vector2f const & aiToDeploy, float const & speed);
			void updateTurn(sf::Vector2f const & aiToDeploy, float const & maxTurnRate, float const & maxSpeed);
			void updatePosition();
			sf::Vector2f generateDeployPosition() const;
		protected: // Protected Member Variables
			/// <summary>
			/// @brief Reference to the ai in this state.
			/// 
			/// 
			/// </summary>
			AiRanged * m_ai;
		private: // Private Member Functions
		private: // Private Member Variables
		};
	}
}

#include "entities\ai\ranged\AiRanged.h"

#endif // !AI_RANGED_STATE_H