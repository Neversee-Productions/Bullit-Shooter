#ifndef AI_BASIC_RECOVER_STATE_H
#define AI_BASIC_RECOVER_STATE_H

#include "AiBasicState.h"

namespace ai
{
	// Forward Referencing

	class AiBasic;

	namespace states
	{

		///
		/// @author Rafael Plugge
		/// @brief Defines the recover state for the basic ai.
		/// @extends AiBasicState
		/// 
		/// 
		///
		class AiBasicRecoverState : public AiBasicState
		{
		public: // Constructors/Destructor
			AiBasicRecoverState(AiBasic & aiUnit);
			~AiBasicRecoverState() = default;

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
			/// <summary>
			/// @brief unique pointer to our timer.
			/// 
			/// counts time on a separate thread.
			/// </summary>
			std::unique_ptr<sf::Clock> m_timer;

			/// <summary>
			/// @brief total amount of recovery time.
			/// 
			/// amount of time that it takes for
			/// the basic ai to recover from this state.
			/// </summary>
			sf::Time const m_RECOVERY_TIME;
		};

		/// <summary>
		/// @brief Alias for Basic Ai Recover State.
		/// 
		/// 
		/// </summary>
		typedef AiBasicRecoverState Recover;
	}
}

#include "AiBasic.h"

#endif // !AI_BASIC_RECOVER_STATE_H