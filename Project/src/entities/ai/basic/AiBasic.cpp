#include "entities\ai\basic\AiBasicState.h"

std::string ai::AiBasic::s_IDLE_ID = "";

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
void ai::AiBasic::setup(std::shared_ptr<Resources> sptrResources, ResourceHandler & resourceHandler, json::json & basicEnemyParser)
{
	std::string const JSON_IDLE("idle");
	std::string const JSON_KEY("key");

	std::string const BASIC_ENEMY_ID = basicEnemyParser.at(JSON_IDLE).at(JSON_KEY).get<std::string>();
	ai::AiBasic::s_IDLE_ID = BASIC_ENEMY_ID;
	// Loading/Parsing Texture
	{
		std::string const JSON_TEXTURE("texture");
		json::json & idleTextureParser = basicEnemyParser.at(JSON_IDLE).at(JSON_TEXTURE);

		std::string const JSON_TEXTURE_PATH("path");
		std::string const JSON_TEXTURE_ORIGIN("origin");
		std::string const JSON_TEXTURE_SCALE("scale");
		std::string const JSON_TEXTURE_FRAME("frame");

		sptrResources->m_texture.m_id = BASIC_ENEMY_ID;
		sptrResources->m_texture.m_origin.x = idleTextureParser.at(JSON_TEXTURE_ORIGIN).at("x").get<float>();
		sptrResources->m_texture.m_origin.y = idleTextureParser.at(JSON_TEXTURE_ORIGIN).at("y").get<float>();
		sptrResources->m_texture.m_scale.x = idleTextureParser.at(JSON_TEXTURE_SCALE).at("x").get<float>();
		sptrResources->m_texture.m_scale.y = idleTextureParser.at(JSON_TEXTURE_SCALE).at("y").get<float>();
		sptrResources->m_texture.m_textureRect.left = idleTextureParser.at(JSON_TEXTURE_FRAME).at("x").get<int>();
		sptrResources->m_texture.m_textureRect.top = idleTextureParser.at(JSON_TEXTURE_FRAME).at("y").get<int>();
		sptrResources->m_texture.m_textureRect.width = idleTextureParser.at(JSON_TEXTURE_FRAME).at("w").get<int>();
		sptrResources->m_texture.m_textureRect.height = idleTextureParser.at(JSON_TEXTURE_FRAME).at("h").get<int>();
		sptrResources->m_texture.m_sptrTexture =
			resourceHandler.loadUp<sf::Texture>(idleTextureParser.at(JSON_TEXTURE_PATH).get<std::string>(), sptrResources->m_texture.m_id);
		sptrResources->m_texture.m_sptrTexture->setSmooth(true);
	}
	// Loading/Parsing Animation
	{
		std::string const JSON_ANIMATION("animation");
		json::json & idleAnimationParser = basicEnemyParser.at(JSON_IDLE).at(JSON_ANIMATION);

		std::string const JSON_ANIMATION_DURATION("duration");
		std::string const JSON_ANIMATION_WIDTH("width");
		std::string const JSON_ANIMATION_HEIGHT("height");
		std::string const JSON_ANIMATION_ORIGIN("origin");
		std::string const JSON_ANIMATION_FRAMES("frames");

		sptrResources->m_animationLoop.m_id = BASIC_ENEMY_ID;
		sptrResources->m_animationLoop.m_duration = sf::seconds(idleAnimationParser.at(JSON_ANIMATION_DURATION).get<float>());
		sptrResources->m_animationLoop.m_origin.x = idleAnimationParser.at(JSON_ANIMATION_ORIGIN).at("x").get<float>();
		sptrResources->m_animationLoop.m_origin.y = idleAnimationParser.at(JSON_ANIMATION_ORIGIN).at("y").get<float>();
		sptrResources->m_animationLoop.m_sptrTexture = sptrResources->m_texture.m_sptrTexture; // Use texture already loaded.

		sptrResources->m_animationLoop.m_frames = thor::FrameAnimation();
		json::json & idleFramesParser = idleAnimationParser.at(JSON_ANIMATION_FRAMES);
		auto const FRAME_WIDTH = idleAnimationParser.at(JSON_ANIMATION_WIDTH).get<int>();
		auto const FRAME_HEIGHT = idleAnimationParser.at(JSON_ANIMATION_HEIGHT).get<int>();
		float i = 0.0f;
		for (
			json::json::iterator itt = idleFramesParser.begin(), end = idleFramesParser.end();
			itt != end;
			++itt, ++i
			)
		{
			auto & jsonNode = *itt;
			sf::IntRect rect;
			rect.left = jsonNode.at("x").get<int>();
			rect.top = jsonNode.at("y").get<int>();
			rect.width = FRAME_WIDTH;
			rect.height = FRAME_HEIGHT;

			sptrResources->m_animationLoop.m_frames.addFrame(i, rect);
		}
	}
}

/// <summary>
/// @brief Default constructor.
/// 
/// Construct our map of actions.
/// </summary>
ai::AiBasic::AiBasic(Player const & player)
	: AiBase()
	, m_position{ 0.0f, 0.0f }
	, m_speed(0.0f)
	, m_heading{ 0.0f, 1.0f }
	, m_angle(0.0f)
	, m_player(player)
	, m_renderQuad({80.0f , 80.0f}) // Implicitly call sf::Vector2f() constructor
	, m_stateStack()
	, m_sptrState(nullptr)
	, m_animator()
{
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
	m_renderQuad.setOrigin(sptrResources->m_texture.m_origin);
	m_renderQuad.setScale(sptrResources->m_texture.m_scale);
	m_renderQuad.setTexture(sptrResources->m_texture.m_sptrTexture.get(), true);
	m_renderQuad.setTextureRect(sptrResources->m_texture.m_textureRect);

	m_animator.addAnimation(sptrResources->m_animationLoop.m_id, sptrResources->m_animationLoop.m_frames, sptrResources->m_animationLoop.m_duration);

	this->initStates();
}

/// <summary>
/// @brief update current state.
/// 
/// 
/// </summary>
void ai::AiBasic::update()
{
	m_sptrState->update();
}

/// <summary>
/// @brief 
/// </summary>
/// <param name="window">reference to target window.</param>
/// <param name="deltaTime">read-only reference to delta time between last render calls.</param>
void ai::AiBasic::draw(Window & window, float const & deltaTime)
{
	m_sptrState->draw(window, deltaTime);
}

/// <summary>
/// @brief Constructs a base pointer and passes the call down.
/// 
/// 
/// </summary>
/// <param name="sptrState">shared pointer to our new state.</param>
void ai::AiBasic::setState(std::shared_ptr<ai::states::Search> sptrState)
{
	std::shared_ptr<ai::states::Basic> sptrBaseState = sptrState;
	this->setState(sptrBaseState);
}

/// <summary>
/// @brief Constructs a base pointer and passes the call down.
/// 
/// 
/// </summary>
/// <param name="sptrState">shared pointer to our new state.</param>
void ai::AiBasic::setState(std::shared_ptr<ai::states::Charge> sptrState)
{
	std::shared_ptr<ai::states::Basic> sptrBaseState = sptrState;
	this->setState(sptrBaseState);
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
void ai::AiBasic::setState(std::shared_ptr<ai::states::Basic> sptrState)
{
	if (nullptr != m_sptrState)
	{
		m_sptrState->exit();
	}
	if (nullptr != sptrState)
	{
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
	std::shared_ptr<ai::states::Search> firstState = std::make_shared<ai::states::Search>(ai::states::Search(*this));
	this->setState(firstState);
}

/// <summary>
/// @brief Initialize the rendering quad.
/// 
/// 
/// </summary>
void ai::AiBasic::initRenderingQuad()
{
	sf::Color const QUAD_FILL = sf::Color::Yellow;
	sf::FloatRect const QUAD_BOUND_BOX = m_renderQuad.getGlobalBounds();
	sf::Vector2f const QUAD_ORIGIN = { QUAD_BOUND_BOX.width * 0.5f, QUAD_BOUND_BOX.height *0.5f };

	m_renderQuad.setFillColor(QUAD_FILL);
	m_renderQuad.setOrigin(QUAD_ORIGIN);
}
