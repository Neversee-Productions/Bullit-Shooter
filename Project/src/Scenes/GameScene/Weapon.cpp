#include "Scenes\GameScene\Weapon.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
/// <param name="position">defines the position of the weapon rectangle</param>
Weapon::Weapon(sf::Vector2f position)
	: m_weaponRect()
	, m_currentBullet(BulletTypes::Standard)
	, m_position(position)
	, TEMPTIME(0.0f)
{
	m_weaponRect.setPosition(position);
	m_weaponRect.setFillColor(sf::Color::Blue);
	m_weaponRect.setSize(sf::Vector2f(25.0f, 25.0f));
	m_weaponRect.setOrigin(m_weaponRect.getSize().x / 2, m_weaponRect.getSize().y / 2);
}

/// <summary>
/// @brief Render entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void Weapon::draw(Window & window, const float & deltaTime)
{
	window.draw(m_weaponRect);
}

/// <summary>
/// @brief update position vector.
/// 
/// 
/// </summary>
void Weapon::update(const sf::Vector2f& pos)
{
	//REMOVE TEMPTIME
	//TEMPTIME += App::getUpdateDeltaTime();
	//if (TEMPTIME >= 7.0f)
	//{
	//	auto bulletTypeNum = static_cast<int>(m_currentBullet);
	//	m_currentBullet = static_cast<BulletTypes>(++bulletTypeNum);
	//	TEMPTIME = 0.0f;
	//}
	//REMOVE TEMPTIME


	m_weaponRect.setPosition(pos);
}
