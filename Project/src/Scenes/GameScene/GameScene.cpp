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
	json::json gameSceneJsonLoader;
	rawFile >> gameSceneJsonLoader;

	if (!m_resources)
	{
		std::ifstream playerRawFile(gameSceneJsonLoader.at("player").get<std::string>());
		json::json playerJson;
		playerRawFile >> playerJson;

		m_resources = std::make_unique<Resources>();
		auto sptrPlayer = m_resources->m_sptrPlayer;
		auto sptrShip = sptrPlayer->m_ship;
		sptrShip->m_sptrTexture = resourceHandler.loadUp<sf::Texture>(playerJson, "ship");
		assert(nullptr != sptrShip->m_sptrTexture);

		sptrShip->m_uptrFrames = std::make_unique<Ship::ShipFrames>();
		auto & frames = *sptrShip->m_uptrFrames;
		auto loadedFrames = resourceHandler.loadUp<Ship::ShipFrames>(playerJson, "ship");
		frames.insert(frames.begin(), loadedFrames->begin(), loadedFrames->end());
		assert(nullptr != sptrShip->m_uptrFrames);

	}

	m_player.init(m_resources->m_sptrPlayer);
}

