#include "Scenes\GameScene\Entities\Player\Bullets\StaticSphere.h"

const float bullets::StaticSphere::s_FIRE_RATE = 1.0f;


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::StaticSphere::StaticSphere()
	: Bullet()
	, m_pulse(false)
	, m_pulseTimer(0.0f)
	, m_pulseCircleCollider()
	, m_uptrStasisAnimator(nullptr)
{
	m_speed = 6.0f * 60.0f;
	m_velocity.y = -m_speed;
	m_angle = -90.0f;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(40.0f, 40.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
	//m_pulseCircle.setFillColor(sf::Color::Red);
	m_pulseCircle.setRadius(0.0f);
	//m_pulseCircle.setOutlineThickness(6.0f);
	//m_pulseCircle.setOutlineColor(sf::Color::Red);
	//m_pulseCircle.setFillColor(sf::Color(0u, 0u, 0u, 0u));
	m_pulseCircle.setPosition(m_position);
	m_pulseCircle.setOrigin(m_pulseCircle.getRadius(), m_pulseCircle.getRadius());

	updateCollisionCircle();

	//change collision rectangle
	updateBox();
}

/// <summary>
/// @brief Bullet resource initialization.
/// 
/// Use our pointer to loaded resources to link our resources.
/// </summary>
/// <param name="sptrResources">shared pointer to loaded resources.</param>
void bullets::StaticSphere::init(std::shared_ptr<Resources> sptrResources)
{
	if (sptrResources->m_sptrLoopAnimation)
	{
		auto & loopAnimation = *sptrResources->m_sptrLoopAnimation;
		m_uptrStasisAnimator = std::make_unique<StasisAnimator>();
		m_uptrStasisAnimator->addAnimation(loopAnimation.m_id, *loopAnimation.m_sptrFrames, loopAnimation.m_duration);
		this->setAnimation(loopAnimation.m_id);
	}
	Bullet::init(sptrResources);
}

/// <summary>
/// @brief update the position and velocity.
/// 
/// 
/// </summary>
void bullets::StaticSphere::update()
{
	m_pulseTimer += UPDATE_DT;
	Bullet::update();
	if (m_pulseTimer > 0.3f)
	{
		m_pulseCircle.setRadius(m_pulseCircle.getRadius() + 1.0f);
		m_pulseCircle.setOrigin(m_pulseCircle.getRadius(), m_pulseCircle.getRadius());
		m_pulseCircle.setPosition(m_position);
		m_pulse = true;

		updateCollisionCircle();
	}
	if (m_pulseCircle.getRadius() > 100)
	{
		m_pulseCircle.setRadius(0.0f);
		m_pulseTimer = 0.0f;

		updateCollisionCircle();
	}
	updateBox();
}

/// <summary>
/// @brief overloaded draw.
/// 
/// will draw a circle when needed
/// </summary>
/// <param name="window">reference to window object</param>
/// <param name="deltaTime">constant reference to deltatime</param>
void bullets::StaticSphere::draw(Window & window, const float & deltaTime)
{
	if (m_pulse)
	{
		if (m_uptrStasisAnimator)
		{
			auto & stasisAnimator = *m_uptrStasisAnimator;
			stasisAnimator.update(sf::seconds(deltaTime));
			stasisAnimator.animate(m_pulseCircle);
		}
		window.draw(m_pulseCircle);
	}
	Bullet::draw(window, deltaTime);
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns>value of fire rate</returns>
float bullets::StaticSphere::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief overloaded set active method.
/// 
/// This method will check if active is being set to false
/// if yes then reset circle to original size.
/// </summary>
/// <param name="active">determines the active state of bullet</param>
void bullets::StaticSphere::setActive(bool active)
{
	if (!active)
	{
		m_pulseCircle.setRadius(0.0f);
		m_pulseTimer = 0.0f;
	}
	m_active = active;
}

/// <summary>
/// @brief this function will update the collision circle.
/// 
/// Change the radius and position of our collision circle.
/// </summary>
void bullets::StaticSphere::updateCollisionCircle()
{
	m_pulseCircleCollider.p.x = m_pulseCircle.getPosition().x;
	m_pulseCircleCollider.p.y = m_pulseCircle.getPosition().y;
	m_pulseCircleCollider.r = m_pulseCircle.getRadius();
}

/// <summary>
/// @brief overriden circle collision.
/// 
/// This version will have to take into account the pulse circle as well
/// as the bullet shape itself,
/// </summary>
/// <param name="other">circle to check collision against</param>
/// <returns>If collision is happening returns true</returns>
bool bullets::StaticSphere::checkCircleCollision(const tinyh::c2Circle & other)
{
	if (tinyh::c2CircletoAABB(other, m_bulletC2Rect) || tinyh::c2CircletoCircle(other, m_pulseCircleCollider))
	{
		return true;
	}
	return false;
}

/// <summary>
/// @brief Sets the animation based on its id.
/// 
/// 
/// </summary>
/// <param name="animationId">ID of the animation to be set.</param>
void bullets::StaticSphere::setAnimation(std::string const & animationId)
{
	if (m_uptrLoopAnimator && m_uptrLoopAnimator->isPlayingAnimation())
	{
		m_uptrLoopAnimator->stopAnimation();
	}
	Bullet::setAnimation(animationId);
	if (m_sptrResources)
	{
		if (nullptr != m_sptrResources->m_sptrLoopAnimation)
		{
			auto & loopAnimation = *m_sptrResources->m_sptrLoopAnimation;
			if (animationId == loopAnimation.m_id)
			{
				m_pulseCircle.setTexture(loopAnimation.m_sptrTexture.get(), true);
				m_uptrStasisAnimator->playAnimation(animationId, true);
			}
		}
	}
}
