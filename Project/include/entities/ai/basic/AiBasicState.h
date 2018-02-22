#ifndef AI_BASIC_ACTION_H
#define AI_BASIC_ACTION_H

//STL Includes
#include <iterator>
#include <memory>
#include <list>
// SFML Includes
#include "SFML\System\Vector2.hpp"
#include "SFML\System\Vector3.hpp"
// Thor Includes
#include "Thor\Math.hpp"
#include "Thor\Vectors.hpp"
// Project Includes
#include "system\Window.h"
#include "entities\ai\AiBaseState.h"

namespace ai
{
	class AiBasic;

	namespace states
	{

		/// 
		/// @author Rafael Plugge
		/// @brief Basic State.
		/// 
		/// 
		/// 
		class AiBasicState : public AiBaseState
		{
		public: // Constructors/Destructor
			AiBasicState(AiBasic & aiUnit);
			~AiBasicState() = default;

		public: // Public Member Functions
			virtual bool checkCollision(tinyh::c2AABB const & collision);
			virtual bool checkCollision(tinyh::c2Circle const & collision);
			virtual bool checkCollision(tinyh::c2Capsule const & collision);
		public: // Public Member Variables
		protected: // Protected Member Functions
		protected: // Protected Member Variables
			/// <summary>
			/// @brief Reference to the ai in this state.
			/// 
			/// 
			/// </summary>
			AiBasic & m_ai;
		private: // Private Member Functions
		private: // Private Member Variables

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