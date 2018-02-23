#include "entities\ai\ranged\ARDeathState.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
/// <param name="aiUnit">pointer to the ai unit.</param>
ai::states::AiRangedDeathState::AiRangedDeathState(ai::AiRanged * aiUnit)
	: ai::states::AiRangedState(aiUnit)
{
}

/// <summary>
/// @brief What the ai does when entering this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedDeathState::enter()
{
	m_ai->m_alive = false;
	m_ai->playAnimation(m_ai->m_sptrResources->m_animationDeath, m_ai->m_sptrResources->m_textureDeath, false);
}

/// <summary>
/// @brief What the ai does in this state for a single frame.
/// 
/// Called each frame in accordance to AiBase::s_DELTA_TIME.
/// </summary>
void ai::states::AiRangedDeathState::update()
{
	this->updateState();
}

/// <summary>
/// @brief What ai does when exiting this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedDeathState::exit()
{
	m_ai->m_alive = true;
}

/// <summary>
/// @brief checks if state is to be terminated and responds appropriatly.
/// 
/// 
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
void ai::states::AiRangedDeathState::updateState()
{
	if (this->checkState())
	{
		m_ai->setActive(false);
	}
}

/// <summary>
/// @brief Checks if state is to be terminated.
/// 
/// True if the ai has been in the deploy state longer than
/// AiRangedDeathState::s_DEPLOY_TIME.
/// </summary>
/// <param name="aiToDeploy">read-only reference to the vector from the ai to the deploy point.</param>
/// <returns>True if ai has been long enough in the deploy state..</returns>
bool ai::states::AiRangedDeathState::checkState() const
{
	return !m_ai->m_animator.isPlayingAnimation();
}

