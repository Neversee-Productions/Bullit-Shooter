#ifndef AI_BASIC_WINDUP_STATE_H
#define AI_BASIC_WINDUP_STATE_H

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
		class AiBasicWindupState : public AiBasicState
		{

		public: // Constructors/Destructor
			AiBasicWindupState(AiBasic & aiUnit);
			~AiBasicWindupState() = default;

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
			/// @brief Unique pointer to the tracker of time.
			/// 
			/// Tracks the amount of time spent in this state.
			/// </summary>
			std::unique_ptr<sf::Clock> m_uptrTimer;
			/// <summary>
			/// Amount of time that it takes for the ai to complete this state.
			/// 
			/// 
			/// </summary>
			sf::Time const m_WINDUP_TIME;
		};

		/// <summary>
		/// @brief Alias for Basic Ai Charge State.
		/// 
		/// 
		/// </summary>
		typedef AiBasicWindupState Windup;
	}
}

#include "AiBasic.h"

#endif // !AI_BASIC_WINDUP_STATE_H