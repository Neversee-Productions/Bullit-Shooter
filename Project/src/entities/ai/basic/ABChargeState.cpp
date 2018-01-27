#include "entities\ai\basic\ABChargeState.h"

/// <summary>
/// @brief Construct the state.
/// 
/// Store reference to unit that is applied to state.
/// </summary>
/// <param name="aiUnit">ai that will call this state.</param>
ai::states::AiBasicChargeState::AiBasicChargeState(AiBasic & aiUnit)
	: AiBasicState(aiUnit)
	, m_ATTACK_RADIUS(100.0f)
	, m_DECCELERATION(10.0f)
	, m_attackCollision()
	, m_attackHitShape(m_ATTACK_RADIUS)
{
}

/// <summary>
/// 
/// </summary>
void ai::states::AiBasicChargeState::enter()
{
	m_ai.m_renderQuad.setFillColor(sf::Color::Red);
	m_ai.m_speed = 0.0f;
}

/// <summary>
/// @brief Ai attack logic.
/// 
/// 
/// </summary>
void ai::states::AiBasicChargeState::update()
{


	this->updateCollision();
}

/// <summary>
/// @brief Ai attack rendering.
/// 
/// Render attack effects.
/// </summary>
/// <param name="window">reference to render target.</param>
/// <param name="deltaTime">read-only reference to delta time between draw calls.</param>
void ai::states::AiBasicChargeState::draw(Window & window, float const & deltaTime)
{
	window.draw(m_ai.m_renderQuad);
	window.draw(m_attackHitShape);
}

/// <summary>
/// @brief 
/// </summary>
void ai::states::AiBasicChargeState::exit()
{
}

/// <summary>
/// 
/// </summary>
void ai::states::AiBasicChargeState::updateCollision()
{
	m_attackCollision.p = { m_ai.m_position.x, m_ai.m_position.y };
	m_attackCollision.r = m_ATTACK_RADIUS;

	m_attackHitShape.setPosition(m_ai.m_position);
	m_attackHitShape.setRadius(m_ATTACK_RADIUS);
}
