#ifndef AI_BASIC_H
#define AI_BASIC_H

// STL Includes
#include <list> // For std::list
// SFML Includes
#include "SFML\Graphics\RectangleShape.hpp"
// Thor Includes
#include "Thor\Animations\Animator.hpp"
// Project Includes
#include "entities\Entities.h"
#include "entities\ai\AiBase.h"


namespace ai
{
	// forward reference

	namespace states
	{
		class AiBasicState;
		class AiBasicSearchState;
	}

	/// 
	/// @author Rafael Plugge
	/// @brief Represents basic ai.
	/// 
	/// This will be basic ai, its natural behaviour,
	/// will be to
	///		approach the player
	///		windup for an attack
	///		attack
	///	repeat.
	/// 
	class AiBasic : public AiBase
	{
	private:
		/// <summary>
		/// @brief Alias for Basic State.
		/// 
		/// Makes life easier
		/// </summary>
		typedef ai::states::AiBasicState BasicState;
		typedef ai::states::AiBasicSearchState SearchState;

		// Friends

		//friend class BasicState;
		friend class SearchState;

	public:
		AiBasic(Player const & player);
		~AiBasic() = default;

		// AiBase Overrides

		virtual void init(std::shared_ptr<Resources> sptrResources) final override;
		virtual void update(float const & deltaTime) final override;
		virtual void draw(Window & window, float const & deltaTime) final override;

	protected:

		/// <summary>
		/// @brief Read-only reference to the player.
		/// 
		/// Needed for search for him and for attack aiming.
		/// </summary>
		Player const & m_player;

		/// <summary>
		/// @brief Ai will be drawn on this quad.
		/// 
		/// Represents a size defined quad that a texture
		/// will be drawn on, frame animations will be targeted to this quad.
		/// </summary>
		sf::RectangleShape m_renderQuad;

	private:

		std::list<std::unique_ptr<BasicState>> m_actions;

		std::unique_ptr<BasicState> m_uptrAction;

	};

	/// <summary>
	/// @brief Alias for a basic enemy.
	/// 
	/// 
	/// </summary>
	typedef AiBasic Basic;

}

#include "AiBasicState.h"
#include "ABSearchState.h"

#endif // !AI_BASIC_H