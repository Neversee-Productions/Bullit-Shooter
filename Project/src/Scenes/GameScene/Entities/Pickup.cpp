#include "Scenes\GameScene\Entities\Pickup.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
/// <param name="texture">defines texture</param>
/// <param name="position">defines position</param>
/// <param name="size">defines size</param>
/// <param name="origin">defines origin</param>
Pickup::Pickup(std::shared_ptr<sf::Texture> texture, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin)
	: m_texture(texture)
	, m_position(position)
	, m_size(size)
	, m_origin(origin)
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
}

void Pickup::update()
{

}

void Pickup::draw(Window & window, const float & deltaTime)
{
}
