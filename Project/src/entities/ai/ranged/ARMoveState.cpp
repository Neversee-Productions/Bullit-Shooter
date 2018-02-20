#include "entities\ai\ranged\ARMoveState.h"

float const ai::states::AiRangedMoveState::s_MAX_SPEED = 120.f;
float const ai::states::AiRangedMoveState::s_MAX_TURN_RATE = 120.0f;
float const ai::states::AiRangedMoveState::s_MIN_DISTANCE = 30.0f;

/// <summary>
/// @brief Default constructor.
/// 
/// Pass ai unit into base constructor.
/// </summary>
/// <param name="aiUnit">reference to ai unit.</param>
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
		m_ai->m_renderQuad.setFillColor(sf::Color::Green);
	}
	m_ai->m_deployPosition = this->generateDeployPosition();

	m_ai->m_renderQuad.setScale(m_ai->m_sptrResources->m_textureMove.m_scale);
	m_ai->m_renderQuad.setTexture(m_ai->m_sptrResources->m_textureMove.m_sptrTexture.get(), true);
	m_ai->m_renderQuad.setTextureRect(m_ai->m_sptrResources->m_textureMove.m_textureRect);
	m_ai->m_renderQuad.setOrigin(m_ai->m_renderQuad.getSize() * 0.5f);
	m_ai->m_animator.playAnimation(m_ai->m_sptrResources->m_animationMove.m_id, true);
}

/// <summary>
/// @brief What the ai does in this state for a single frame.
/// 
/// Called each frame in accordance to AiBase::s_DELTA_TIME.
/// </summary>
void ai::states::AiRangedMoveState::update()
{
	sf::Vector2f const AI_TO_DEPLOY = m_ai->m_deployPosition - m_ai->m_position;
	this->updateSpeed(AI_TO_DEPLOY);
	this->updateTurn(AI_TO_DEPLOY);
	this->updatePosition();
	this->updateState(AI_TO_DEPLOY);
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
void ai::states::AiRangedMoveState::draw(Window & window, float const & deltaTime)
{
	m_ai->m_renderQuad.setPosition(m_ai->m_position);
	m_ai->m_renderQuad.setRotation(m_ai->m_angle + 90.0f);
	m_ai->m_animator.update(sf::seconds(deltaTime));
	m_ai->m_animator.animate(m_ai->m_renderQuad);
	window.draw(m_ai->m_renderQuad);
}

/// <summary>
/// @brief What ai does when exiting this state.
/// 
/// 
/// </summary>
void ai::states::AiRangedMoveState::exit()
{
	if (m_ai->m_animator.isPlayingAnimation())
	{
		m_ai->m_animator.stopAnimation();
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
float ai::states::AiRangedMoveState::clamp(float const & value, float const & min, float const & max) const
{
	float clampedValue = value > max ? max : value;
	clampedValue = clampedValue < min ? min : clampedValue;
	return clampedValue;
}

/// <summary>
/// @brief checks if state is to be terminated and responds appropriatly.
/// 
/// 
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
void ai::states::AiRangedMoveState::updateState(sf::Vector2f const & aiToDeploy)
{
	if (this->checkState(aiToDeploy))
	{
		//typedef ai::states::AiRangedState NewState;
		//std::shared_ptr<NewState> newState = std::make_shared<NewState>();
		//m_ai->setNewState<NewState>(newState);
		m_ai->m_renderQuad.setFillColor(sf::Color::Red);
	}
}

/// <summary>
/// @brief Checks if state is to be terminated.
/// 
/// True if the ai is within a small radius of the deployment area.
/// </summary>
/// <param name="aiToDeploy">read-only reference to the vector from the ai to the deploy point.</param>
/// <returns>True if ai is close enough to player to commence attack sequence.</returns>
bool ai::states::AiRangedMoveState::checkState(sf::Vector2f const & aiToDeploy)
{
	return thor::length(aiToDeploy) < AiRangedMoveState::s_MIN_DISTANCE;
}

/// <summary>
/// @brief calculate the ai's new speed.
/// 
/// the speed is determined by the distance from aiToPlayer.
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player.</param>
void ai::states::AiRangedMoveState::updateSpeed(sf::Vector2f const & aiToDeploy)
{
	m_ai->m_speed = AiRangedMoveState::s_MAX_SPEED;
}

/// <summary>
/// @brief calculate the ai's heading and the angle he is looking at.
/// 
/// 
/// </summary>
/// <param name="aiToPlayer">read-only reference to the vector from the ai to the player,</param>
void ai::states::AiRangedMoveState::updateTurn(sf::Vector2f const & aiToDeploy)
{
	float const MAX_TURN_RATE = s_MAX_TURN_RATE * (1.0f / m_ai->m_speed) * s_MAX_SPEED;
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
void ai::states::AiRangedMoveState::updatePosition()
{
	m_ai->m_position += m_ai->m_heading * m_ai->m_speed * m_DELTA_TIME;
}

/// <summary>
/// @brief Generate random position within the deploy zone.
/// 
/// 
/// </summary>
/// <returns>deploy position generated within the deploy zone.</returns>
sf::Vector2f ai::states::AiRangedMoveState::generateDeployPosition() const
{
	return sf::Vector2f {
		static_cast<float>(std::rand() % m_ai->m_onScreenRect.width + m_ai->m_onScreenRect.left),
		static_cast<float>(std::rand() % m_ai->m_onScreenRect.height + m_ai->m_onScreenRect.top)
	};
}
