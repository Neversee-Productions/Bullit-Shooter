#include "Scenes\GameScene\GameScene.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Constructs a base Scene using the name of "Game".
/// </summary>
GameScene::GameScene(KeyHandler& keyHandler)
	: Scene("Game")
	, m_player(keyHandler)
	, m_keyHandler(keyHandler)
	, m_resources(nullptr)
{
}

/// <summary>
/// @brief Preloads resources on different thread.
/// 
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void GameScene::preStart(const std::string & resourceFilePath)
{
	if (!m_resources)
	{
		this->setup(resourceFilePath);
	}
}

/// <summary>
/// @brief Empty for now.
/// 
/// Will contain the loading of external content.
/// </summary>
void GameScene::start(const std::string & resourceFilePath)
{
	Scene::setNextSceneName("");
	if (!m_resources)
	{
		this->setup(resourceFilePath);
	}
}

/// <summary>
/// @brief Empty for now.
/// 
/// Will contain the unloading of external content.
/// </summary>
void GameScene::stop()
{
}

/// <summary>
/// @brief Update game scene entities.
/// 
/// 
/// </summary>
void GameScene::update()
{
	m_player.update();
}

/// <summary>
/// @brief Render game scene entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void GameScene::draw(Window & window, const float & deltaTime)
{
	m_player.draw(window, deltaTime);
}

/// <summary>
/// @brief Tells the SceneManager to change to another Scene.
/// 
/// 
/// </summary>
void GameScene::goToNextScene()
{
	Scene::setNextSceneName("");
}

/// <summary>
/// @brief Loads all external assets.
/// 
/// 
/// </summary>
/// <param name="filePath">defines the path to the json file for this scene</param>
void GameScene::setup(const std::string & filePath)
{
	auto & resourceHandler = ResourceHandler::get();

	std::ifstream rawFile(filePath);
	json::json jsonLoader;
	rawFile >> jsonLoader;

	if (!m_resources)
	{
		m_resources = std::make_unique<Resources>();
		std::unique_ptr<Resources::Ship> uptrShip = std::move(m_resources->m_uptrShip);
		uptrShip->m_sptrShipTexture = resourceHandler.loadUp<sf::Texture>(jsonLoader, "ship");
		assert(nullptr != uptrShip->m_sptrShipTexture);

		uptrShip->m_sptrShipAnimator = std::make_shared<SpriteAnimator>();
		const auto & duration = jsonLoader.at("animation").at("ship").at("duration").get<float>();
		uptrShip->m_sptrShipAnimator->addAnimation("ship", *resourceHandler.loadUp<thor::FrameAnimation>(jsonLoader, "ship"), sf::seconds(duration));
		assert(nullptr != uptrShip->m_sptrShipAnimator);

		m_resources->m_uptrShip = std::move(uptrShip);
	}
}

