#include "Entities\Asteroids\Asteroid.h"

float const Asteroid::INVULNERABILITY_FRAMES = 0.01f;
sf::Time const Asteroid::s_FLASH_TIME = sf::seconds(0.05f);

/// <summary>
/// @brief Setups resource pointer.
/// 
/// 
/// </summary>
/// <param name="sptrResources">shared pointer to asteroid resource.</param>
void Asteroid::setup(std::shared_ptr<Resources> sptrResources, js::json & jsonParser)
{
	setupFlashFrame(sptrResources->m_flashTextureRect, jsonParser.at("idle").at("flash_frame"));
	sptrResources->m_idleTexture = jsonParser.at("idle").at("texture").get<Resources::Texture>();
	sptrResources->m_explodeTexture = jsonParser.at("explode").at("texture").get<Resources::Texture>();
	sptrResources->m_explodeAnimation = jsonParser.at("explode").at("animation").get<Resources::Animation>();
}

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Asteroid::Asteroid(std::shared_ptr<Resources> sptrResources)
	: m_sptrResources(sptrResources)
	, m_rectangle(sf::Vector2f(200.0f, 200.0f))
	, m_circle(100.0f, 30u)
	, m_velocity(0.0f, 0.0f)
	, m_position(300.0f, 300.0f)
	, m_active(false)
	, m_explode(false)
	, m_spawnEnemy(false)
	, m_collisionCircle()
	, m_windowC2Rect()
	, m_health(10.0f)
	, m_invulnerable(false)
	, m_invulnTimer(0.0f)
	, UPDATE_DT(App::getUpdateDeltaTime())
	, UPDATE_TIME_DT(sf::seconds(UPDATE_DT))
	, m_animator()
	, m_explosionTimer(sf::milliseconds(0))
	, m_flashTimer(sf::milliseconds(0))
	, m_flash(false)
{
	const auto & windowRect = App::getViewC2Rect();
	const auto & extraHeight = m_rectangle.getGlobalBounds().height * 2.0f;
	m_windowC2Rect.min.x = 0.0f;
	m_windowC2Rect.min.y = -extraHeight;
	m_windowC2Rect.max.x = windowRect.max.x;
	m_windowC2Rect.max.y = windowRect.max.y;
	m_rectangle.setOrigin(m_rectangle.getGlobalBounds().width / 2, m_rectangle.getGlobalBounds().height / 2);
	m_rectangle.setPosition(m_position);
	
	// Initialize asteroid circle shape
	m_circle.setPosition(m_position);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setScale(sptrResources->m_idleTexture.m_scale);
	m_circle.setTexture(sptrResources->m_idleTexture.m_sptrTexture.get(), true);
	m_circle.setTextureRect(sptrResources->m_idleTexture.m_textureRect);
	
	// Initialize asteroid circle collider
	m_collisionCircle.r = m_circle.getRadius() * 0.75f;
	updateCollisionCircle();

	// Initialize asteroid explosion animation
	m_animator.addAnimation(
		sptrResources->m_explodeAnimation.m_id,
		sptrResources->m_explodeAnimation.m_frames,
		sptrResources->m_explodeAnimation.m_duration);
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
		m_invulnTimer += App::getUpdateDeltaTime();
		if (m_invulnTimer >= INVULNERABILITY_FRAMES)
		{
			m_invulnerable = false;
			m_invulnTimer = 0.0f;
		}
	}
	if (m_active)
	{
		if (m_explode)
		{
			m_explosionTimer += UPDATE_TIME_DT;
			if (m_explosionTimer > m_sptrResources->m_explodeAnimation.m_duration)
			{
				m_active = false;
			}
		}
		else
		{
			if (m_flash)
			{
				m_flashTimer += UPDATE_TIME_DT;
				if (m_flashTimer > s_FLASH_TIME)
				{
					m_flash = false;
					m_circle.setTextureRect(m_sptrResources->m_idleTexture.m_textureRect);
				}
			}
		}
		m_position += m_velocity * UPDATE_DT;
		m_rectangle.setPosition(m_position);
		m_circle.setPosition(m_position);
		m_circle.rotate(m_rotation * UPDATE_DT);
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
		if (m_explode)
		{
			m_animator.update(sf::seconds(deltaTime));
			m_animator.animate(m_circle);
		}
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
/// @brief this is the velocity getter.
/// 
/// 
/// </summary>
/// <returns>m_velocity, a vector2f that represents the velocity</returns>
sf::Vector2f Asteroid::getVelocity()
{
	return m_velocity;
}

/// <summary>
/// @brief getter for position.
/// 
/// 
/// </summary>
/// <returns>m_position a vector2f that represents the position.</returns>
sf::Vector2f Asteroid::getPosition()
{
	return m_position;
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
	m_position.x = static_cast<float>(temp);
}

/// <summary>
/// @brief method to reuse an asteroid.
/// 
/// generates new position and velocity values
/// sets the active to true.
/// </summary>
void Asteroid::reuseAsteroid()
{
	this->generateRandomVel();
	this->generateRandomPos();
	this->generateRandomRotation();
	this->generateRandomEnemy();
	m_health = 10.0f;
	m_explode = false;
	m_active = true;
	m_invulnerable = false;
	m_flash = false;
	m_flashTimer = sf::milliseconds(0);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setScale(m_sptrResources->m_idleTexture.m_scale);
	m_circle.setTexture(m_sptrResources->m_idleTexture.m_sptrTexture.get(), true);
	m_circle.setTextureRect(m_sptrResources->m_idleTexture.m_textureRect);
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
/// <param name="invurnState">determine if asteroid is to become invurnelable.</param>
void Asteroid::decrementHealth(float dmg, bool invurnState)
{
	if (!m_invulnerable)
	{
		m_health -= dmg;
		m_invulnerable = invurnState;
		if (m_health <= 0)
		{
			this->explode();
		}
		else
		{
			m_flash = true;
			m_flashTimer = sf::seconds(0.0f);
			m_circle.setTextureRect(m_sptrResources->m_flashTextureRect);
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
/// <returns>Return whether asteroid is active.</returns>
bool Asteroid::isActive()
{
	return m_active;
}

/// <summary>
/// @brief check if asteroid has exploded.
/// 
/// 
/// </summary>
/// <returns>Whether asteroid has exploded.</returns>
bool Asteroid::isExplosion() const
{
	return m_explode;
}

/// <summary>
/// @brief Start explosion animation and enter explode state.
/// 
/// 
/// </summary>
void Asteroid::explode()
{
	this->setVelocity({ 0.0f, 0.0f });
	m_rotation = 0.0f;
	m_explosionTimer = sf::Time();
	m_circle.setPosition(m_position);
	m_circle.setScale(m_sptrResources->m_explodeTexture.m_scale);
	m_circle.setOrigin({ m_circle.getRadius(), m_circle.getRadius() });
	m_circle.setTexture(m_sptrResources->m_explodeTexture.m_sptrTexture.get(), true);
	m_circle.setTextureRect(m_sptrResources->m_explodeTexture.m_textureRect);
	m_animator.playAnimation(m_sptrResources->m_explodeAnimation.m_id, false);
	m_explode = true;
}

/// <summary>
/// @brief Defines whether the asteroid contains a enemy.
/// 
/// 
/// </summary>
/// <returns>true if the asteroid contains a enemy.</returns>
bool Asteroid::containsEnemy() const
{
	return m_spawnEnemy;
}

/// <summary>
/// @brief this is a setter function that will set the new position.
/// 
/// 
/// </summary>
/// <param name="newPos">new position of the asteroid defined as a vector2f</param>
void Asteroid::setPosition(sf::Vector2f newPos)
{
	m_position = newPos;
	this->updateCollisionCircle();
}

/// <summary>
/// @brief setter for rotation.
/// 
/// 
/// </summary>
/// <param name="newRotation">new rotation value</param>
void Asteroid::setRotation(float newRotation)
{
	m_rotation = newRotation;
}

/// <summary>
/// @brief getter for the rotation value.
/// 
/// 
/// </summary>
/// <returns>rotation value as float in degrees</returns>
float Asteroid::getRotation()
{
	return m_rotation;
}

/// <summary>
/// @brief load up flash frame.
/// 
/// 
/// </summary>
/// <param name="flashFrame">reference to flash frame to be loaded.</param>
/// <param name="flashFrameParser">reference to json parser.</param>
void Asteroid::setupFlashFrame(sf::IntRect & flashFrame, js::json & flashFrameParser)
{
	flashFrame = sf::IntRect(
		flashFrameParser.at("x").get<int>()
		, flashFrameParser.at("y").get<int>()
		, flashFrameParser.at("w").get<int>()
		, flashFrameParser.at("h").get<int>()
	);
}

/// <summary>
/// @brief determines with a random chance of the asteroid containing a enemy.
/// 
/// 
/// </summary>
void Asteroid::generateRandomEnemy()
{
	int const CHANCE = std::rand() % 101;
	int const SPAWN_CHANCE = 100;
	m_spawnEnemy = (CHANCE <= SPAWN_CHANCE);
}

/// <summary>
/// @brief determines a random number for rotation speed.
/// 
/// 
/// </summary>
void Asteroid::generateRandomRotation()
{
	auto const randomWholeNumber = (std::rand() % 180) - 90;
	auto const randomDecimal = (std::rand() % 100000) / 100000;
	m_rotation = static_cast<float>(randomWholeNumber + randomDecimal); // generate number from -90.000 to 90.000 per second
}

/// <summary>
/// @brief json getter function.
/// 
/// Used by the json library when parsing the json file into 
/// Asteroid::Resources::Texture type.
/// </summary>
/// <param name="j">read-only reference to json file to be parsed</param>
/// <param name="textureData">reference to destination of data to be parsed</param>
void from_json(const js::json & j, Asteroid::Resources::Texture & textureData)
{
	// Resource handler will load in out texture for us.
	ResourceHandler & resourceHandler = ResourceHandler::get();

	std::string const JSON_KEY("key");
	std::string const JSON_PATH("path");
	std::string const JSON_ORIGIN("origin");
	std::string const JSON_SCALE("scale");
	std::string const JSON_FRAME("frame");

	textureData.m_id = j.at(JSON_KEY).get<std::string>();
	textureData.m_origin.x = j.at(JSON_ORIGIN).at("x").get<float>();
	textureData.m_origin.y = j.at(JSON_ORIGIN).at("y").get<float>();
	textureData.m_scale.x = j.at(JSON_SCALE).at("x").get<float>();
	textureData.m_scale.y = j.at(JSON_SCALE).at("y").get<float>();
	textureData.m_textureRect.left = j.at(JSON_FRAME).at("x").get<int>();
	textureData.m_textureRect.top = j.at(JSON_FRAME).at("y").get<int>();
	textureData.m_textureRect.width = j.at(JSON_FRAME).at("w").get<int>();
	textureData.m_textureRect.height = j.at(JSON_FRAME).at("h").get<int>();
	textureData.m_sptrTexture =
		resourceHandler.loadUp<sf::Texture>(j.at(JSON_PATH).get<std::string>(), textureData.m_id);
	textureData.m_sptrTexture->setSmooth(true);
}

/// <summary>
/// @brief json getter function.
/// 
/// Used by the json library when parsing the json file into 
/// Asteroid::Resources::Animation type.
/// </summary>
/// <param name="j">read-only reference to json file to be parsed</param>
/// <param name="animationData">reference to destination of data to be parsed</param>
void from_json(const js::json & j, Asteroid::Resources::Animation & animationData)
{
	ResourceHandler & resourceHandler = ResourceHandler::get();

	std::string const JSON_KEY("key");
	std::string const JSON_TEXTURE_KEY("texture_key");
	std::string const JSON_DURATION("duration");
	std::string const JSON_WIDTH("width");
	std::string const JSON_HEIGHT("height");
	std::string const JSON_ORIGIN("origin");
	std::string const JSON_FRAMES("frames");


	animationData.m_id = j.at(JSON_KEY).get<std::string>();
	animationData.m_duration = sf::seconds(j.at(JSON_DURATION).get<float>());
	animationData.m_origin.x = j.at(JSON_ORIGIN).at("x").get<float>();
	animationData.m_origin.y = j.at(JSON_ORIGIN).at("y").get<float>();
	animationData.m_sptrTexture = resourceHandler.loadUp<sf::Texture>("", j.at(JSON_TEXTURE_KEY).get<std::string>());

	animationData.m_frames = thor::FrameAnimation();
	{ // Initialize animation frames.
		sf::IntRect rect = { 0,0,0,0 };
		rect.width = j.at(JSON_WIDTH).get<int>();
		rect.height = j.at(JSON_HEIGHT).get<int>();
		for (auto & jsonNode : j.at(JSON_FRAMES))
		{
			rect.left = jsonNode.at("x").get<int>();
			rect.top = jsonNode.at("y").get<int>();

			animationData.m_frames.addFrame(1.0f, rect);
		}
	}
}
