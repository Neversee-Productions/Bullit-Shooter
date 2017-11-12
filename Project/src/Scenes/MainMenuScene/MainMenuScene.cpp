#include "Scenes\MainMenuScene\MainMenuScene.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Defines our main menu for the game.
/// </summary>
/// <param name="keyHandler">defines a pre-created key handler</param>
/// <param name="controller">defines a pre-created controller</param>
MainMenuScene::MainMenuScene(
	std::shared_ptr<KeyHandler> keyHandler
	, std::shared_ptr<Controller> controller
)
	: Scene("MainMenu")
	, m_gui(nullptr)
	, m_keyHandler(keyHandler)
	, m_controller(controller)
	, m_resources(nullptr)
	, m_timer(nullptr)
	, m_DELAY_TIME(0.5f)
	, m_nextName()
{
}

/// <summary>
/// @brief Preloads resources on different thread.
/// 
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void MainMenuScene::preStart(const std::string & resourceFilePath)
{
	this->setup(resourceFilePath);
}

/// <summary>
/// @brief Configures our MainMenuScene.
/// 
/// Setups appropriate resources for gui
/// and defines a layout for the gui.
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void MainMenuScene::start(const std::string & resourceFilePath)
{
	Scene::setNextSceneName("");
	this->setup(resourceFilePath);
}

/// <summary>
/// @brief Used to unload external assets.
/// 
/// 
/// </summary>
void MainMenuScene::stop()
{
	std::unique_ptr<gui::GUI>(nullptr).swap(m_gui);
	std::unique_ptr<sf::Clock>(nullptr).swap(m_timer);
	std::unique_ptr<Resources>(nullptr).swap(m_resources);
}

/// <summary>
/// @brief Update scene entities.
/// 
/// 
/// </summary>
void MainMenuScene::update()
{
	if (m_timer)
	{
		const auto & timeInSeconds = m_timer->getElapsedTime().asSeconds();
		if (timeInSeconds >= m_DELAY_TIME)
		{
			this->goToNextScene();
		}
	}
	else
	{
		m_controller->update();
		m_gui->update(m_UPDATE_DT);
	}
}

/// <summary>
/// @brief Render scene entities.
/// 
/// 
/// </summary>
/// <param name="window">reference to window</param>
/// <param name="deltaTime">reference to draw time step</param>
void MainMenuScene::draw(Window & window, const float & deltaTime)
{
	m_gui->draw(window);
}

/// <summary>
/// @brief Tells the SceneManager to change to another Scene.
/// 
/// 
/// </summary>
void MainMenuScene::goToNextScene()
{
	Scene::setNextSceneName(m_nextName);
}

/// <summary>
/// @brief Load up what MainMenuScene needs to run.
/// 
/// 
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void MainMenuScene::setup(const std::string & resourceFilePath)
{
	auto & resourceHandler = ResourceHandler::get();

	std::ifstream rawFile(resourceFilePath);
	json::json jsonLoader;
	rawFile >> jsonLoader;

	if (!m_resources)
	{
		// instatiate our resource pointers that will "own"
		// the asset on the heap.
		m_resources = std::make_unique<Resources>();

		m_resources->m_sptrButtonTexture = resourceHandler.loadUp<sf::Texture>(jsonLoader, "button");
		assert(nullptr != m_resources->m_sptrButtonTexture);

		m_resources->m_sptrButtonFont = resourceHandler.loadUp<sf::Font>(jsonLoader, "button");
		assert(nullptr != m_resources->m_sptrButtonFont);
	}
	if (!m_gui)
	{
		loadGui(*m_resources, jsonLoader.at("fontsize").get<unsigned int>());
	}
}

/// <summary>
/// @brief Loadups GUI.
/// 
/// @warning Assumes external assets are already loaded.
/// </summary>
/// <param name="resources">defines reference to our external assets.</param>
/// <param name="fontSize">defines the size of our gui::GUI's font</param>
void MainMenuScene::loadGui(Resources & resources, const sf::Uint32 & fontSize)
{
	const sf::Vector2f & zero = sf::Vector2f(0.0f, 0.0f);
	auto sptrButtonFont = resources.m_sptrButtonFont;
	auto sptrButtonTexture = resources.m_sptrButtonTexture;

	// instantiate our gui object and assign ownership.
	m_gui = std::make_unique<gui::GUI>(m_keyHandler, m_controller, true);
	// store dereferenced pointer
	// used to avoid pointer syntax.
	auto & gui = *m_gui;

	m_gui->addButton(
		std::bind(&MainMenuScene::btnNewGame, this),
		"New Game",
		zero,
		sptrButtonFont,
		fontSize,
		sptrButtonTexture,
		gui::Button::s_TEXT_RECT_LEFT,
		gui::Button::s_TEXT_RECT_MID,
		gui::Button::s_TEXT_RECT_RIGHT
	);

	m_gui->addButton(
		std::bind(&MainMenuScene::btnOptions, this),
		"Options",
		zero,
		sptrButtonFont,
		fontSize,
		sptrButtonTexture,
		gui::Button::s_TEXT_RECT_LEFT,
		gui::Button::s_TEXT_RECT_MID,
		gui::Button::s_TEXT_RECT_RIGHT
	);

	m_gui->addButton(
		std::bind(&MainMenuScene::btnExitGame, this),
		"Exit Game",
		zero,
		sptrButtonFont,
		fontSize,
		sptrButtonTexture,
		gui::Button::s_TEXT_RECT_LEFT,
		gui::Button::s_TEXT_RECT_MID,
		gui::Button::s_TEXT_RECT_RIGHT
	);

	const auto& windowSize = App::getWindowSize();
	gui.configure(gui::GUI::Layouts::StripDiagonal, windowSize);
}

/// <summary>
/// @brief New game Button's callback function.
/// 
/// The new game Button has a pointer to a function
/// that is called when the new game Button is pressed
/// this is the function that it calls
/// </summary>
void MainMenuScene::btnNewGame()
{
	m_nextName = "Game";
	m_timer = std::make_unique<sf::Clock>();
}

/// <summary>
/// @brief Exit Button's callback function.
/// 
/// The exit Button has a pointer to a function
/// that is called when the exit Button is pressed
/// this is the function that it calls
/// </summary>
void MainMenuScene::btnExitGame()
{
	m_nextName = "Exit";
	m_timer = std::make_unique<sf::Clock>();
}

/// <summary>
/// @brief Options Button's callback function.
/// 
/// The options Button has a pointer to a function
/// that is called when the options Button is pressed
/// this is the function that it calls
/// </summary>
void MainMenuScene::btnOptions()
{
	m_nextName = "Options";
	m_timer = std::make_unique<sf::Clock>();
}

