#include "Scenes\OptionsScene\OptionsScene.h"

/// <summary>
/// @brief default constructor.
/// 
/// Defines our options screen that is used to alter video and audio settings.
/// 
/// </summary>
/// <param name="keyHandler">defines a pre-created key handler</param>
/// <param name="controller">defines a pre-created controller</param>
OptionsScene::OptionsScene(
	std::shared_ptr<KeyHandler> keyHandler
	, std::shared_ptr<Controller> controller
)
	: Scene("Options")
	, m_gui(nullptr)
	, m_keyHandler(keyHandler)
	, m_controller(controller)
	, m_resources(nullptr)
	, m_timer(nullptr)
	, m_DELAY_TIME(0.4f)
	, m_nextName()
{
}

/// <summary>
/// @brief Preloads resources on different thread.
/// 
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void OptionsScene::preStart(const std::string & resourceFilePath)
{
	if (!m_resources)
	{
		this->setup(resourceFilePath);
	}
}

/// <summary>
/// @brief Configures our OptionsScene.
/// 
/// Setups appropriate resources for gui
/// and defines a layout for the gui.
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void OptionsScene::start(const std::string & resourceFilePath)
{
	if (!m_resources)
	{
		this->setup(resourceFilePath);
	}
}

/// <summary>
/// @brief Used to unload external assets.
/// 
/// 
/// </summary>
void OptionsScene::stop()
{
	std::unique_ptr<gui::GUI>().swap(m_gui);
	std::unique_ptr<Resources>().swap(m_resources);
	std::unique_ptr<sf::Clock>().swap(m_timer);
}

/// <summary>
/// @brief Update scene entities.
/// 
/// 
/// </summary>
void OptionsScene::update()
{
	if (m_timer)
	{
		const auto & timeInSeconds = m_timer->getElapsedTime().asSeconds();
		if (timeInSeconds >= m_DELAY_TIME)
		{
			this->goToNextScene();
			m_timer.reset(nullptr);
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
void OptionsScene::draw(Window & window, const float & deltaTime)
{
	m_gui->draw(window);
}

/// <summary>
/// @brief Tells the SceneManager to change to another Scene.
/// 
/// 
/// </summary>
void OptionsScene::goToNextScene()
{
	Scene::setNextSceneName(m_nextName);
}

/// <summary>
/// @brief Loads up all assets necessary for OptionsScene.
/// 
/// 
/// </summary>
/// <param name="filePath">defines the path to the json file for this scene</param>
void OptionsScene::setup(const std::string & filePath)
{
	auto & resourceHandler = ResourceHandler::get();
	Scene::setNextSceneName("");

	std::ifstream fileRaw(filePath);
	json::json jsonLoader;
	fileRaw >> jsonLoader;

	m_resources = std::make_unique<Resources>();

	m_resources->m_sptrButtonFont = resourceHandler.loadUp<sf::Font>(jsonLoader, "button");
	assert(nullptr != m_resources->m_sptrButtonFont);

	m_resources->m_sptrButtonTexture = resourceHandler.loadUp<sf::Texture>(jsonLoader, "button");
	assert(nullptr != m_resources->m_sptrButtonTexture);

	loadGui(*m_resources, jsonLoader.at("fontsize").get<unsigned int>());
}

void OptionsScene::loadGui(Resources & resources, const sf::Uint32 & fontSize)
{
	const sf::Vector2f & zero = sf::Vector2f(0.0f, 0.0f);
	auto sptrButtonFont = resources.m_sptrButtonFont;
	auto sptrButtonTexture = resources.m_sptrButtonTexture;

	// instantiate our gui object and assign ownership.
	m_gui = std::make_unique<gui::GUI>(m_keyHandler, m_controller, true);
	// store dereferenced pointer
	// used to avoid pointer syntax.
	auto & gui = *m_gui;

	gui.addButton(
		std::bind(&OptionsScene::btnBack, this),
		"Back",
		zero,
		sptrButtonFont,
		fontSize,
		sptrButtonTexture,
		gui::Button::s_TEXT_RECT_LEFT,
		gui::Button::s_TEXT_RECT_MID,
		gui::Button::s_TEXT_RECT_RIGHT
	);

	const auto& windowSize = App::getViewSize();
	gui.configure(gui::GUI::Layouts::StackVertically, windowSize);

}

/// <summary>
/// @brief Back Button's callback function.
/// 
/// The back Button has a pointer to a function
/// that is called when the back Button is pressed
/// this is the function that it calls
/// </summary>
void OptionsScene::btnBack()
{
	m_nextName = "MainMenu";
	m_timer = std::make_unique<sf::Clock>();
}
