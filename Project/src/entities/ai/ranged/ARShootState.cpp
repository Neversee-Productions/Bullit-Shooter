#include "entities\ai\ranged\ARShootState.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
/// <param name="aiUnit">pointer to the ai unit.</param>
ai::states::AiRangedShootState::AiRangedShootState(ai::AiRanged * aiUnit)
	: ai::states::AiRangedState(aiUnit)
	, m_MIN_ANGLE(10.0f)
	, m_FIRE_RATE(sf::seconds(1.5f))
{
}

/// <summary>
/// @brief What the ai does when entering this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedShootState::enter()
{
}

/// <summary>
/// @brief What the ai does in this state for a single frame.
/// 
/// Called each frame in accordance to AiBase::s_DELTA_TIME.
/// </summary>
void ai::states::AiRangedShootState::update()
{
	sf::Vector2f const aiToPlayer = m_ai->m_player.getPosition() - m_ai->m_position;
	this->updateTurn(aiToPlayer, 90.0f, 120.0f);
	this->updateTimer();
	this->updateShooting(aiToPlayer);
}

/// <summary>
/// @brief What ai does when exiting this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedShootState::exit()
{
}

/// <summary>
/// 
/// </summary>
void ai::states::AiRangedShootState::updateShooting(sf::Vector2f const & aiToPlayer)
{
	float const ANGLE_BETWEEN = std::abs(thor::polarAngle(m_ai->m_heading) - thor::polarAngle(aiToPlayer));
	if (ANGLE_BETWEEN < m_MIN_ANGLE
		&& m_timer > m_FIRE_RATE)
	{
		this->shoot(aiToPlayer);
		m_timer = sf::Time::Zero;
	}
}

/// <summary>
/// @brief Update the deployment timer.
/// 
/// 
/// </summary>
void ai::states::AiRangedShootState::updateTimer()
{
	m_timer += sf::seconds(m_ai->s_DELTA_TIME);
}

/// <summary>
/// @brief 
/// </summary>
/// <param name="direction"></param>
void ai::states::AiRangedShootState::shoot(sf::Vector2f const & direction)
{
	m_ai->m_bulletManager.shoot(m_ai->m_position, direction);
	m_ai->playAnimation(m_ai->m_sptrResources->m_animationShoot, m_ai->m_sptrResources->m_textureShoot, false);
}
