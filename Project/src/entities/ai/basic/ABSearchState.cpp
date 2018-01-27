#include "entities\ai\basic\ABSearchState.h"

/// <summary>
/// @brief Basic Search State constructor.
/// 
/// Sets all constants for the current state.
/// </summary>
/// <param name="aiUnit">reference of ai unit that will call this state.</param>
ai::states::AiBasicSearchState::AiBasicSearchState(AiBasic & aiUnit)
	: AiBasicState(aiUnit)
	, m_DELTA_TIME(AiBase::s_DELTA_TIME)
	, m_MAX_SPEED(60.0f)
	, m_MAX_TURN_RATE(60.0f)
	, m_MIN_DISTANCE(100.0f)
{
}

/// <summary>
/// @brief What the ai does when entering this state.
/// 
/// Start loop animation.
/// </summary>
void ai::states::AiBasicSearchState::enter()
{
	m_ai.m_animator.playAnimation(ai::Basic::s_IDLE_ID, true);
}

/// <summary>
/// @brief What the ai does in this state for a single frame.
/// 
/// Called each frame in accordance to AiBase::s_DELTA_TIME.
/// </summary>
void ai::states::AiBasicSearchState::update()
{
	sf::Vector2f const AI_TO_PLAYER = m_ai.m_player.getPosition() - m_ai.m_position;
	this->updateState(AI_TO_PLAYER);
	this->updateSpeed(AI_TO_PLAYER);
	this->updateTurn(AI_TO_PLAYER);
	this->updatePosition();
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
void ai::states::AiBasicSearchState::draw(Window & window, float const & deltaTime)
{
	m_ai.m_renderQuad.setPosition(m_ai.m_position);
	m_ai.m_renderQuad.setRotation(m_ai.m_angle + 90.0f);
	m_ai.m_animator.update(sf::seconds(deltaTime));
	m_ai.m_animator.animate(m_ai.m_renderQuad);
	window.draw(m_ai.m_renderQuad);
}

/// <summary>
/// @brief What ai does when exiting this animation.
/// 
/// Stop current animation loop.
/// </summary>
void ai::states::AiBasicSearchState::exit()
{
	if (m_ai.m_animator.isPlayingAnimation())
	{
		m_ai.m_animator.stopAnimation();
	}
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
float ai::states::AiBasicSearchState::clamp(float const & value, float const & min, float const & max) const
{
	if (value > max)
	{
		return max;
	}
	else if (value < min)
	{
		return min;
	}
	return value;
}

/// <summary>
/// @brief checks if state is to be terminated and responds appropriatly.
/// 
/// 
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
void ai::states::AiBasicSearchState::updateState(sf::Vector2f const & aiToPlayer)
{
	if (this->checkState(aiToPlayer))
	{
		std::shared_ptr<ai::states::Basic> sptrNextState =
			std::make_shared<ai::states::Charge>(ai::states::Charge(m_ai));
		m_ai.setState(sptrNextState);
	}
}

/// <summary>
/// @brief Checks if state is to be terminated.
/// 
/// State terminates if player is close enough for the ai to attack.
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
/// <returns>True if ai is close enough to player to commence attack sequence.</returns>
bool ai::states::AiBasicSearchState::checkState(sf::Vector2f const & aiToPlayer)
{


	return false;
}

/// <summary>
/// @brief calculate the ai's new speed.
/// 
/// the speed is determined by the distance from aiToPlayer.
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
void ai::states::AiBasicSearchState::updateSpeed(sf::Vector2f const & aiToPlayer)
{
	m_ai.m_speed = m_MAX_SPEED;
}



/// <summary>
/// @brief calculate the ai's heading and the angle he is looking at.
/// 
/// 
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player,</param>
void ai::states::AiBasicSearchState::updateTurn(sf::Vector2f const & aiToPlayer)
{
	float const MAX_TURN_RATE = m_MAX_TURN_RATE * (1.0f / m_ai.m_speed) * m_MAX_SPEED;
	float const TURN_ANGLE = this->clamp(thor::signedAngle(m_ai.m_heading, aiToPlayer), -(MAX_TURN_RATE), MAX_TURN_RATE);
	while (m_ai.m_angle > 360.0f)
	{
		m_ai.m_angle -= 360.0f;
	}
	while (m_ai.m_angle < -360.0f)
	{
		m_ai.m_angle += 360.0f;
	}
	m_ai.m_angle += TURN_ANGLE * m_DELTA_TIME;
	m_ai.m_heading = thor::unitVector(thor::rotatedVector(m_ai.m_heading, TURN_ANGLE * m_DELTA_TIME));
}

/// <summary>
/// @brief Calculate new position of ai.
/// 
/// New position calculated using heading for direction,
/// by speed, by delta time, in seconds so that the
/// position gets updated at a rate of per second.
/// </summary>
void ai::states::AiBasicSearchState::updatePosition()
{
	m_ai.m_position += m_ai.m_heading * m_ai.m_speed * m_DELTA_TIME;
}
