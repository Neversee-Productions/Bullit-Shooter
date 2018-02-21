#include "entities\ai\ranged\ARDeployState.h"

sf::Time const ai::states::AiRangedDeployState::s_DEPLOY_TIME = sf::seconds(1.0f);
sf::Time const ai::states::AiRangedDeployState::s_UPDATE_DT_TIME = sf::seconds(App::getUpdateDeltaTime());

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
/// <param name="aiUnit">pointer to the ai unit.</param>
ai::states::AiRangedDeployState::AiRangedDeployState(ai::AiRanged * aiUnit)
	: ai::states::AiRangedState(aiUnit)
{
}

/// <summary>
/// @brief What the ai does when entering this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedDeployState::enter()
{
	m_timer = sf::Time();
	m_ai->m_animator.stopAnimation();
	m_ai->playAnimation(m_ai->m_sptrResources->m_animationDeploy, m_ai->m_sptrResources->m_textureDeploy, false);
}

/// <summary>
/// @brief What the ai does in this state for a single frame.
/// 
/// Called each frame in accordance to AiBase::s_DELTA_TIME.
/// </summary>
void ai::states::AiRangedDeployState::update()
{
	this->updateTimer();
	this->updateState();
}

/// <summary>
/// @brief What ai does when exiting this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedDeployState::exit()
{
	m_ai->m_animator.stopAnimation();
}

/// <summary>
/// @brief checks if state is to be terminated and responds appropriatly.
/// 
/// 
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
void ai::states::AiRangedDeployState::updateState()
{
	if (this->checkState())
	{
		m_ai->setState(std::make_shared<ai::states::AiRangedShootState>(m_ai), false);
	}
}

/// <summary>
/// @brief Checks if state is to be terminated.
/// 
/// True if the ai has been in the deploy state longer than
/// AiRangedDeployState::s_DEPLOY_TIME.
/// </summary>
/// <param name="aiToDeploy">read-only reference to the vector from the ai to the deploy point.</param>
/// <returns>True if ai has been long enough in the deploy state..</returns>
bool ai::states::AiRangedDeployState::checkState() const
{
	return m_timer > AiRangedDeployState::s_DEPLOY_TIME;
}

/// <summary>
/// @brief Update the deployment timer.
/// 
/// 
/// </summary>
void ai::states::AiRangedDeployState::updateTimer()
{
	m_timer += s_UPDATE_DT_TIME;
}
