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
		/// @brief 
		/// 
		class AiRangedMoveState : public AiRangedState
		{
		public: // Constructors/Destructor
			AiRangedMoveState(AiRanged * aiUnit);
			~AiRangedMoveState() = default;

		public: // Public Member Functions
			virtual void enter() final override;
			virtual void update() final override;
			virtual void draw(Window & window, float const & deltaTime) final override;
			virtual void exit() final override;
		public: // Public Member Variables
		protected: // Protected Member Functions
		protected: // Protected Member Variables
		private: // Private Member Functions
			float clamp(float const & value, float const & min, float const & max) const;
			void updateState(sf::Vector2f const & aiToDeploy);
			bool checkState(sf::Vector2f const & aiToDeploy);
			void updateSpeed(sf::Vector2f const & aiToDeploy);
			void updateTurn(sf::Vector2f const & aiToDeploy);
			void updatePosition();
			sf::Vector2f generateDeployPosition() const;
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