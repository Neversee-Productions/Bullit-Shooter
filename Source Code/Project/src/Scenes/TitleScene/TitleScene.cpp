#include "Scenes\TitleScene\TitleScene.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
/// <param name="keyhandler">defines shared pointer to a KeyHandler.</param>
/// <param name="controller">defines shared pointer to a Controller.</param>
TitleScene::TitleScene(
	std::shared_ptr<KeyHandler> keyhandler
	, std::shared_ptr<Controller> controller
)
	: Scene("Title")
	, m_keyHandler(keyhandler)
	, m_controller(controller)
	, m_resources(nullptr)
	, m_titleSprite(nullptr)
	, m_continueText(nullptr)
	, m_background()
{
}

/// <summary>
/// @brief Used to pre-load assets on another thread.
/// 
/// 
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void TitleScene::preStart(const std::string & resourceFilePath)
{
	if (!m_resources)
	{
		setup(resourceFilePath);
	}
}

/// <summary>
/// @brief Loads assets and prepare to launch.
/// 
/// 
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void TitleScene::start(const std::string & resourceFilePath)
{
	if (!m_resources)
	{
		setup(resourceFilePath);
	}
	m_background.setTargetColor(sf::Color::White);
}

/// <summary>
/// @brief Used to unload external assets.
/// 
/// 
/// </summary>
void TitleScene::stop()
{
	std::unique_ptr<Resources>().swap(m_resources);
	std::unique_ptr<thor::BigSprite>().swap(m_titleSprite);
	std::unique_ptr<sf::Text>().swap(m_continueText);
}

/// <summary>
/// @brief Update scene entities.
/// 
/// 
/// </summary>
void TitleScene::update()
{
	m_background.update();
	if (
		m_keyHandler->isAnyPressed()
		|| 
		(m_controller->isConnected() && m_controller->isAnyButtonPressed())
		)
	{
		goToNextScene();
	}
}

/// <summary>
/// @brief Render scene entities.
/// 
/// 
/// </summary>
/// <param name="window">reference to window</param>
/// <param name="deltaTime">reference to draw time step</param>
void TitleScene::draw(Window & window, const float & deltaTime)
{
	m_background.draw(window, deltaTime);
	window.draw(*m_titleSprite);
	window.draw(*m_continueText);
}

/// <summary>
/// @brief Tells the SceneManager to change to another Scene.
/// 
/// 
/// </summary>
void TitleScene::goToNextScene()
{
	Scene::setNextSceneName("MainMenu");
}

/// <summary>
/// @brief Load external assets and setups scene.
/// 
/// 
/// </summary>
/// <param name="filePath">defines the path to the json file for this scene</param>
void TitleScene::setup(const std::string & filePath)
{
	auto & resourceHandler = ResourceHandler::get();

	Scene::setNextSceneName("");

	js::json jsonLoader = util::loadJsonFromFile(filePath);

	// instatiate our resource pointers that will "own"
	// the asset on the heap.
	m_resources = std::make_unique<Resources>();

	m_resources->m_sptrBackground->m_sptrBgShader = resourceHandler.loadUp<sf::Shader>(jsonLoader, "background");
	assert(nullptr != m_resources->m_sptrBackground->m_sptrBgShader);
	m_resources->m_sptrTitleTexture = resourceHandler.loadUp<thor::BigTexture>(jsonLoader, "title");
	assert(nullptr != m_resources->m_sptrTitleTexture);
	m_resources->m_sptrTextFont = resourceHandler.loadUp<sf::Font>(jsonLoader, "text");
	assert(nullptr != m_resources->m_sptrTextFont);

	// Storing a constant reference to the windows dimensions as floats
	const auto & windowSize = static_cast<sf::Vector2f>(App::getViewSize());
	
	// storing a constant of the center position of the window
	const auto windowCenter = windowSize * 0.5f;

	// Setup Background
	m_background.init(m_resources->m_sptrBackground);

	// Setup Title Sprite
	m_titleSprite = std::make_unique<thor::BigSprite>();
	auto & titleSprite = *m_titleSprite;
	titleSprite.setTexture(*(m_resources->m_sptrTitleTexture));
	const auto & boxTitle = titleSprite.getLocalBounds();
	titleSprite.setOrigin(boxTitle.width * 0.5f, boxTitle.height);
	titleSprite.setPosition(windowCenter);

	// Setup continue Text
	m_continueText = std::make_unique<sf::Text>();
	auto & continueText = *m_continueText;
	continueText.setFont(*(m_resources->m_sptrTextFont));
	continueText.setCharacterSize(jsonLoader.at("fontsize").get<unsigned int>());
	continueText.setString("Press any key to continue");
	const auto & boxText = continueText.getLocalBounds();
	continueText.setOrigin(boxText.width * 0.5f, boxText.height * 0.5f);
	continueText.setPosition(windowCenter);
	continueText.setOutlineThickness(1.0f);
	continueText.setOutlineColor(sf::Color::Black);
	continueText.setFillColor(sf::Color::White);
}
