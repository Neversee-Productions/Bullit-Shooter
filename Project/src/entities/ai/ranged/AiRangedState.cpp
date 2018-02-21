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


/// <summary>
/// @brief clamps value between min and max.
/// 
/// if value is outside the range than it returns
/// the closest of the two.
/// </summary>
/// <param name="value">value to be clamped.</param>
/// <param name="min">minimum value, inclusive.</param>
/// <param name="max">maximum value, inclusive.</param>
/// <returns>the clamped value.</returns>
float ai::states::AiRangedState::clamp(float const & value, float const & min, float const & max) const
{
	float clampedValue = value > max ? max : value;
	clampedValue = clampedValue < min ? min : clampedValue;
	return clampedValue;
}


/// <summary>
/// @brief Checks if state is to be terminated.
/// 
/// True if the ai is within a small radius of the deployment area.
/// </summary>
/// <param name="aiToDeploy">read-only reference to the vector from the ai to the deploy point.</param>
/// <returns>True if ai is close enough to player to commence attack sequence.</returns>
bool ai::states::AiRangedState::checkState(sf::Vector2f const & aiToDeploy, float const & minDistance)
{
	return thor::length(aiToDeploy) < minDistance;
}

/// <summary>
/// @brief calculate the ai's new speed.
/// 
/// the speed is determined by the distance from aiToPlayer.
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
void ai::states::AiRangedState::updateSpeed(sf::Vector2f const & aiToDeploy, float const & speed)
{
	m_ai->m_speed = speed;
}

/// <summary>
/// @brief calculate the ai's heading and the angle he is looking at.
/// 
/// 
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player,</param>
void ai::states::AiRangedState::updateTurn(sf::Vector2f const & aiToDeploy, float const & maxTurnRate, float const & maxSpeed)
{
	float const MAX_TURN_RATE = maxTurnRate * (1.0f / m_ai->m_speed) * maxSpeed;
	float const TURN_ANGLE = this->clamp(thor::signedAngle(m_ai->m_heading, aiToDeploy), -(MAX_TURN_RATE), MAX_TURN_RATE);
	while (m_ai->m_angle > 360.0f)
	{
		m_ai->m_angle -= 360.0f;
	}
	while (m_ai->m_angle < -360.0f)
	{
		m_ai->m_angle += 360.0f;
	}
	m_ai->m_angle += TURN_ANGLE * m_DELTA_TIME;
	m_ai->m_heading = thor::unitVector(thor::rotatedVector(m_ai->m_heading, TURN_ANGLE * m_DELTA_TIME));
}

/// <summary>
/// @brief Calculate new position of ai.
/// 
/// New position calculated using heading for direction,
/// by speed, by delta time, in seconds so that the
/// position gets updated at a rate of per second.
/// </summary>
void ai::states::AiRangedState::updatePosition()
{
	m_ai->m_position += m_ai->m_heading * m_ai->m_speed * m_DELTA_TIME;
}

/// <summary>
/// @brief Generate random position within the deploy zone.
/// 
/// 
/// </summary>
/// <returns>deploy position generated within the deploy zone.</returns>
sf::Vector2f ai::states::AiRangedState::generateDeployPosition() const
{
	return sf::Vector2f{
		static_cast<float>(std::rand() % m_ai->m_onScreenRect.width + m_ai->m_onScreenRect.left),
		static_cast<float>(std::rand() % m_ai->m_onScreenRect.height + m_ai->m_onScreenRect.top)
	};
}
