#include "Entities\Player\Weapon.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
/// <param name="position">defines the position of the weapon rectangle</param>
Weapon::Weapon(sf::Vector2f position, bool const & flipped)
	: m_weaponSprite()
	, m_currentBullet(BulletTypes::Standard)
	, m_position(position)
	, m_animator(nullptr)
	, m_resources(nullptr)
{
	m_weaponSprite.setPosition(position);
	m_weaponSprite.setScale(0.75f, 0.75f);
	this->setFlipped(flipped);
}

/// <summary>
/// @brief Initialize weapon assets.
/// 
/// 
/// </summary>
/// <param name="sptrResources">shared pointer to our weapon resources.</param>
void Weapon::init(std::shared_ptr<Resources> sptrResources)
{
	m_resources = sptrResources;
	if (nullptr == m_animator)
	{
		m_animator = std::make_unique<WeaponAnimator>();
		auto & animator = *m_animator;
		
		int const & MAX_WEAPONS = Weapon::MAX_WEAPONS;
		for (int i = 0; i < MAX_WEAPONS; ++i)
		{
			auto & weaponAnimation = sptrResources->m_weaponAnimations.at(i);

			auto & beginAnimation = *weaponAnimation->first;
			animator.addAnimation(beginAnimation.m_id, *(beginAnimation.m_sptrFrames), beginAnimation.m_duration);

			auto & shootAnimation = *weaponAnimation->second;
			if (shootAnimation.m_duration.asSeconds() < 0.0f)
			{
				switch (static_cast<BulletTypes>(i))
				{
				case BulletTypes::Standard:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::Standard::getFireRate()));
					break;
				case BulletTypes::Empowered:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::Empowered::getFireRate()));
					break;
				case BulletTypes::DeathOrb:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::DeathOrb::getFireRate()));
					break;
				case BulletTypes::FireBlast:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::FireBlast::getFireRate()));
					break;
				case BulletTypes::HolySphere:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::HolySphere::getFireRate()));
					break;
				case BulletTypes::MagmaShot:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::MagmaShot::getFireRate()));
					break;
				case BulletTypes::NapalmSphere:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::NapalmSphere::getFireRate()));
					break;
				case BulletTypes::CometShot:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::CometShot::getFireRate()));
					break;
				case BulletTypes::NullWave:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::NullWave::getFireRate()));
					break;
				case BulletTypes::StaticSphere:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::StaticSphere::getFireRate()));
					break;
				case BulletTypes::PyroBlast:
					animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), sf::seconds(bullets::PyroBlast::getFireRate()));
					break;
				default:
					break;
				}
			}
			else
			{
				animator.addAnimation(shootAnimation.m_id, *(shootAnimation.m_sptrFrames), shootAnimation.m_duration);
			}
		}
		

		auto & startingWeaponAnimation = *sptrResources->m_weaponAnimations.at(static_cast<int>(m_currentBullet));
		auto & weaponBeginAnimation = *startingWeaponAnimation.first;
		auto & weaponShootAnimation = *startingWeaponAnimation.second;
		auto & weaponBeginTexture = *(startingWeaponAnimation.first->m_sptrTexture);
		m_weaponSprite.setTexture(weaponBeginTexture, true);
		m_weaponSprite.setOrigin(weaponBeginAnimation.m_origin);
		animator.playAnimation(startingWeaponAnimation.first->m_id, false);
	}
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
	m_animator->update(sf::seconds(deltaTime));
	m_animator->animate(m_weaponSprite);
	window.draw(m_weaponSprite);
}

/// <summary>
/// @brief update position vector.
/// 
/// 
/// </summary>
void Weapon::update(const sf::Vector2f& pos)
{
	if (!getIsFlipped())
	{
		sf::Vector2f const weaponPos = sf::Vector2f(pos.x - 75.0f, pos.y);
		m_weaponSprite.setPosition(weaponPos);
	}
	else
	{
		sf::Vector2f const weaponPos = sf::Vector2f(pos.x + 75.0f, pos.y);
		m_weaponSprite.setPosition(weaponPos);
	}
}

/// <summary>
/// @brief sets new position of rectangle.
/// 
/// 
/// </summary>
/// <param name="pos">defines new position</param>
void Weapon::setRectPos(sf::Vector2f pos)
{
	m_weaponSprite.setPosition(pos);
}

/// <summary>
/// @brief Sets whether the texture is flipped on the x-axis.
/// 
/// 
/// </summary>
/// <param name="flip">defines whether to flip or not to flip.</param>
void Weapon::setFlipped(bool const & flip)
{
	if (flip)
	{
		m_weaponSprite.scale(-1.0f, 1.0f);
	}
	else
	{
		m_weaponSprite.scale(1.0f, 1.0f);
	}
}

/// <summary>
/// @brief Plays the shoot animation.
/// 
/// 
/// </summary>
void Weapon::shoot()
{
	auto weaponID = static_cast<int>(m_currentBullet);
	if (weaponID >= Weapon::MAX_WEAPONS)
	{
		weaponID = 0;
	}
	auto & weaponShootAnimation = *(m_resources->m_weaponAnimations.at(weaponID)->second);
	std::string const & shootID = weaponShootAnimation.m_id;
	m_weaponSprite.setTexture(*weaponShootAnimation.m_sptrTexture, true);
	m_weaponSprite.setOrigin(weaponShootAnimation.m_origin);
	m_animator->playAnimation(shootID, false);
}

/// <summary>
/// @brief Plays the shoot animation.
/// 
/// 
/// </summary>
/// <param name="bulletType">Defines what weapon type to use.</param>
void Weapon::shoot(BulletTypes const & bulletType)
{

}

/// <summary>
/// @brief returns the rectangles position.
/// 
/// 
/// </summary>
/// <returns>returns a constant reference to the position</returns>
const sf::Vector2f & Weapon::getPosition()
{
	return m_weaponSprite.getPosition();
}

/// <summary>
/// @brief return the weapons current type.
/// 
/// 
/// </summary>
/// <returns>Constant reference to the bullet type</returns>
const BulletTypes & Weapon::getBulletType()
{
	return m_currentBullet;
}

/// <summary>
/// @brief returns whether the weapon is flipped.
/// 
/// Determined by checking if the weapon rectangle has a negative scale-x.
/// </summary>
/// <returns>returns true if flipped, else false.</returns>
bool const Weapon::getIsFlipped() const
{
	return m_weaponSprite.getScale().x < 0;
}

/// <summary>
/// @brief Changes the type of weapon according to the bullet type.
/// 
/// Based on the bullet type, the weapon changes is current texture,
/// and the associated animation that plays with that weapon type.
/// </summary>
/// <param name="bulletType">Defines a new bullet type and therefore its appropriate weapon type is selected.</param>
void Weapon::setType(BulletTypes const & bulletType)
{
	m_currentBullet = bulletType;
	auto weaponID = static_cast<int>(m_currentBullet);
	if (weaponID >= Weapon::MAX_WEAPONS)
	{
		weaponID = 0;
	}
	auto & weaponBeginAnimation = *(m_resources->m_weaponAnimations.at(weaponID)->first);
	auto & weaponShootAnimation = *(m_resources->m_weaponAnimations.at(weaponID)->second);
	std::string const & beginID = weaponBeginAnimation.m_id;
	std::string const & shootID = weaponShootAnimation.m_id;
	m_weaponSprite.setTexture(*weaponBeginAnimation.m_sptrTexture, true);
	m_weaponSprite.setOrigin(weaponBeginAnimation.m_origin);
	switch (bulletType)
	{
	default:

		break;
	}
	m_animator->playAnimation(beginID, false);
}
