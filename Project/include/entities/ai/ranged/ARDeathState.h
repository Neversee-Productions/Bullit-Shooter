#ifndef AI_RANGED_DEATH_STATE_H
#define AI_RANGED_DEATH_STATE_H

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
		class AiRangedDeathState : public ai::states::AiRangedState
		{
		public: // Constructors/Destructor
			AiRangedDeathState(ai::AiRanged * aiUnit);
			~AiRangedDeathState() = default;
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
		private: // Private Static Variables
		private: // Private Member Variables
		};
	}
}

#include "AiRanged.h"

#endif // !AI_RANGED_DEPLOY_STATE_H