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