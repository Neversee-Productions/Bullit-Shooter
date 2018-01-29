#ifndef AI_BASIC_RECOVER_STATE_H
#define AI_BASIC_RECOVER_STATE_H

#include "AiBasicState.h"

namespace ai
{
	// Forward Referencing

	class AiBasic;

	namespace states
	{
		class AiBasicRecoverState : public AiBasicState
		{
		public: // Constructors/Destructor
			AiBasicRecoverState(AiBasic & aiUnit);
			~AiBasicRecoverState() = default;

		public: // Public Member Functions
		public: // Public Member Variables
		protected: // Protected Member Functions
		protected: // Protected Member Variables
		private: // Private Member Functions
		private: // Private Member Variables
		};
	}
}

#include "AiBasic.h"

#endif // !AI_BASIC_RECOVER_STATE_H