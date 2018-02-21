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
	, m_CHARGE_SPEED(450.0f)
	, m_DECCELERATION(250.0f)
	, m_LOW_SPEED(180.0f * m_DELTA_TIME)
{
}

/// <summary>
/// @brief What the ai does when entering this state.
/// 
/// 
/// </summary>
void ai::states::AiBasicChargeState::enter()
{
	if (m_ai.s_COLOR_STATES)
	{
		m_ai.m_renderQuad.setFillColor(sf::Color::Red);
	}
	m_ai.m_speed = m_CHARGE_SPEED;
	m_ai.playAnimation(ai::AiBasic::s_CHARGE_ID, false);
}

/// <summary>
/// @brief What the ai does in this state for a single frame.
/// 
/// 
/// </summary>
void ai::states::AiBasicChargeState::update()
{
	m_ai.updateHitbox(m_ai.m_renderQuad);
	this->updateSpeed();
	this->updatePosition();
	this->updateState();
}

/// <summary>
/// @brief render the ai to the screen.
/// 
/// Render attack effects.
/// </summary>
/// <param name="window">reference to render target.</param>
/// <param name="deltaTime">read-only reference to delta time between draw calls.</param>
void ai::states::AiBasicChargeState::draw(Window & window, float const & deltaTime)
{
	m_ai.m_renderQuad.setPosition(m_ai.m_position);
	m_ai.m_renderQuad.setRotation(m_ai.m_angle + 90.0f);
	m_ai.m_animator.update(sf::seconds(deltaTime));
	m_ai.m_animator.animate(m_ai.m_renderQuad);
	window.draw(m_ai.m_renderQuad);
}

/// <summary>
/// @brief What ai does when exiting this state
/// 
/// 
/// </summary>
void ai::states::AiBasicChargeState::exit()
{
}

/// <summary>
/// @brief checks if state is to be terminated and responds appropriatly.
/// 
/// 
/// </summary>
void ai::states::AiBasicChargeState::updateState()
{
	if (this->checkState())
	{
		std::shared_ptr<ai::states::Basic> sptrNewState =
			std::make_shared<ai::states::Seek>(m_ai);
		m_ai.setState(sptrNewState, false);
	}
}

/// <summary>
/// @brief Checks if state is to be terminated.
/// 
/// State terminates if ai's speed is low enough.
/// </summary>
/// <returns>True if the ai's speed is lower than </returns>
bool ai::states::AiBasicChargeState::checkState()
{
	if (m_ai.m_speed < m_LOW_SPEED)
	{
		return true;
	}
	return false;
}

/// <summary>
/// @brief Changes speed per frame.
/// 
/// Applies a deceleration to the current speed.
/// </summary>
void ai::states::AiBasicChargeState::updateSpeed()
{
	m_ai.m_speed -= m_DECCELERATION * m_DELTA_TIME;
}

/// <summary>
/// @brief Updates position according to speed and heading.
/// 
/// 
/// </summary>
void ai::states::AiBasicChargeState::updatePosition()
{
	m_ai.m_position += m_ai.m_heading * m_ai.m_speed * m_DELTA_TIME;
}
