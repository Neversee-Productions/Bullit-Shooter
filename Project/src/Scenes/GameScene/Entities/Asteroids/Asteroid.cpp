#include "Scenes\GameScene\Entities\Asteroids\Asteroid.h"

float const Asteroid::INVULNERABILITY_FRAMES = 0.01f;


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Asteroid::Asteroid()
	: m_rectangle(sf::Vector2f(200.0f, 200.0f))
	, m_circle(10.0f)
	, m_velocity(0.0f, 0.0f)
	, m_position(300.0f, 300.0f)
	, m_active(false)
	, m_collisionCircle()
	, m_windowC2Rect()
	, m_health(10.0f)
	, m_invulnerable(false)
	, m_invulnTimer(0.0f)
	, UPDATE_DT(App::getUpdateDeltaTime())
{
	const auto & windowRect = App::getViewC2Rect();
	const auto & extraHeight = m_rectangle.getGlobalBounds().height * 2.0f;
	m_windowC2Rect.min.x = 0.0f;
	m_windowC2Rect.min.y = -extraHeight;
	m_windowC2Rect.max.x = windowRect.max.x;
	m_windowC2Rect.max.y = windowRect.max.y;
	m_rectangle.setOrigin(m_rectangle.getGlobalBounds().width / 2, m_rectangle.getGlobalBounds().height / 2);
	m_rectangle.setPosition(m_position);
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setPosition(m_position);
	m_circle.setRadius(m_rectangle.getGlobalBounds().width / 2);
	m_circle.setOrigin(m_rectangle.getOrigin());
	m_collisionCircle.r = m_circle.getRadius();
	updateCollisionCircle();
}

/// <summary>
/// @brief update position based on velocity.
/// 
/// 
/// </summary>
void Asteroid::update()
{
	if (m_invulnerable)
	{
		m_circle.setFillColor(sf::Color::Blue);
		m_invulnTimer += App::getUpdateDeltaTime();
		if (m_invulnTimer >= INVULNERABILITY_FRAMES)
		{
			m_invulnerable = false;
			m_invulnTimer = 0.0f;
		}
	}
	else
	{
		m_circle.setFillColor(sf::Color::Red);
	}
	if (m_active)
	{
		m_position += m_velocity * UPDATE_DT;
		m_rectangle.setPosition(m_position);
		m_circle.setPosition(m_position);
		updateCollisionCircle();
		updateWindowCollisions();
	}
}

/// <summary>
/// @brief Draw if active.
/// 
/// 
/// </summary>
/// <param name="window">reference to the window</param>
/// <param name="deltaTime">constant reference to delta time</param>
void Asteroid::draw(Window & window, const float & deltaTime)
{
	if (m_active)
	{
		//window.draw(m_rectangle);
		window.draw(m_circle);
	}
}

/// <summary>
/// @brief sets the velocity of the asteroid.
/// 
/// 
/// </summary>
void Asteroid::setVelocity(sf::Vector2f vel)
{
	m_velocity = vel;
}

/// <summary>
/// @brief Sets active of asteroid to passed parameter.
/// 
/// 
/// </summary>
/// <param name="active">new value of m_active</param>
void Asteroid::setActive(bool active)
{
	m_active = active;
}

/// <summary>
/// @brief updates the position of the collision circle.
/// 
/// 
/// </summary>
void Asteroid::updateCollisionCircle()
{
	m_collisionCircle.p.x = m_circle.getPosition().x;
	m_collisionCircle.p.y = m_circle.getPosition().y;
}

/// <summary>
/// @brief generates a random velocity.
/// 
/// Velocity is not fully random and will be constrained
/// to go more or less towards the screen.
/// </summary>
void Asteroid::generateRandomVel()
{
	m_velocity.x = (rand() % 7 - 3) * 60.0f; //generate number from 3 to -3
	m_velocity.y = (rand() % 4 + 2) * 60.0f; //generate number from 2 to 5
}

/// <summary>
/// @brief generate random position.
/// 
/// Generates a random y position x will always be the same
/// when spawning a new asteroid.
/// </summary>
void Asteroid::generateRandomPos()
{
	m_position.y = -m_rectangle.getGlobalBounds().height; //x stays same offscreen value
	
	int temp = rand() % App::getViewSize().x; //generate number between 0 and right side of screen
	m_position.x = temp;
}

/// <summary>
/// @brief method to reuse an asteroid.
/// 
/// generates new position and velocity values
/// sets the active to true.
/// </summary>
void Asteroid::reuseAsteroid()
{
	generateRandomVel();
	generateRandomPos();
	m_health = 10.0f;
	m_active = true;
}

/// <summary>
/// @brief Update collision with window.
/// 
/// If asteroid is offscreen it becomes inactive.
/// </summary>
void Asteroid::updateWindowCollisions()
{
	if (!tinyh::c2CircletoAABB(m_collisionCircle, m_windowC2Rect))
	{
		m_active = false;
	}
}

/// <summary>
/// @brief returns a constant reference to the collision rectangle.
/// 
/// 
/// </summary>
/// <returns>Constant reference to collision box</returns>
tinyh::c2Circle Asteroid::getCollisionCircle()
{
	return m_collisionCircle;
}

/// <summary>
/// @brief Decrement health by a certain value.
/// 
/// 
/// </summary>
/// <param name="dmg">amount of health to decrement</param>
void Asteroid::decrementHealth(float dmg)
{
	if (!m_invulnerable)
	{
		m_health -= dmg;
		m_invulnerable = true;
		if (m_health <= 0)
		{
			m_active = false;
		}
	}
}

/// <summary>
/// @brief check if currently invulnerable
/// 
/// 
/// </summary>
/// <returns>returns the invulnerability bool</returns>
bool Asteroid::isInvulnerable()
{
	return m_invulnerable;
}

/// <summary>
/// @brief knocks the asteroid back by a few pixels.
/// 
/// 
/// </summary>
void Asteroid::knockback()
{
	m_velocity.y -= bullets::CometShot::s_KNOCK_BACK;
}

/// <summary>
/// @brief check if asteroid is active.
/// 
/// 
/// </summary>
/// <returns>Return whether aseroid is active.</returns>
bool Asteroid::isActive()
{
	return m_active;
}

