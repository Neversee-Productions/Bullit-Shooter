#include "entities\ai\basic\ABRecoverState.h"

/// <summary>
/// @brief Basic Recover State constructor.
/// 
/// Sets all constants for the current state.
/// </summary>
/// <param name="aiUnit">reference of ai unit that will call this state.</param>
ai::states::AiBasicRecoverState::AiBasicRecoverState(AiBasic & aiUnit)
	: AiBasicState(aiUnit)
	, m_timer(nullptr)
	, m_RECOVERY_TIME(sf::seconds(0.25f))
{
}

/// <summary>
/// @brief What the ai does when entering this state.
/// 
/// 
/// </summary>
void ai::states::AiBasicRecoverState::enter()
{
	if (m_ai.s_COLOR_STATES)
	{
		m_ai.m_renderQuad.setFillColor(sf::Color::Cyan);
	}
	//m_ai.playAnimation(ai::AiBasic::s_RECOVER_ID, false);
	m_timer = std::make_unique<sf::Clock>();
}

/// <summary>
/// @brief What the ai does in this state for each single frame.
/// 
/// Called each frame in accordance to AiBase::s_DELTA_TIME.
/// </summary>
void ai::states::AiBasicRecoverState::update()
{
	this->updateState();
}

/// <summary>
/// @brief render the ai to the screen.
/// 
/// Using a quad to render the ai he is rendered at
/// AiBasic::m_position facing the direction
/// represented by the angle, in degrees, AiBasic::m_angle.
/// </summary>
/// <param name="window">reference to the window, used as the target for render calls.</param>
/// <param name="deltaTime">read-only reference to the delta time for the last draw call, in seconds.</param>
void ai::states::AiBasicRecoverState::draw(Window & window, float const & deltaTime)
{
	m_ai.m_animator.update(sf::seconds(deltaTime));
	m_ai.m_animator.animate(m_ai.m_renderQuad);
	window.draw(m_ai.m_renderQuad);
}

/// <summary>
/// @brief What ai does when exiting this state.
/// 
/// 
/// </summary>
void ai::states::AiBasicRecoverState::exit()
{
	//m_ai.stopAnimation();
}

/// <summary>
/// @brief checks if state is to be terminated and responds appropriatly.
/// 
/// 
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
void ai::states::AiBasicRecoverState::updateState()
{
	if (this->checkState())
	{
		std::shared_ptr<ai::states::Basic> sptrNextState = 
			std::make_shared<ai::states::Seek>(ai::states::Seek(m_ai));
		m_ai.setState(sptrNextState, false);
	}
}

/// <summary>
/// @brief Checks if state is to be terminated.
/// 
/// 
/// </summary>
/// <returns>True if timer elapsed time is greater than the time to recover.</returns>
bool ai::states::AiBasicRecoverState::checkState()
{
	if (m_timer->getElapsedTime() > m_RECOVERY_TIME)
	{
		return true;
	}
	return false;
}
