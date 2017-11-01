#include "Scenes\MainMenuScene\MainMenuScene.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Requires a std::shared_ptr<Controller> so as to process input.
/// </summary>
/// <param name="controller">defines the controller</param>
MainMenuScene::MainMenuScene(std::shared_ptr<Controller> controller)
	: Scene("MainMenu")
	, m_gui(nullptr)
	, m_controller(controller)
{
}

/// <summary>
/// @brief Configures our gui.
/// 
/// 
/// </summary>
void MainMenuScene::start()
{
	m_gui = std::make_unique<GUI>(m_controller);
	auto & gui = *m_gui;

	const auto& windowSize = App::getWindowSize();
	gui.configure(GUI::Layouts::Custom, windowSize);

}

/// <summary>
/// @brief Used to unload external assets.
/// 
/// 
/// </summary>
void MainMenuScene::stop()
{
}

/// <summary>
/// @brief Update scene entities.
/// 
/// 
/// </summary>
void MainMenuScene::update()
{
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
}

