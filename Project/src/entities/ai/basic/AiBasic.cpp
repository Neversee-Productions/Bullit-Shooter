#include "entities\ai\basic\AiBasicState.h"

std::string ai::AiBasic::s_SEEK_ID = "";
std::string ai::AiBasic::s_CHARGE_ID = "";
std::string ai::AiBasic::s_WINDUP_ID = "";
std::string ai::AiBasic::s_RECOVER_ID = "";
std::string ai::AiBasic::s_DEATH_ID = "";
bool const ai::AiBasic::s_COLOR_STATES = false;
float const ai::AiBasic::s_MAX_HEALTH = 10.0f;

/// <summary>
/// @brief Setups ai::AiBasic::Resources.
///
/// Loads all necessary resources for the basic enemy.
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="sptrEnemyResources">
/// shared pointer to our basic enemy resources, assumed to be a valid pointer (initialized).
/// @warning No checks are made as to the validity of the pointer.
/// </param>
/// <param name="basicEnemyParser">reference to loaded json file ready to be parsed.</param>
void ai::AiBasic::setup(
	std::shared_ptr<Resources> sptrResources
	, ResourceHandler & resourceHandler
	, js::json & basicEnemyParser)
{
	std::string const JSON_SEEK("seek");
	std::string const JSON_WINDUP("windup");
	std::string const JSON_CHARGE("charge");
	std::string const JSON_RECOVER("recover");
	std::string const JSON_DEATH("death");

	std::string const JSON_KEY("key");

	ai::AiBasic::s_SEEK_ID = basicEnemyParser.at(JSON_SEEK).at(JSON_KEY).get<std::string>();
	ai::AiBasic::s_WINDUP_ID = basicEnemyParser.at(JSON_WINDUP).at(JSON_KEY).get<std::string>();
	ai::AiBasic::s_CHARGE_ID = basicEnemyParser.at(JSON_CHARGE).at(JSON_KEY).get<std::string>();
	ai::AiBasic::s_RECOVER_ID = basicEnemyParser.at(JSON_RECOVER).at(JSON_KEY).get<std::string>();
	ai::AiBasic::s_DEATH_ID = basicEnemyParser.at(JSON_DEATH).at(JSON_KEY).get<std::string>();
	
	// Loading/Parsing Texture

	std::string const JSON_TEXTURE("texture");
	ai::AiBase::setup(sptrResources->m_textureSeek, resourceHandler, basicEnemyParser.at(JSON_SEEK).at(JSON_TEXTURE), ai::AiBasic::s_SEEK_ID);
	ai::AiBase::setup(sptrResources->m_textureWindup, resourceHandler, basicEnemyParser.at(JSON_WINDUP).at(JSON_TEXTURE), ai::AiBasic::s_WINDUP_ID);
	ai::AiBase::setup(sptrResources->m_textureCharge, resourceHandler, basicEnemyParser.at(JSON_CHARGE).at(JSON_TEXTURE), ai::AiBasic::s_CHARGE_ID);
	ai::AiBase::setup(sptrResources->m_textureRecover, resourceHandler, basicEnemyParser.at(JSON_RECOVER).at(JSON_TEXTURE), ai::AiBasic::s_RECOVER_ID);
	ai::AiBase::setup(sptrResources->m_textureDeath, resourceHandler, basicEnemyParser.at(JSON_DEATH).at(JSON_TEXTURE), ai::AiBasic::s_DEATH_ID);

	// Loading/Parsing Animations

	std::string const JSON_ANIMATION("animation");
	ai::AiBase::setup(sptrResources->m_animationSeek, resourceHandler, basicEnemyParser.at(JSON_SEEK).at(JSON_ANIMATION), ai::AiBasic::s_SEEK_ID);
	ai::AiBase::setup(sptrResources->m_animationWindup, resourceHandler, basicEnemyParser.at(JSON_WINDUP).at(JSON_ANIMATION), ai::AiBasic::s_WINDUP_ID);
	ai::AiBase::setup(sptrResources->m_animationCharge, resourceHandler, basicEnemyParser.at(JSON_CHARGE).at(JSON_ANIMATION), ai::AiBasic::s_CHARGE_ID);
	ai::AiBase::setup(sptrResources->m_animationRecover, resourceHandler, basicEnemyParser.at(JSON_RECOVER).at(JSON_ANIMATION), ai::AiBasic::s_RECOVER_ID);
	ai::AiBase::setup(sptrResources->m_animationDeath, resourceHandler, basicEnemyParser.at(JSON_DEATH).at(JSON_ANIMATION), ai::AiBasic::s_DEATH_ID);
}

/// <summary>
/// @brief Default constructor.
/// 
/// Construct our map of actions.
/// </summary>
ai::AiBasic::AiBasic(Player const & player, sf::Vector2f const & position)
	: AiBase()
	, m_position(position)
	, m_speed(0.0f)
	, m_heading{ 0.0f, 1.0f }
	, m_angle(0.0f)
	, m_player(player)
	, m_collisionShape({ 50.0f, 50.0f })
	, m_collisionRect()
	, m_renderQuad({80.0f , 80.0f}) // Implicitly call sf::Vector2f() constructor
	, m_stateStack()
	, m_sptrState(nullptr)
	, m_sptrResources(nullptr)
	, m_animator()
	, m_healthbarOffstet(50.0f)
	, m_healthBarStartWidth(60.0f)
{
	m_healthBar.setSize(sf::Vector2f(m_healthBarStartWidth, 10.0f));
	m_healthBar.setFillColor(sf::Color::Green);
	m_healthBar.setOrigin(0.0f, m_healthBar.getLocalBounds().height / 2);
	m_healthBar.setPosition(m_position.x - (m_healthBar.getLocalBounds().width / 2), m_position.y + m_healthbarOffstet);
	m_active = true;
	m_health = s_MAX_HEALTH;
	this->initRenderingQuad();
}

/// <summary>
/// @brief Initialize resource dependant members.
/// 
/// 
/// </summary>
/// <param name="sptrResources">shared pointer to already loaded resources.</param>
void ai::AiBasic::init(std::shared_ptr<Resources> sptrResources)
{
	m_sptrResources = sptrResources;
	this->setTexture(this->s_SEEK_ID);
	this->initAnimations();
	this->initStates();
}

/// <summary>
/// @brief update current state.
/// 
/// 
/// </summary>
void ai::AiBasic::update()
{
	m_healthBar.setPosition(m_position.x - (m_healthBar.getLocalBounds().width / 2), m_position.y + m_healthbarOffstet);
	m_healthBar.setScale(m_health / s_MAX_HEALTH, 1.0f);
	if (m_showHealthbar)
	{
		m_healthbarShowTimer += App::getUpdateDeltaTime();
		if (m_healthbarShowTimer >= m_healthbarShowForTime)
		{
			m_showHealthbar = false;
			m_healthbarShowTimer = 0.0f;
		}
	}
	m_sptrState->update();
	this->updateHitbox(m_renderQuad);
}

/// <summary>
/// @brief 
/// </summary>
/// <param name="window">reference to target window.</param>
/// <param name="deltaTime">read-only reference to delta time between last render calls.</param>
void ai::AiBasic::draw(Window & window, float const & deltaTime)
{
	if (m_showHealthbar)
	{
		m_healthBar.setFillColor(sf::Color(
			255u - static_cast<sf::Uint8>(220u * (m_health / s_MAX_HEALTH)),
			static_cast<sf::Uint8>(220u * (m_health / s_MAX_HEALTH)) + 25u,
			0u,
			255u));
		window.draw(m_healthBar);
	}
	m_sptrState->draw(window, deltaTime);
}

/// <summary>
/// Passes the call to the current state.
/// </summary>
/// <param name="collision">read-only reference to a 2d collision AABB rectangle.</param>
/// <returns>True if a collision has occured, else false.</returns>
bool ai::AiBasic::checkCollision(tinyh::c2Circle const & collision) const
{
	return m_sptrState->checkCollision(collision);
}

/// <summary>
/// Passes the call to the current state.
/// </summary>
/// <param name="collision">read-only reference to a 2d collision AABB rectangle.</param>
/// <returns>True if a collision has occured, else false.</returns>
bool ai::AiBasic::checkCollision(tinyh::c2AABB const & collision) const
{
	return m_sptrState->checkCollision(collision);
}

/// <summary>
/// Passes the call to the current state.
/// </summary>
/// <param name="collision">read-only reference to a 2d collision AABB rectangle.</param>
/// <returns>True if a collision has occured, else false.</returns>
bool ai::AiBasic::checkCollision(tinyh::c2Capsule const & collision) const
{
	return m_sptrState->checkCollision(collision);
}

/// <summary>
/// @brief Gets the rotated collision box.
/// 
/// 
/// </summary>
/// <returns>read-only reference the AABB collision box.</returns>
tinyh::c2AABB const & ai::AiBasic::getCollisionAABB() const
{
	return m_collisionRect;
}

void ai::AiBasic::spawn(sf::Vector2f const & spawnPosition, sf::Vector2f const & spawnHeading)
{
	m_position = spawnPosition;
	m_speed = 0.0f;
	m_heading = spawnHeading;
	m_angle = 0.0f;
	m_health = s_MAX_HEALTH;
	this->setActive(true);
	this->setTexture(this->s_SEEK_ID);
	this->initStates();
}

/// <summary>
/// @brief Constructs a base pointer and passes the call down.
/// 
/// 
/// </summary>
/// <param name="sptrState">shared pointer to our new state.</param>
/// <param name="rememberPrevious">tells whether or not to add the new state to the stack.</param>
void ai::AiBasic::setState(std::shared_ptr<ai::states::Seek> sptrState, bool rememberPrevious)
{
	std::shared_ptr<ai::states::Basic> sptrBaseState = sptrState;
	this->setState(sptrBaseState, rememberPrevious);
}

/// <summary>
/// @brief Updates collision box using the rectangle shape.
/// 
/// Uses the shape's transform to form a AABB Rectangle.
/// </summary>
/// <param name="box">read-only reference to a rectangle shape</param>
void ai::AiBasic::updateHitbox(sf::RectangleShape const & box)
{
	m_collisionShape.setPosition(box.getPosition());
	m_collisionShape.setScale(box.getScale());
	m_collisionShape.setOrigin(m_collisionShape.getSize() * 0.5f);

	auto const & boxBounds = m_collisionShape.getGlobalBounds();
	m_collisionRect.min = { boxBounds.left, boxBounds.top };
	m_collisionRect.max = { boxBounds.left + boxBounds.width, boxBounds.top + boxBounds.height };
}

/// <summary>
/// @brief Constructs a base pointer and passes the call down.
/// 
/// 
/// </summary>
/// <param name="sptrState">shared pointer to our new state.</param>
/// <param name="rememberPrevious">tells whether or not to add the new state to the stack.</param>
void ai::AiBasic::setState(std::shared_ptr<ai::states::Charge> sptrState, bool rememberPrevious)
{
	std::shared_ptr<ai::states::Basic> sptrBaseState = sptrState;
	this->setState(sptrBaseState, rememberPrevious);
}

/// <summary>
/// @brief Set a new state.
/// 
/// Assigns our curret state pointer to the new state and pushes that
/// new state onto the stack.
/// If is the passed pointer is nullptr than we remove the state on
/// top of the stack and assign the newest top of the stack to our
/// current state pointer.
/// </summary>
/// <param name="sptrState">
/// pointer to our new state, nullptr will cause us to use the
/// stack of states, using a design pattern of 
/// 
/// Pushdown Automata
/// http://gameprogrammingpatterns.com/state.html#pushdown-automata
/// </param>
/// <param name="rememberPrevious">tells whether or not to add the new state to the stack.</param>
void ai::AiBasic::setState(std::shared_ptr<ai::states::Basic> sptrState, bool rememberPrevious)
{
	if (nullptr != m_sptrState)
	{
		m_sptrState->exit();
	}
	if (nullptr != sptrState)
	{
		if (false == rememberPrevious)
		{
			if (!m_stateStack.empty())
			{
				m_stateStack.pop();
			}
		}
		m_stateStack.push(sptrState);
		m_sptrState = sptrState;
	}
	else if (!m_stateStack.empty())
	{
		m_stateStack.pop();
		m_sptrState = m_stateStack.top();
	}
	m_sptrState->enter();
}

/// <summary>
/// @brief Initialize the different basic ai states.
/// 
/// 
/// </summary>
void ai::AiBasic::initStates()
{
	while (!m_stateStack.empty())
	{
		m_stateStack.pop();
	}
	std::shared_ptr<ai::states::Seek> sptrFirstState = std::make_shared<ai::states::Seek>(ai::states::Seek(*this));
	this->setState(sptrFirstState, true);
}

/// <summary>
/// @brief Initialize the rendering quad.
/// 
/// 
/// </summary>
void ai::AiBasic::initRenderingQuad()
{
	//sf::Color const QUAD_FILL = sf::Color::Yellow;
	sf::FloatRect const QUAD_BOUND_BOX = m_renderQuad.getGlobalBounds();
	sf::Vector2f const QUAD_ORIGIN = { QUAD_BOUND_BOX.width * 0.5f, QUAD_BOUND_BOX.height *0.5f };

	//m_renderQuad.setFillColor(QUAD_FILL);
	m_renderQuad.setOrigin(QUAD_ORIGIN);
}

/// <summary>
/// @brief Initialize all of the animator's animations.
/// 
/// 
/// </summary>
void ai::AiBasic::initAnimations()
{
	m_animator.addAnimation(
		m_sptrResources->m_animationSeek.m_id,
		m_sptrResources->m_animationSeek.m_frames,
		m_sptrResources->m_animationSeek.m_duration);
	m_animator.addAnimation(
		m_sptrResources->m_animationWindup.m_id,
		m_sptrResources->m_animationWindup.m_frames,
		m_sptrResources->m_animationWindup.m_duration);
	m_animator.addAnimation(
		m_sptrResources->m_animationCharge.m_id,
		m_sptrResources->m_animationCharge.m_frames,
		m_sptrResources->m_animationCharge.m_duration);
	m_animator.addAnimation(
		m_sptrResources->m_animationRecover.m_id,
		m_sptrResources->m_animationRecover.m_frames,
		m_sptrResources->m_animationRecover.m_duration);
}

/// <summary>
/// @brief set the ai to the new texture state.
/// 
/// 
/// </summary>
/// <param name="id">specifies the id of the state.</param>
void ai::AiBasic::setTexture(std::string const & id)
{
	if (id == this->s_SEEK_ID)
	{
		//m_renderQuad.setOrigin(m_sptrResources->m_textureSeek.m_origin);
		m_renderQuad.setScale(m_sptrResources->m_textureSeek.m_scale);
		m_renderQuad.setTexture(m_sptrResources->m_textureSeek.m_sptrTexture.get(), true);
		m_renderQuad.setTextureRect(m_sptrResources->m_textureSeek.m_textureRect);
	}
	else if (id == this->s_WINDUP_ID)
	{
		//m_renderQuad.setOrigin(m_sptrResources->m_textureWindup.m_origin);
		m_renderQuad.setScale(m_sptrResources->m_textureWindup.m_scale);
		m_renderQuad.setTexture(m_sptrResources->m_textureWindup.m_sptrTexture.get(), true);
		m_renderQuad.setTextureRect(m_sptrResources->m_textureWindup.m_textureRect);
	}
	else if (id == this->s_CHARGE_ID)
	{
		//m_renderQuad.setOrigin(m_sptrResources->m_textureCharge.m_origin);
		m_renderQuad.setScale(m_sptrResources->m_textureCharge.m_scale);
		m_renderQuad.setTexture(m_sptrResources->m_textureCharge.m_sptrTexture.get(), true);
		m_renderQuad.setTextureRect(m_sptrResources->m_textureCharge.m_textureRect);
	}
	else if (id == this->s_RECOVER_ID)
	{
		//m_renderQuad.setOrigin(m_sptrResources->m_textureRecover.m_origin);
		m_renderQuad.setScale(m_sptrResources->m_textureRecover.m_scale);
		m_renderQuad.setTexture(m_sptrResources->m_textureRecover.m_sptrTexture.get(), true);
		m_renderQuad.setTextureRect(m_sptrResources->m_textureRecover.m_textureRect);
	}
}

/// <summary>
/// @brief Play's the specified animation.
/// 
/// 
/// </summary>
/// <param name="id">used to id the animation and the texture.</param>
/// <param name="loop">indicates whether to loop the animation.</param>
void ai::AiBasic::playAnimation(std::string const & id, bool const & loop)
{
	this->setTexture(id);
	m_animator.playAnimation(id, loop);
}

/// <summary>
/// @brief Checks if a animation is playing, stops it and resets the render quad's texture frame.
/// 
/// 
/// </summary>
void ai::AiBasic::stopAnimation()
{
	if (m_animator.isPlayingAnimation())
	{
		this->setTexture(m_animator.getPlayingAnimation());
		m_animator.stopAnimation();
	}
}
