#ifndef AI_BASIC_ACTION_H
#define AI_BASIC_ACTION_H

//STL Includes
#include <iterator>
#include <memory>
#include <list>
// Project Includes
#include "Window.h"

namespace ai
{
	class AiBasic;

	/// 
	/// @author Rafael Plugge
	/// @brief Encapsulate all the states into their own namespace.
	/// 
	/// 
	/// 
	namespace states
	{

		/// 
		/// @author Rafael Plugge
		/// @brief Basic State.
		/// 
		/// 
		/// 
		class AiBasicState
		{
		public:

			AiBasicState(AiBasic & aiUnit);
			~AiBasicState() = default;

			virtual void update() = 0;
			virtual void draw(Window & window, float const & deltaTime) = 0;

		protected:
			AiBasic & m_ai;
		};

		/// <summary>
		/// @brief Alias for shortened Class name.
		/// 
		/// 
		/// </summary>
		typedef AiBasicState Basic;
	}
}

#include "AiBasic.h"

#endif // !AI_BASIC_ACTION_H