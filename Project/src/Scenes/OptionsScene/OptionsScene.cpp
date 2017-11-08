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
/// @brief Configures our OptionsScene.
/// 
/// Setups appropriate resources for gui
/// and defines a layout for the gui.
/// </summary>
void OptionsScene::start()
{
	const std::string GUI_PATH("resources/gui/");
	const std::string BTN_FONT_PATH = GUI_PATH + "fonts/QuartzMS.ttf";
	const std::string BTN_TEXTURE_PATH = GUI_PATH + "textures/button.png";
	const sf::Vector2f & zero = sf::Vector2f(0.0f, 0.0f);

	m_nextSceneName = "";

	m_resources = std::make_unique<Resources>();
	// store dereferenced pointer
	// used to avoid pointer syntax.
	auto & resources = *m_resources;

	m_gui = std::make_unique<gui::GUI>(m_keyHandler, m_controller, true);
	// store dereferenced pointer
	// used to avoid pointer syntax.
	auto & gui = *m_gui;

	auto sptrButtonFont = resources.m_sptrButtonFont;
	assert(sptrButtonFont->loadFromFile(BTN_FONT_PATH));

	auto sptrButtonTexture = resources.m_sptrButtonTexture;
	assert(sptrButtonTexture->loadFromFile(BTN_TEXTURE_PATH));

	gui.addButton(
		std::bind(&OptionsScene::btnBack, this),
		"Back",
		zero,
		sptrButtonFont,
		24u,
		sptrButtonTexture,
		gui::Button::s_TEXT_RECT_LEFT,
		gui::Button::s_TEXT_RECT_MID,
		gui::Button::s_TEXT_RECT_RIGHT
	);

	const auto& windowSize = App::getWindowSize();
	gui.configure(gui::GUI::Layouts::StackVertically, windowSize);
}

/// <summary>
/// @brief Used to unload external assets.
/// 
/// 
/// </summary>
void OptionsScene::stop()
{
	m_gui.reset(nullptr);
	m_resources.reset(nullptr);
	m_timer.reset(nullptr);
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
			m_nextSceneName = std::move(m_nextName);
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
