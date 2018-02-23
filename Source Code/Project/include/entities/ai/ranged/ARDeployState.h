#ifndef AI_RANGED_DEPLOY_STATE_H
#define AI_RANGED_DEPLOY_STATE_H

// STD Includes
// Project Includes
#include "AiRangedState.h"

namespace ai
{
	class AiRanged;

	namespace states
	{
		/// 
		/// @author Rafael Plugge
		/// @brief Ranged Ai's Deploy State.
		/// 
		/// 
		/// 
		class AiRangedDeployState : public ai::states::AiRangedState
		{
		public: // Constructors/Destructor
			AiRangedDeployState(ai::AiRanged * aiUnit);
			~AiRangedDeployState() = default;
		public: // Public Member Functions
			virtual void enter() final override;
			virtual void update() final override;
			virtual void exit() final override;
		public: // Public Member Variables
		protected: // Protected Member Functions
		protected: // Protected Member Variables
		private: // Private Member Functions
			void updateState();
			bool checkState() const;
			void updateTimer();
		private: // Private Static Variables
			static sf::Time const s_DEPLOY_TIME;
			static sf::Time const s_UPDATE_DT_TIME;
		private: // Private Member Variables
			/// <summary>
			/// @brief Tracks how long the ai has been in the deploy state.
			/// 
			/// 
			/// </summary>
			sf::Time m_timer;
		};
	}
}

#include "AiRanged.h"

#endif // !AI_RANGED_DEPLOY_STATE_H