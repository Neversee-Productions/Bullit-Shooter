#include "entities\ai\ranged\AiRanged.h"

float const ai::AiRanged::s_MAX_HEALTH = 10.0f;
sf::Vector2f const ai::AiRanged::s_SIZE = { 60.0f, 60.0f };
std::string ai::AiRanged::s_MOVE_ID = "";
bool const ai::AiRanged::s_COLOR_QUAD = false;

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
	, m_active(true)
	, m_health(s_MAX_HEALTH)
	, m_position(position)
	, m_speed(0.0f)
	, m_heading({ 0.0f, 1.0f })
	, m_angle(0.0f)
	, m_collisionShape(s_SIZE)
	, m_collisionRect()
	, m_renderQuad(s_SIZE)
	, m_animator()
	, m_onScreenRect({ 100, 0 }, { 1100, 200 })
	, m_stateStack()
	, m_sptrState(nullptr)
	, m_sptrResources(nullptr)
{
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
	std::shared_ptr<Resources> sptrResources
	, ResourceHandler & resourceHandler
	, js::json & rangedEnemyParser)
{
	std::string const JSON_MOVE("move");
	std::string const JSON_DEPLOY("deploy");
	std::string const JSON_SHOOT("shoot");
	std::string const JSON_SPIT("ebola");

	std::string const JSON_KEY("key");

	ai::AiRanged::s_MOVE_ID =
		rangedEnemyParser.at(JSON_MOVE).at(JSON_KEY).get<std::string>();

	// Loading/Parsing Texture

	std::string const JSON_TEXTURE("texture");
	ai::AiBase::setup(
		sptrResources->m_textureMove,
		resourceHandler,
		rangedEnemyParser.at(JSON_MOVE).at(JSON_TEXTURE),
		ai::AiRanged::s_MOVE_ID);

	// Loading/Parsing Animations

	std::string const JSON_ANIMATION("animation");
	ai::AiBase::setup(
		sptrResources->m_animationMove,
		resourceHandler,
		rangedEnemyParser.at(JSON_MOVE).at(JSON_ANIMATION),
		ai::AiRanged::s_MOVE_ID);
}

/// <summary>
/// @brief initialize resources.
/// 
/// 
/// </summary>
/// <param name="sptrResources">shared pointer to loaded resources.</param>
void ai::AiRanged::init(std::shared_ptr<Resources> sptrResources)
{
	m_sptrResources = sptrResources;
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
	m_sptrState->update();
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
	m_sptrState->draw(window, deltaTime);
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
	m_heading = { 0.0f, 0.0f };
	m_angle = 0.0f;
	while (!m_stateStack.empty())
	{
		m_stateStack.pop();
	}
	std::shared_ptr<states::AiRangedState>(nullptr).swap(m_sptrState);
}

/// <summary>
/// @brief Determines whether a enemy is active.
/// 
/// A enemy that is not active doesn't update not is drawn.
/// (Considered in a dead state)
/// </summary>
/// <returns>true if enemy is active, else false.</returns>
bool const & ai::AiRanged::isActive() const
{
	return m_active;
}

/// <summary>
/// @brief Updates AiRanged::m_collisionShape and AiRanged::m_collisionRect.
/// 
/// 
/// </summary>
void ai::AiRanged::updateHitbox(sf::RectangleShape const & box)
{
	m_collisionShape.setPosition(box.getPosition());
	m_collisionShape.setScale(box.getScale());
	m_collisionShape.setOrigin(m_collisionShape.getSize() * 0.5f);

	auto const & boxBounds = m_collisionShape.getGlobalBounds();
	m_collisionRect.min = { boxBounds.left, boxBounds.top };
	m_collisionRect.max = { boxBounds.left + boxBounds.width, boxBounds.top + boxBounds.height };
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
		m_sptrState->enter();
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
	m_animator.addAnimation(
		m_sptrResources->m_animationMove.m_id,
		m_sptrResources->m_animationMove.m_frames,
		m_sptrResources->m_animationMove.m_duration);
}
