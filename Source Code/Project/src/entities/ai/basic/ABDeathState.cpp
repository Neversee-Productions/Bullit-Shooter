#include "entities\ai\basic\ABDeathState.h"

/// <summary>
/// @brief Construct the state.
/// 
/// Store reference to unit that is applied to state.
/// </summary>
/// <param name="aiUnit">ai that will call this state.</param>
ai::states::AiBasicDeathState::AiBasicDeathState(AiBasic & aiUnit)
	: AiBasicState(aiUnit)
{
}

/// <summary>
/// @brief What the ai does when entering this state.
/// 
/// 
/// </summary>
void ai::states::AiBasicDeathState::enter()
{
	m_ai.m_dead = true;
	m_ai.playAnimation(ai::AiBasic::s_DEATH_ID, false);
}

/// <summary>
/// @brief What the ai does in this state for a single frame.
/// 
/// 
/// </summary>
void ai::states::AiBasicDeathState::update()
{
	this->updateState();
}

/// <summary>
/// @brief render the ai to the screen.
/// 
/// Render attack effects.
/// </summary>
/// <param name="window">reference to render target.</param>
/// <param name="deltaTime">read-only reference to delta time between draw calls.</param>
void ai::states::AiBasicDeathState::draw(Window & window, float const & deltaTime)
{
	m_ai.m_animator.update(sf::seconds(deltaTime));
	m_ai.m_animator.animate(m_ai.m_renderQuad);
	window.draw(m_ai.m_renderQuad);
}

/// <summary>
/// @brief What ai does when exiting this state
/// 
/// 
/// </summary>
void ai::states::AiBasicDeathState::exit()
{
	m_ai.m_dead = false;
}

/// <summary>
/// @brief checks if state is to be terminated and responds appropriatly.
/// 
/// 
/// </summary>
void ai::states::AiBasicDeathState::updateState()
{
	if (this->checkState())
	{
		m_ai.setActive(false);
	}
}

/// <summary>
/// @brief Checks if state is to be terminated.
/// 
/// 
/// </summary>
/// <returns>True if the ai's death animation is finished playing.</returns>
bool ai::states::AiBasicDeathState::checkState()
{
	return !m_ai.m_animator.isPlayingAnimation();
}
