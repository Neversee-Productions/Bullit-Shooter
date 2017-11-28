#include "Scenes\SplashScreen\SplashScene.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Defines our splash scene for the game.
/// </summary>
SplashScene::SplashScene()
	: Scene("Splash")
	, m_resources(nullptr)
	, m_backgroundSprite(nullptr)
	, m_backgroundColor(nullptr)
	, m_incrementColor(1u)
	, m_fadeState(FadeState::FadeIn)
{
}

/// <summary>
/// @brief Pre loads the resources on another thread.
/// 
/// 
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void SplashScene::preStart(const std::string & resourceFilePath)
{
	setup(resourceFilePath);
}

/// <summary>
/// @brief Loads the assets for the scene.
/// 
/// 
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void SplashScene::start(const std::string & resourceFilePath)
{
	setup(resourceFilePath);
}

/// <summary>
/// @brief Used to unload external assets.
/// 
/// 
/// </summary>
void SplashScene::stop()
{
	std::unique_ptr<Resources>().swap(m_resources);
	std::unique_ptr<thor::BigSprite>().swap(m_backgroundSprite);
	std::unique_ptr<sf::Color>().swap(m_backgroundColor);
}

/// <summary>
/// @brief Update scene entities.
/// 
/// 
/// </summary>
void SplashScene::update()
{
	if (255u == m_backgroundColor->a)
	{
		m_backgroundColor->a -= m_incrementColor;
		m_fadeState = FadeState::FadeOut;
	}
	else if (0u == m_backgroundColor->a)
	{
		goToNextScene();
	}
	else
	{
		switch (m_fadeState)
		{
		case SplashScene::FadeState::FadeIn:
			m_backgroundColor->a += m_incrementColor;
			break;
		case SplashScene::FadeState::FadeOut:
			m_backgroundColor->a -= m_incrementColor;
			break;
		default:
			break;
		}
	}

	m_backgroundSprite->setColor(*m_backgroundColor);
}

/// <summary>
/// @brief Render scene entities.
/// 
/// 
/// </summary>
/// <param name="window">reference to window</param>
/// <param name="deltaTime">reference to draw time step</param>
void SplashScene::draw(Window & window, const float & deltaTime)
{
	window.draw(*m_backgroundSprite);
}

/// <summary>
/// @brief Tells the SceneManager to change to another Scene.
/// 
/// 
/// </summary>
void SplashScene::goToNextScene()
{
	Scene::setNextSceneName("Title");
}

/// <summary>
/// @brief Loads external assets.
/// 
/// 
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene.</param>
void SplashScene::setup(const std::string & filePath)
{
	auto & resourceHandler = ResourceHandler::get();
	Scene::setNextSceneName("");

	if (!m_resources)
	{
		std::ifstream rawFile(filePath);
		json::json jsonLoader;
		rawFile >> jsonLoader;

		// instatiate our resource pointers that will "own"
		// the asset on the heap.
		m_resources = std::make_unique<Resources>();

		m_resources->m_backgroundTexture = resourceHandler.loadUp<thor::BigTexture>(jsonLoader, "splash_background");
		assert(nullptr != m_resources->m_backgroundTexture);

		const auto & windowSize = static_cast<sf::Vector2f>(App::getViewSize());

		// Setup Background Color
		m_backgroundColor = std::make_unique<sf::Color>();
		auto & backgroundColor = *m_backgroundColor;
		backgroundColor.a = 1u;
		backgroundColor.b = 255u;
		backgroundColor.g = 255u;
		backgroundColor.r = 255u;

		// Setup Background Sprite
		m_backgroundSprite = std::make_unique<thor::BigSprite>();
		auto & backgroundSprite = *m_backgroundSprite;
		backgroundSprite.setTexture(*m_resources->m_backgroundTexture);
		const auto & backgroundBox = backgroundSprite.getLocalBounds();
		backgroundSprite.setOrigin(backgroundBox.width * 0.5f, backgroundBox.height * 0.5f);
		backgroundSprite.setPosition(windowSize.x * 0.5f, windowSize.y * 0.5f);
		backgroundSprite.setScale(0.5f, 0.5f);
		backgroundSprite.setColor(backgroundColor);
	}
}
