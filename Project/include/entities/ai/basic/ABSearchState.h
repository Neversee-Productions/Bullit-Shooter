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
		public: // Constructors
			AiBasicSearchState(AiBasic & aiUnit);
			~AiBasicSearchState() = default;

		public: // Base Class Overrides
			virtual void enter() final override;
			virtual void update() final override;
			virtual void draw(Window & window, float const & deltaTime) final override;
			virtual void exit() final override;

		private: // Private member functions
			float clamp(float const & value, float const & min, float const & max) const;
			void updateState(sf::Vector2f const & aiToPlayer);
			bool checkState(sf::Vector2f const & aiToPlayer);
			void updateSpeed(sf::Vector2f const & aiToPlayer);
			void updateTurn(sf::Vector2f const & aiToPlayer);
			void updatePosition();

		private: // Private member variables
			float const & m_DELTA_TIME;
			float const m_MAX_SPEED;
			float const m_MAX_TURN_RATE;
			float const m_MIN_DISTANCE;

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