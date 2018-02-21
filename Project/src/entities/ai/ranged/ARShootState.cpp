#include "entities\ai\ranged\ARShootState.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
/// <param name="aiUnit">pointer to the ai unit.</param>
ai::states::AiRangedShootState::AiRangedShootState(ai::AiRanged * aiUnit)
	: ai::states::AiRangedState(aiUnit)
{
}

/// <summary>
/// @brief What the ai does when entering this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedShootState::enter()
{
	m_ai->m_animator.stopAnimation();
	m_ai->playAnimation(m_ai->m_sptrResources->m_animationShoot, m_ai->m_sptrResources->m_textureShoot, true);
}

/// <summary>
/// @brief What the ai does in this state for a single frame.
/// 
/// Called each frame in accordance to AiBase::s_DELTA_TIME.
/// </summary>
void ai::states::AiRangedShootState::update()
{
}

/// <summary>
/// @brief What ai does when exiting this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedShootState::exit()
{
	m_ai->m_animator.stopAnimation();
}

/// <summary>
/// @brief checks if state is to be terminated and responds appropriatly.
/// 
/// 
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
void ai::states::AiRangedShootState::updateState()
{
	if (this->checkState())
	{

	}
}

/// <summary>
/// @brief Checks if state is to be terminated.
/// 
/// True if the ai is within a small radius of the deployment area.
/// </summary>
/// <param name="aiToDeploy">read-only reference to the vector from the ai to the deploy point.</param>
/// <returns>True if ai is close enough to player to commence attack sequence.</returns>
bool ai::states::AiRangedShootState::checkState() const
{
	return false;
}

/// <summary>
/// @brief Update the deployment timer.
/// 
/// 
/// </summary>
void ai::states::AiRangedShootState::updateTimer()
{
}
