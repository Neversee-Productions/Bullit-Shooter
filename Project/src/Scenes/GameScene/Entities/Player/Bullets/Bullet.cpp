#include "Scenes\GameScene\Entities\Player\Bullets\Bullet.h"

double const bullets::Bullet::DEG_TO_RAD = thor::Pi / 180.0f;
//static std::string const s_LOOP_ID;
std::string const bullets::Bullet::s_LOOP_ID = "loop";
std::string const bullets::Bullet::s_IMPACT_ID = "impact";

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::Bullet::Bullet()
	: m_position(0.0f,0.0f)
	, m_bulletRect()
	, m_active(false)
	, m_type(BulletTypes::Standard)
	, m_bulletC2Rect()
	, m_velocity(0.0f,0.0f)
	, m_speed(0)
	, m_angle(0)
	, tempRect()
	, m_damage(1.0f)
	, UPDATE_DT(App::getUpdateDeltaTime())
	, m_sptrResources(nullptr)
	, m_uptrLoopAnimator(nullptr)
	, m_uptrImpactAnimator(nullptr)
	, m_hit(false)
{
	m_bulletRect.setPosition(0.0f,0.0f);
	m_bulletRect.setFillColor(sf::Color::White);
	m_bulletRect.setSize(sf::Vector2f(50.0f, 50.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	//define the bullet collision rectangle
	updateBox();

	tempRect.setPosition(m_bulletC2Rect.min.x, m_bulletC2Rect.min.y);
	tempRect.setSize(sf::Vector2f(m_bulletC2Rect.max.x - m_bulletC2Rect.min.x, m_bulletC2Rect.max.x - m_bulletC2Rect.min.y));
	tempRect.setFillColor(sf::Color::Yellow);
}

/// <summary>
/// @brief Bullet resource initialization.
/// 
/// Use our pointer to loaded resources to link our resources.
/// </summary>
/// <param name="sptrResources">shared pointer to loaded resources.</param>
void bullets::Bullet::init(std::shared_ptr<Resources> sptrResources)
{
	m_sptrResources = sptrResources;
	if (m_sptrResources->m_sptrLoopAnimation)
	{
		auto & loopAnimation = *sptrResources->m_sptrLoopAnimation;
		m_uptrLoopAnimator = std::make_unique<BulletAnimator>();
		m_uptrLoopAnimator->addAnimation(loopAnimation.m_id, *loopAnimation.m_sptrFrames, loopAnimation.m_duration);
		this->setAnimation(loopAnimation.m_id);
	}
	if (m_sptrResources->m_sptrImpactAnimation)
	{
		auto & impactAnimation = *sptrResources->m_sptrImpactAnimation;
		m_uptrImpactAnimator = std::make_unique<BulletAnimator>();
		m_uptrImpactAnimator->addAnimation(impactAnimation.m_id, *impactAnimation.m_sptrFrames, impactAnimation.m_duration);
	}
}

/// <summary>
/// @brief default update.
/// 
/// updates bullet position based on velocity
/// </summary>
void bullets::Bullet::update()
{
	if (m_hit)
	{
		if (m_uptrImpactAnimator)
		{
			auto & impactAnimator = *m_uptrImpactAnimator;
			if (!impactAnimator.isPlayingAnimation())
			{
				this->setActive(false);
			}
		}
		else
		{
			this->setActive(false);
		}
	}
	else
	{
		m_position += m_velocity * UPDATE_DT;
	}
	m_bulletRect.setPosition(m_position.x, m_position.y);
	updateBox();
	tempRect.setPosition(m_bulletC2Rect.min.x, m_bulletC2Rect.min.y);
	tempRect.setSize(sf::Vector2f(m_bulletC2Rect.max.x - m_bulletC2Rect.min.x, m_bulletC2Rect.max.y - m_bulletC2Rect.min.y));
}

/// <summary>
/// @brief Render entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void bullets::Bullet::draw(Window & window, const float & deltaTime)
{
	if (m_uptrLoopAnimator)
	{
		auto & loopAnimator = *m_uptrLoopAnimator;
		loopAnimator.update(sf::seconds(deltaTime));
		loopAnimator.animate(m_bulletRect);
	}
	if (m_uptrImpactAnimator)
	{
		auto & impactAnimator = *m_uptrImpactAnimator;
		impactAnimator.update(sf::seconds(deltaTime));
		if (impactAnimator.isPlayingAnimation())
		{
			impactAnimator.animate(m_bulletRect);
		}
	}
	m_bulletRect.setRotation(m_angle);
	window.draw(m_bulletRect);
}

/// <summary>
/// @brief get the collision box.
/// 
/// 
/// </summary>
/// <returns>The collision box</returns>
tinyh::c2AABB bullets::Bullet::getCollisionRect()
{
	return m_bulletC2Rect;
}

/// <summary>
/// @brief response to bullet colliding with a entity.
/// 
/// 
/// </summary>
void bullets::Bullet::hit()
{
	this->setAnimation(s_IMPACT_ID);
	m_hit = true;
}

/// <summary>
/// @brief set the active of bullet.
/// 
/// 
/// </summary>
/// <param name="active">the active boolean</param>
void bullets::Bullet::setActive(bool active)
{
	m_active = active;
	if (m_active)
	{
		this->setAnimation(s_LOOP_ID);
		m_hit = false;
	}
}

/// <summary>
/// @brief update bounding box.
/// 
/// 
/// </summary>
void bullets::Bullet::updateBox()
{
	const auto & bulletRect = m_bulletRect.getGlobalBounds();
	m_bulletC2Rect.min.x = bulletRect.left;
	m_bulletC2Rect.min.y = bulletRect.top;
	m_bulletC2Rect.max.x = bulletRect.left + bulletRect.width;
	m_bulletC2Rect.max.y = bulletRect.top + bulletRect.height;
}

/// <summary>
/// @brief Set the position vector
/// 
/// 
/// </summary>
/// <param name="pos">defines the new position vector</param>
void bullets::Bullet::setPosition(const sf::Vector2f& pos)
{
	m_position = pos;
	m_bulletRect.setPosition(pos);
	updateBox();
}

/// <summary>
/// @brief set angle of fire.
/// 
/// 
/// </summary>
/// <param name="angle">reference to angle of fire</param>
void bullets::Bullet::setAngle(const float & angle)
{
	m_angle = angle;
}

/// <summary>
/// @brief update the velocity based on angle.
/// 
/// 
/// </summary>
void bullets::Bullet::updateVelocityVector()
{
	const auto & angleRad = thor::toRadian(m_angle);
	m_velocity.x = cos(angleRad) * m_speed;
	m_velocity.y = sin(angleRad) * m_speed;
}

/// <summary>
/// @brief return the active boolean.
/// 
/// 
/// </summary>
/// <returns>active bool</returns>
bool bullets::Bullet::isActive() const
{
	return m_active;
}

/// <summary>
/// @brief check collision against a circle.
/// 
///
/// </summary>
/// <param name="other">the circle to collide with</param>
/// <returns>true if collided</returns>
bool bullets::Bullet::checkCircleCollision(const tinyh::c2Circle & other)
{
	if (tinyh::c2CircletoAABB(other, m_bulletC2Rect))
	{
		return true;
	}
	return false;
}

/// <summary>
/// @brief access damage of the bullet.
/// 
/// 
/// </summary>
/// <returns></returns>
const float & bullets::Bullet::getDamage()
{
	return m_damage;
}

/// <summary>
/// @brief acquires whether or not the bullet is in the impact state.
/// 
/// 
/// </summary>
/// <returns>true if in impact state, else false</returns>
bool const & bullets::Bullet::isImpact() const
{
	return m_hit;
}

/// <summary>
/// @brief Sets the animation based on its id.
/// 
/// 
/// </summary>
/// <param name="animationId">ID of the animation to be set.</param>
void bullets::Bullet::setAnimation(std::string const & animationId)
{
	if (animationId != s_IMPACT_ID)
	{
		if (m_uptrImpactAnimator && m_uptrImpactAnimator->isPlayingAnimation())
		{
			m_uptrImpactAnimator->stopAnimation();
		}
	}
	if (m_uptrLoopAnimator && m_uptrLoopAnimator->isPlayingAnimation())
	{
		m_uptrLoopAnimator->stopAnimation();
	}
	
	
	if (m_sptrResources)
	{
		if (nullptr != m_sptrResources->m_sptrLoopAnimation)
		{
			auto & loopAnimation = *m_sptrResources->m_sptrLoopAnimation;
			if (animationId == loopAnimation.m_id)
			{
				m_bulletRect.setTexture(loopAnimation.m_sptrTexture.get(), true);
				m_uptrLoopAnimator->playAnimation(animationId, true);
			}
		}
		if (nullptr != m_sptrResources->m_sptrImpactAnimation)
		{
			auto & impactAnimation = *m_sptrResources->m_sptrImpactAnimation;
			if (animationId == impactAnimation.m_id)
			{
				m_bulletRect.setTexture(impactAnimation.m_sptrTexture.get(), true);
				if (!m_uptrImpactAnimator->isPlayingAnimation())
				{
					m_uptrImpactAnimator->playAnimation(animationId);
				}
			}
		}
	}
}





