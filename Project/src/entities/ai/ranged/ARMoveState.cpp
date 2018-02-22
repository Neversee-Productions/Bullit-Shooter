#include "entities\ai\ranged\ARMoveState.h"

float const ai::states::AiRangedMoveState::s_MAX_SPEED = 120.f;
float const ai::states::AiRangedMoveState::s_MAX_TURN_RATE = 120.0f;
float const ai::states::AiRangedMoveState::s_MIN_DISTANCE = 30.0f;

/// <summary>
/// @brief Default constructor.
/// 
/// Pass ai unit into base constructor.
/// </summary>
/// <param name="aiUnit">pointer to ai unit.</param>
ai::states::AiRangedMoveState::AiRangedMoveState(AiRanged * aiUnit)
	: ai::states::AiRangedState(aiUnit)
{
}

/// <summary>
/// @brief What the ai does when entering this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedMoveState::enter()
{
	if (ai::AiRanged::s_COLOR_QUAD)
	{
		m_ai->m_renderQuad.setColor(sf::Color::Green);
	}
	m_ai->m_deployPosition = this->generateDeployPosition();
	m_ai->m_animator.stopAnimation();
	m_ai->playAnimation(m_ai->m_sptrResources->m_animationMove, m_ai->m_sptrResources->m_textureMove, true);
}

/// <summary>
/// @brief What the ai does in this state for a single frame.
/// 
/// Called each frame in accordance to AiBase::s_DELTA_TIME.
/// </summary>
void ai::states::AiRangedMoveState::update()
{
	sf::Vector2f const AI_TO_DEPLOY = m_ai->m_deployPosition - m_ai->m_position;
	this->updateSpeed(AI_TO_DEPLOY, AiRangedMoveState::s_MAX_SPEED);
	this->updateTurn(AI_TO_DEPLOY, AiRangedMoveState::s_MAX_TURN_RATE, AiRangedMoveState::s_MAX_SPEED);
	this->updatePosition();
	this->updateState(AI_TO_DEPLOY);
}

/// <summary>
/// @brief What ai does when exiting this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedMoveState::exit()
{
	m_ai->m_animator.stopAnimation();
}

/// <summary>
/// @brief checks if state is to be terminated and responds appropriatly.
/// 
/// 
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
void ai::states::AiRangedMoveState::updateState(sf::Vector2f const & aiToDeploy)
{
	if (this->checkState(aiToDeploy, AiRangedMoveState::s_MIN_DISTANCE))
	{
		m_ai->setState(std::make_shared<ai::states::AiRangedDeployState>(m_ai), false);
	}
}