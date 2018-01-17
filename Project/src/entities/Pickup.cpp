#include "Entities\Pickup.h"

Pickup::Pickup()
{

}

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
/// <param name="texture">defines texture</param>
/// <param name="position">defines position</param>
/// <param name="size">defines size</param>
/// <param name="origin">defines origin</param>
Pickup::Pickup(/*std::shared_ptr<sf::Texture> texture,*/sf::Vector2f position, sf::Vector2f size)
	: m_position(position)
	, m_size(size)
	, m_active(true)
{
	if (m_size.x > m_size.y) //make collision circle same as the bigger side
	{
		m_collisionCircle.r = m_size.x;
	}
	else
	{
		m_collisionCircle.r = m_size.y;
	}
	m_collisionCircle.p.x = m_position.x;
	m_collisionCircle.p.y = m_position.y;
	m_rectangle.setSize(m_size);
	m_rectangle.setPosition(m_position);
	m_rectangle.setOrigin(m_rectangle.getGlobalBounds().width / 2, m_rectangle.getGlobalBounds().height);
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
		m_position += m_velocity;
		m_rectangle.setPosition(m_position);
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
		window.draw(m_rectangle);
	}
}

/// <summary>
/// @brief Sets the position of object.
/// 
/// 
/// </summary>
/// <param name="pos">Define new position of object</param>
void Pickup::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

/// <summary>
/// @brief Return the position.
/// 
/// 
/// </summary>
/// <returns>returns the position of object</returns>
sf::Vector2f const Pickup::getPosition() const
{
	return m_position;
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
/// @brief Set velocity of object.
/// 
/// 
/// </summary>
/// <param name="vel">new velocity.</param>
void Pickup::setVelocity(sf::Vector2f vel)
{
	m_velocity = vel;
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

