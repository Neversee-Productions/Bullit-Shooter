#include "entities\ai\ranged\AiRanged.h"

float const ai::AiRanged::s_MAX_HEALTH = 20.0f;
sf::Vector2f const ai::AiRanged::s_SIZE = { 60.0f, 60.0f };
std::string ai::AiRanged::s_MOVE_ID = "";
std::string ai::AiRanged::s_DEPLOY_ID = "";
std::string ai::AiRanged::s_SHOOT_ID = "";
std::string ai::AiRanged::s_EBOLA_ID = "";
bool const ai::AiRanged::s_COLOR_QUAD = false;
float const ai::AiRanged::s_C2_RADIUS = 25.0f;

/// <summary>
/// @brief Ranged Ai Default constructor.
/// 
/// Initialize member variables.
/// </summary>
/// <param name="player">read-only reference to the player.</param>
/// <param name="position">starting position.</param>
ai::AiRanged::AiRanged(Player const & player, sf::Vector2f position)
	: ai::AiBase()
	, m_player(player)
	, m_position(position)
	, m_speed(0.0f)
	, m_heading({ 0.0f, 1.0f })
	, m_angle(0.0f)
	, m_collisionCircle()
	, m_renderQuad()
	, m_animator()
	, m_onScreenRect({ 100, 100 }, { App::getViewSizeI().x - 200, (App::getViewSizeI().y / 2) - 100 })
	, m_stateStack()
	, m_sptrState(nullptr)
	, m_sptrResources(nullptr)
	, m_bulletManager()
	, m_healthbarOffstet(50.0f)
	, m_healthBarStartWidth(60.0f)
{
	m_healthBar.setSize(sf::Vector2f(m_healthBarStartWidth, 10.0f));
	m_healthBar.setFillColor(sf::Color::Green);
	m_healthBar.setOrigin(0.0f, m_healthBar.getLocalBounds().height / 2);
	m_healthBar.setPosition(m_position.x - (m_healthBar.getLocalBounds().width / 2), m_position.y + m_healthbarOffstet);
	m_active = true;
	m_health = s_MAX_HEALTH;
	m_collisionCircle.r = s_C2_RADIUS;
}


/// <summary>
/// @brief Setups ai::AiRanged::Resources.
///
/// Loads all necessary resources for the ranged enemy.
/// </summary>
/// <param name="resourceHandler">
/// reference to resource handler, loads our resources using json parser and an ID.
/// </param>
/// <param name="sptrEnemyResources">
/// shared pointer to our basic enemy resources, assumed to be a valid pointer (initialized).
/// @warning No checks are made as to the validity of the pointer.
/// </param>
/// <param name="basicEnemyParser">reference to loaded json file ready to be parsed.</param>
void ai::AiRanged::setup(
	std::shared_ptr<ai::Resources> sptrResources
	, ResourceHandler & resourceHandler
	, js::json & rangedEnemyParser)
{
	std::string const JSON_MOVE("move");
	std::string const JSON_DEPLOY("deploy");
	std::string const JSON_SHOOT("shoot");
	std::string const JSON_SPIT("ebola");

	std::string const JSON_KEY("key");

	ai::AiRanged::s_MOVE_ID = rangedEnemyParser.at(JSON_MOVE).at(JSON_KEY).get<std::string>();
	ai::AiRanged::s_DEPLOY_ID = rangedEnemyParser.at(JSON_DEPLOY).at(JSON_KEY).get<std::string>();
	ai::AiRanged::s_SHOOT_ID = rangedEnemyParser.at(JSON_SHOOT).at(JSON_KEY).get<std::string>();
	ai::AiRanged::s_EBOLA_ID = rangedEnemyParser.at(JSON_SPIT).at(JSON_KEY).get<std::string>();

	// Loading/Parsing Texture

	std::string const JSON_TEXTURE("texture");
	ai::AiBase::setup(
		sptrResources->m_textureMove,
		resourceHandler,
		rangedEnemyParser.at(JSON_MOVE).at(JSON_TEXTURE),
		ai::AiRanged::s_MOVE_ID);
	ai::AiBase::setup(
		sptrResources->m_textureDeploy,
		resourceHandler,
		rangedEnemyParser.at(JSON_DEPLOY).at(JSON_TEXTURE),
		ai::AiRanged::s_DEPLOY_ID
	);
	ai::AiBase::setup(
		sptrResources->m_textureShoot,
		resourceHandler,
		rangedEnemyParser.at(JSON_SHOOT).at(JSON_TEXTURE),
		ai::AiRanged::s_SHOOT_ID
	);
	ai::AiBase::setup(
		sptrResources->m_textureEbola,
		resourceHandler,
		rangedEnemyParser.at(JSON_SPIT).at(JSON_TEXTURE),
		ai::AiRanged::s_EBOLA_ID
	);

	// Loading/Parsing Animations

	std::string const JSON_ANIMATION("animation");
	ai::AiBase::setup(
		sptrResources->m_animationMove,
		resourceHandler,
		rangedEnemyParser.at(JSON_MOVE).at(JSON_ANIMATION),
		ai::AiRanged::s_MOVE_ID);
	ai::AiBase::setup(
		sptrResources->m_animationDeploy,
		resourceHandler,
		rangedEnemyParser.at(JSON_DEPLOY).at(JSON_ANIMATION),
		ai::AiRanged::s_DEPLOY_ID
	);
	ai::AiBase::setup(
		sptrResources->m_animationShoot,
		resourceHandler,
		rangedEnemyParser.at(JSON_SHOOT).at(JSON_ANIMATION),
		ai::AiRanged::s_SHOOT_ID
	);
	ai::AiBase::setup(
		sptrResources->m_animationEbola,
		resourceHandler,
		rangedEnemyParser.at(JSON_SPIT).at(JSON_ANIMATION),
		ai::AiRanged::s_EBOLA_ID
	);
}

/// <summary>
/// @brief initialize resources.
/// 
/// 
/// </summary>
/// <param name="sptrResources">shared pointer to loaded resources.</param>
void ai::AiRanged::init(std::shared_ptr<ai::Resources> sptrResources)
{
	m_sptrResources = sptrResources;
	m_bulletManager.init(sptrResources);
	this->initAnimations();
	this->initStates();
}

/// <summary>
/// @brief Update ranged ai's current state.
/// 
/// 
/// </summary>
void ai::AiRanged::update()
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
	if (this->getActive())
	if (this->getActive() && m_sptrState)
	{
		m_sptrState->update();
		this->updateHitbox();
	}
	else if (!m_sptrState)
	{
		this->setActive(false);
	}
	m_bulletManager.update();
}

/// <summary>
/// @brief Draw ranged ai's current state.
/// 
/// 
/// </summary>
/// <param name="window">reference to target draw window.</param>
/// <param name="deltaTime">read-only reference to delta time since last draw call.</param>
void ai::AiRanged::draw(Window & window, float const & deltaTime)
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
	if (this->getActive() && m_sptrState)
	{
		m_sptrState->draw(window, deltaTime);
	}
	else if (!m_sptrState)
	{
		this->setActive(false);
	}
	m_bulletManager.draw(window, deltaTime);
}

/// <summary>
/// @brief Spawn enemy at specified position.
/// 
/// 
/// </summary>
/// <param name="spawnPosition">determines the spawn point</param>
void ai::AiRanged::spawn(sf::Vector2f const & spawnPosition)
{
	m_active = true;
	m_health = s_MAX_HEALTH;
	m_position = spawnPosition;
	m_speed = 0.0f;
	m_heading = { 0.0f, 1.0f };
	m_angle = 0.0f;
	while (!m_stateStack.empty())
	{
		m_stateStack.pop();
	}
	std::shared_ptr<states::AiRangedState>(nullptr).swap(m_sptrState);
	this->setState(std::make_shared<states::AiRangedMoveState>(this), false);
}

/// <summary>
/// Passes the call to the current state.
/// </summary>
/// <param name="collision">read-only reference to a 2d collision AABB rectangle.</param>
/// <returns>True if a collision has occured, else false.</returns>
bool ai::AiRanged::checkCollision(tinyh::c2Circle const & collision) const
{
	return false;
}

/// <summary>
/// Passes the call to the current state.
/// </summary>
/// <param name="collision">read-only reference to a 2d collision AABB rectangle.</param>
/// <returns>True if a collision has occured, else false.</returns>
bool ai::AiRanged::checkCollision(tinyh::c2AABB const & collision) const
{
	return false;
}

/// <summary>
/// Passes the call to the current state.
/// </summary>
/// <param name="collision">read-only reference to a 2d collision AABB rectangle.</param>
/// <returns>True if a collision has occured, else false.</returns>
bool ai::AiRanged::checkCollision(tinyh::c2Capsule const & collision) const
{
	return false;
}

/// <summary>
/// @brief Updates AiRanged::m_collisionShape and AiRanged::m_collisionRect.
/// 
/// 
/// </summary>
void ai::AiRanged::updateHitbox()
{
	m_collisionCircle.p = { m_position.x, m_position.y };
}

/// <summary>
/// @brief Defines ai's new animation.
/// 
/// 
/// </summary>
/// <param name="animation">read-only reference to the animation.</param>
/// <param name="texture">read-only reference to the texture.</param>
/// <param name="loop">read-only reference whether to loop or not.</param>
void ai::AiRanged::playAnimation(Resources::Animation const & animation, Resources::Texture const & texture, bool const & loop)
{
	m_renderQuad.setScale(texture.m_scale);
	m_renderQuad.setTexture(*texture.m_sptrTexture, true);
	m_renderQuad.setTextureRect(texture.m_textureRect);
	m_renderQuad.setOrigin(texture.m_origin);
	m_animator.playAnimation(animation.m_id, loop);
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
/// stack of states, using the design pattern
/// 
/// Pushdown Automata
/// http://gameprogrammingpatterns.com/state.html#pushdown-automata
/// </param>
/// <param name="rememberPrevious">tells whether or not to add the new state to the stack.</param>
void ai::AiRanged::setState(std::shared_ptr<ai::states::AiRangedState> sptrNewState, bool rememberPrevious)
{
	if (nullptr != m_sptrState)
	{
		m_sptrState->exit();
	}
	if (nullptr != sptrNewState)
	{
		if (false == rememberPrevious)
		{
			if (!m_stateStack.empty())
			{
				m_stateStack.pop();
			}
		}
		m_stateStack.push(sptrNewState);
		m_sptrState = sptrNewState;
	}
	else if (!m_stateStack.empty())
	{
		m_stateStack.pop();
		m_sptrState = m_stateStack.top();
	}
	m_sptrState->enter();
}

/// <summary>
/// @brief Initialize the finite state machine.
/// 
/// 
/// </summary>
void ai::AiRanged::initStates()
{
	while (!m_stateStack.empty())
	{
		m_stateStack.pop();
	}
	this->setState(std::make_shared<ai::states::AiRangedMoveState>(ai::states::AiRangedMoveState(this)), false);
}

/// <summary>
/// @brief Initialize all animations.
/// 
/// 
/// </summary>
void ai::AiRanged::initAnimations()
{
	this->initAnimation(m_sptrResources->m_animationMove);
	this->initAnimation(m_sptrResources->m_animationDeploy);
	this->initAnimation(m_sptrResources->m_animationShoot);
}

/// <summary>
/// @brief Add individual animation to animator map.
/// 
/// 
/// </summary>
/// <param name="animation">read-only reference loaded animation data.</param>
void ai::AiRanged::initAnimation(Resources::Animation const & animation)
{
	m_animator.addAnimation(
		animation.m_id,
		animation.m_frames,
		animation.m_duration
	);
}
