#ifndef AI_BASIC_SEARCH_STATE_H
#define AI_BASIC_SEARCH_STATE_H

#include "AiBasic.h"
#include "AiBasicState.h"

namespace ai
{
	class AiBasic;

	namespace states
	{
		class AiBasicSearchState :
			public AiBasicState
		{
		public:
			AiBasicSearchState(AiBasic & aiUnit);
			~AiBasicSearchState() = default;

			// overrides

			virtual void update() final override;
			virtual void draw(Window & window, float const & deltaTime) final override;

		};

		/// <summary>
		/// @brief Alias for Basic Ai Search State.
		/// 
		/// 
		/// </summary>
		typedef AiBasicSearchState Search;

	}
}

#include "AiBasic.h"

#endif // !AI_BASIC_SEARCH_STATE_H