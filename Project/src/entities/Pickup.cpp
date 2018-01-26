﻿#include "Entities\Pickup.h"

Pickup::Pickup()
{

}

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
/// <param name="resources">defines resources</param>
/// <param name="position">defines position</param>
/// <param name="size">defines size</param>
/// <param name="origin">defines origin</param>
Pickup::Pickup(std::shared_ptr<Resources> resources,sf::Vector2f position, sf::Vector2f size, BulletTypes const & pickupType)
	: m_rightPosition(position)
	, m_leftPosition(position)
	, m_size(size)
	, m_active(true)
	, m_effectSprite()
	, m_animator()
	
{
	if (m_size.x > m_size.y) //make collision circle same as the bigger side
	{
		m_collisionCircle.r = m_size.x;
	}
	else
	{
		m_collisionCircle.r = m_size.y;
	}
	m_collisionCircle.p.x = m_rightPosition.x;
	m_collisionCircle.p.y = m_rightPosition.y;

	auto const & pickupData = resources->m_pickups.at(pickupType);

	m_rightSprite.setPosition(m_rightPosition);
	m_rightSprite.setOrigin(pickupData.m_origin);
	m_rightSprite.setScale(pickupData.m_scale);
	m_rightSprite.setTexture(*pickupData.m_texture, true);
	m_rightSprite.setTextureRect(pickupData.m_frame);

	m_leftSprite.setPosition(m_rightPosition);
	m_leftSprite.setOrigin(pickupData.m_origin);
	m_leftSprite.setScale(pickupData.m_scale);
	m_leftSprite.setTexture(*pickupData.m_texture, true);
	m_leftSprite.setTextureRect(pickupData.m_frame);

	auto const & effectTextureData = resources->m_effect.m_texture;

	m_effectSprite.setPosition(position);
	m_effectSprite.setOrigin(effectTextureData.m_origin);
	m_effectSprite.setScale(effectTextureData.m_scale);
	m_effectSprite.setTexture(*effectTextureData.m_texture, true);
	m_effectSprite.setTextureRect(effectTextureData.m_frame);

	m_animator.addAnimation(resources->m_effect.m_animation.m_id, *resources->m_effect.m_animation.m_sptrFrames, resources->m_effect.m_animation.m_duration);
}

/// <summary>
/// @brief update object.
/// 
/// 
/// </summary>
void Pickup::update()
{
	if (m_active)
	{
		m_rightPosition += m_rightVelocity;
		m_leftPosition += m_leftVelocity;
		m_rightSprite.setPosition(m_rightPosition);
		m_leftSprite.setPosition(m_leftPosition);
	}
}

/// <summary>
/// @brief Render object.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void Pickup::draw(Window & window, const float & deltaTime)
{
	if (m_active)
	{
		m_animator.update(sf::seconds(deltaTime));
		m_animator.animate(m_effectSprite);
		window.draw(m_effectSprite);
		window.draw(m_rightSprite);
		window.draw(m_leftSprite);
	}
}

/// <summary>
/// @brief Sets the position of right sprite.
/// 
/// 
/// </summary>
/// <param name="pos">Define new position of sprite</param>
void Pickup::setRightPosition(sf::Vector2f pos)
{
	m_rightPosition = pos;
}

/// <summary>
/// @brief Sets the position of left sprite.
/// 
/// 
/// </summary>
/// <param name="pos">Define new position of sprite</param>
void Pickup::setLeftPosition(sf::Vector2f pos)
{
	m_leftPosition = pos;
}

/// <summary>
/// @brief Return the position of right sprite.
/// 
/// 
/// </summary>
/// <returns>returns the position of sprite</returns>
sf::Vector2f const Pickup::getRightPosition() const
{
	return m_rightPosition;
}

/// <summary>
/// @brief Return the position of left sprite.
/// 
/// 
/// </summary>
/// <returns>returns the position of sprite</returns>
sf::Vector2f const & Pickup::getLeftPosition() const
{
	return m_leftPosition;
}

/// <summary>
/// @brief Set new size.
/// 
/// 
/// </summary>
/// <param name="size">new size of the object</param>
void Pickup::setSize(sf::Vector2f size)
{
	m_size = size;
}

/// <summary>
/// @brief get the current size.
/// 
/// 
/// </summary>
/// <returns>current size of object.</returns>
sf::Vector2f const Pickup::getSize() const
{
	return m_size;
}

/// <summary>
/// @brief Set velocity of right sprite.
/// 
/// 
/// </summary>
/// <param name="vel">new velocity.</param>
void Pickup::setRightVelocity(sf::Vector2f vel)
{
	m_rightVelocity = vel;
}

/// <summary>
/// @brief Set velocity of left sprite.
/// 
/// 
/// </summary>
/// <param name="vel">new velocity.</param>
void Pickup::setLeftVelocity(sf::Vector2f vel)
{
	m_leftVelocity = vel;
}

/// <summary>
/// @brief check if the pickup is active.
/// 
/// 
/// </summary>
/// <returns>return active boolean.</returns>
bool const Pickup::isActive() const
{
	return m_active;
}

/// <summary>
/// @brief set the active state.
/// 
/// 
/// </summary>
/// <param name="active">new active state.</param>
void Pickup::setActive(bool active)
{
	m_active = active;
}

