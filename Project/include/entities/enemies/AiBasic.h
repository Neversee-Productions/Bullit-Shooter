#ifndef AI_BASIC_H
#define AI_BASIC_H

// SFML Includes
#include "SFML\Graphics\RectangleShape.hpp"
// Thor Includes
#include "Thor\Animations\Animator.hpp"
// Project Includes
#include "AiActions.h"
#include "AiBase.h"

class AiBasic :
	public AiBase<AiActions::BasicActions>
{
private:
	typedef AiActions::BasicActions ActionType;

public:
	AiBasic();
	~AiBasic() = default;

	// AiBase Overrides

	virtual void update(float const & deltaTime) final override;
	virtual void draw(Window & window, float const & deltaTime) final override;

protected:
	/// <summary>
	/// @brief Ai will be drawn on this quad.
	/// 
	/// Represents a size defined quad that a texture
	/// will be drawn on, frame animations will be targeted to this quad.
	/// </summary>
	sf::RectangleShape m_renderQuad;

private:
	void passiveSearch(AiBasic &);
	void spottedPlayer(AiBasic &, sf::Vector2f const & playerPosition);
	void approachPlayer(AiBasic &, sf::Vector2f const & playerPosition);
	void attackPlayer(AiBasic &, sf::Vector2f const & playerPosition);

};

#endif // !AI_BASIC_H