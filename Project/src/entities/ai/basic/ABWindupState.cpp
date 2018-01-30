#include "entities\ai\basic\ABWindupState.h"

/// <summary>
/// @brief Construct the state.
/// 
/// Store reference to unit that is applied to state.
/// </summary>
/// <param name="aiUnit">ai that will call this state.</param>
ai::states::AiBasicWindupState::AiBasicWindupState(AiBasic & aiUnit)
	: AiBasicState(aiUnit)
	, m_uptrTimer()
	, m_WINDUP_TIME(sf::seconds(0.5f))
{
}

/// <summary>
/// @brief What the ai does when entering this state.
/// 
/// 
/// </summary>
void ai::states::AiBasicWindupState::enter()
{
	if (m_ai.s_COLOR_STATES)
	{
		m_ai.m_renderQuad.setFillColor(sf::Color(255u, 165u, 0u, 255u));
	}
	m_uptrTimer = std::make_unique<sf::Clock>(sf::Clock());
	m_ai.playAnimation(ai::AiBasic::s_WINDUP_ID, false);
}

/// <summary>
/// @brief What the ai does in this state for a single frame.
/// 
/// 
/// </summary>
void ai::states::AiBasicWindupState::update()
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
void ai::states::AiBasicWindupState::draw(Window & window, float const & deltaTime)
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
void ai::states::AiBasicWindupState::exit()
{
	std::make_unique<sf::Clock>().swap(m_uptrTimer);
}

/// <summary>
/// @brief checks if state is to be terminated and responds appropriatly.
/// 
/// 
/// </summary>
void ai::states::AiBasicWindupState::updateState()
{
	if (this->checkState())
	{
		std::shared_ptr<ai::states::Basic> sptrNewState =
			std::make_shared<ai::states::Charge>(ai::states::Charge(m_ai));
		m_ai.setState(sptrNewState, false);
	}
}

/// <summary>
/// @brief Checks if state is to be terminated.
/// 
/// State terminates if ai's time spent in this state exceeds,
/// AiBasicWindupState::m_WINDUP_TIME.
/// </summary>
/// <returns>True if the ai's spent time greater than the state's windup time.</returns>
bool ai::states::AiBasicWindupState::checkState()
{
	if (m_uptrTimer->getElapsedTime() > m_WINDUP_TIME)
	{
		return true;
	}
	return false;
}
