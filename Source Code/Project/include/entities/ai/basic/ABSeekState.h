#ifndef AI_BASIC_SEARCH_STATE_H
#define AI_BASIC_SEARCH_STATE_H

#include "AiBasic.h"
#include "AiBasicState.h"

namespace ai
{
	class AiBasic;

	namespace states
	{
		/// 
		/// @author Rafael Plugge
		/// @brief Basic Ai's Seek State.
		/// 
		/// Will seek the player out with a 
		/// maximum speed and turning rate.
		/// Terminates when within a certain
		/// proximity of the player.
		/// 
		class AiBasicSeekState :
			public AiBasicState
		{
		public: // Constructors
			AiBasicSeekState(AiBasic & aiUnit);
			~AiBasicSeekState() = default;

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
			float const m_MAX_SPEED;
			float const m_MAX_TURN_RATE;
			float const m_MIN_DISTANCE;
			float const m_MIN_ANGLE;

		};

		/// <summary>
		/// @brief Alias for Basic Ai Seek State.
		/// 
		/// 
		/// </summary>
		typedef AiBasicSeekState Seek;

	}
}

#include "AiBasic.h"

#endif // !AI_BASIC_SEARCH_STATE_H