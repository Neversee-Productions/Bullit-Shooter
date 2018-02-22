#ifndef AI_BASIC_DEATH_STATE_H
#define AI_BASIC_DEATH_STATE_H

#include "AiBasicState.h"

namespace ai
{
	// Forward referencing

	class AiBasic;

	namespace states
	{
		/// 
		/// @author Rafael Plugge
		/// @brief Defines the windup state for the basic ai.
		/// @extends AiBasicState
		/// 
		/// 
		class AiBasicDeathState : public AiBasicState
		{

		public: // Constructors/Destructor
			AiBasicDeathState(AiBasic & aiUnit);
			~AiBasicDeathState() = default;

		public: // Public Member Functions
			virtual void enter() final override;
			virtual void update() final override;
			virtual void draw(Window & window, float const & deltaTime) final override;
			virtual void exit() final override;

		public: // Public Member Variables
		protected: // Protected Member Functions
		protected: // Protected Member Variables
		private: // Private Member Functions
			void updateState();
			bool checkState();
		private: // Private Member Variables

		};
	}
}

#include "AiBasic.h"

#endif // !AI_BASIC_WINDUP_STATE_H