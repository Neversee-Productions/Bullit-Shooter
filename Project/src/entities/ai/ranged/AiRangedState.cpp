#include "entities\ai\ranged\AiRangedState.h"

/// <summary>
/// @brief Base Ranged Ai State.
/// 
/// 
/// </summary>
/// <param name="aiUnit">pointer to the ai unit.</param>
ai::states::AiRangedState::AiRangedState(AiRanged * aiUnit)
	: ai::states::AiBaseState()
	, m_ai(aiUnit)
{
}

/// <summary>
/// @brief render the ai to the screen.
/// 
/// Using a quad to render the ai he is rendered at
/// AiRanged::m_position facing the direction
/// represented by the angle, in degrees, AiRanged::m_angle.
/// </summary>
/// <param name="window">reference to the window, used as the target for render calls.</param>
/// <param name="deltaTime">read-only reference to the delta time for the last draw call, in seconds.</param>
void ai::states::AiRangedState::draw(Window & window, float const & deltaTime)
{
	m_ai->m_renderQuad.setPosition(m_ai->m_position);
	m_ai->m_renderQuad.setRotation(m_ai->m_angle + 90.0f);
	m_ai->m_animator.update(sf::seconds(deltaTime));
	m_ai->m_animator.animate(m_ai->m_renderQuad);
	window.draw(m_ai->m_renderQuad);
}
