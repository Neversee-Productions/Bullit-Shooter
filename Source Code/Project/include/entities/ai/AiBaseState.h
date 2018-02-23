#ifndef AI_BASE_STATE_H
#define AI_BASE_STATE_H

// Project Includes
#include "system\Window.h"

namespace ai
{
	class AiBase;

	/// 
	/// @author Rafael Plugge
	/// @brief Encapsulate all the states into their own namespace.
	/// 
	/// 
	/// 
	namespace states
	{
		/// 
		/// @brief Abstract Base Ai State.
		/// @author Rafael Plugge
		/// 
		/// Defines the abstract interface of all states.
		/// 
		class AiBaseState
		{
		public: // Constructors/Destructor
			AiBaseState();
			~AiBaseState() = default;
		public: // Public Member Functions
			virtual void enter() abstract;
			virtual void update() abstract;
			virtual void draw(Window & window, float const & deltaTime) abstract;
			virtual void exit() abstract;
		public: // Public Member Variables
		protected: // Protected Member Functions
		protected: // Protected Member Variables
			/// <summary>
			/// @brief Time between each update call, in seconds.
			///
			///
			/// </summary>
			float const & m_DELTA_TIME;
		private: // Private Member Functions
		private: // Private Member Variables
		};
	}
}

#include "AiBase.h"

#endif // !AI_BASE_STATE_H