#include "Scenes\MainMenuScene\MainMenuScene.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Requires a std::shared_ptr<Controller> so as to process input.
/// </summary>
/// <param name="controller">defines the controller</param>
MainMenuScene::MainMenuScene(std::shared_ptr<KeyHandler> keyHandler, std::shared_ptr<Controller> controller)
	: Scene("MainMenu")
	, m_gui(nullptr)
	, m_keyHandler(keyHandler)
	, m_controller(controller)
	, m_resources(nullptr)
{
}

/// <summary>
/// @brief Configures our MainMenuScene.
/// 
/// Setups appropriate resources for gui
/// and defines a layout for the gui.
/// </summary>
void MainMenuScene::start()
{
	const std::string GUI_PATH("resources/gui/");
	const std::string BTN_FONT_PATH = GUI_PATH + "fonts/QuartzMS.ttf";
	const std::string BTN_TEXTURE_PATH = GUI_PATH + "textures/button.png";
	const sf::Vector2f & zero = sf::Vector2f(0.0f, 0.0f);

	m_resources = std::make_unique<Resources>();
	// store dereferenced pointer
	// used to avoid pointer syntax.
	auto & resources = *m_resources;

	m_gui = std::make_unique<gui::GUI>(m_keyHandler, m_controller);
	// store dereferenced pointer
	// used to avoid pointer syntax.
	auto & gui = *m_gui;

	auto sptrButtonFont = resources.m_sptrButtonFont;
	if (!sptrButtonFont->loadFromFile(BTN_FONT_PATH))
	{
		std::cout << "Failed to load:" << std::endl << " - " << BTN_FONT_PATH.c_str() << std::endl;
	}

	auto sptrButtonTexture = resources.m_sptrButtonTexture;
	if (!sptrButtonTexture->loadFromFile(BTN_TEXTURE_PATH))
	{
		std::cout << "Failed to load:" << std::endl << " - " << BTN_TEXTURE_PATH.c_str() << std::endl;
	}

	m_gui->addButton(
		std::bind(&MainMenuScene::btnExitGame, this),
		"Exit Game",
		zero,
		sptrButtonFont,
		24u,
		sptrButtonTexture,
		gui::Button::s_TEXT_RECT_LEFT,
		gui::Button::s_TEXT_RECT_MID,
		gui::Button::s_TEXT_RECT_RIGHT
	);

	m_gui->addButton(
		std::bind(&MainMenuScene::btnNewGame, this),
		"New Game",
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
void MainMenuScene::stop()
{
	m_gui.reset(nullptr);
	m_resources.reset(nullptr);
}

/// <summary>
/// @brief Update scene entities.
/// 
/// 
/// </summary>
void MainMenuScene::update()
{
	m_controller->update();
	m_gui->update(m_UPDATE_DT);
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
/// @brief New game Button's callback function.
/// 
/// The new game Button has a pointer to a function
/// that is called when the new game Button is pressed
/// this is the function that it calls
/// </summary>
void MainMenuScene::btnNewGame()
{
	m_nextSceneName = "Game";
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
	m_nextSceneName = "Exit";
}

