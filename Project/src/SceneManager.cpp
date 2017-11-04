#include "SceneManager.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Construct our scene manager and
/// initializes its members.
/// </summary>
/// <param name="window">to be stored as a reference to a created Window.</param>
/// <param name="keyHandler">to be stored as a shared pointer to a created KeyHandler.</param>
SceneManager::SceneManager(
	Window & window,
	std::shared_ptr<KeyHandler> keyHandler
)
	: m_window(window)
	, m_keyHandler(keyHandler)
	, m_currentScene(nullptr)
	, m_sceneMap()
	, m_controller(nullptr)
{
	m_controller = std::make_shared<Controller>();

	std::shared_ptr<Scene> scenePt = std::make_shared<GameScene>(*m_keyHandler);
	addScene(scenePt);

	scenePt = std::make_shared<MainMenuScene>(m_keyHandler, m_controller);
	addScene(scenePt);
	loadScene(scenePt->getName());
}

/// <summary>
/// @brief Acquires the current scene.
/// 
/// Iterates over our list of scenes and
/// returns the Scene whose Scene::m_name is equal to name.
/// @warning if no Scene is found than a std::exception is thrown.
/// </summary>
/// <param name="name">Name of the scene we are looking for.</param>
/// <returns>Reference to the Scene found.</returns>
Scene & SceneManager::getScene(const std::string & name)
{
	auto itt = m_sceneMap.find(name);
	if (itt != m_sceneMap.end())
	{
		return *(itt->second);
	}
	else
	{
		std::string errorMsg("");
		errorMsg.append("Scene: " + name + " not found!\n");
		throw std::exception(errorMsg.c_str());
	}
}

/// <summary>
/// @brief Gets currently active Scene.
/// 
/// 
/// </summary>
/// <returns>Reference to currently active Scene.</returns>
Scene & SceneManager::getActive() const
{
	return *(m_currentScene);
}

/// <summary>
/// @brief Appends to our list of scenes.
/// 
/// The scene is added to our list, however this scene is not activated.
/// Note: if a scene with the same name exists it is overwritten.
/// </summary>
/// <param name="scenePt">Defines our new scene to be added.</param>
void SceneManager::addScene(std::shared_ptr<Scene> scenePt)
{
	m_sceneMap[scenePt->getName()] = scenePt;
}

/// <summary>
/// @brief Loads and activates named Scene.
/// 
/// Finds the Scene whoose Scene::m_name is the same as name,
/// deactivates the current Scene and activates the new Scene.
/// If no Scene is found than nothing happens.
/// </summary>
/// <param name="name">defines the Scene to be loaded</param>
void SceneManager::loadScene(const std::string & name)
{
	auto itt = m_sceneMap.find(name);
	if (itt != m_sceneMap.end())
	{
		if (m_currentScene != nullptr)
		{
			m_currentScene->stop();
		}
		m_currentScene = (itt->second);
		m_currentScene->start();
	}
	else if (name == "Exit")
	{
		m_window.close();
	}
}

/// <summary>
/// @brief Stops current Scene and progresses to the next one.
/// 
/// The next scene is defined as Scene::m_nextSceneName.
/// </summary>
void SceneManager::goToNextScene()
{
	loadScene(m_currentScene->getNextSceneName());
}

/// <summary>
/// @brief Updates current Scene.
/// 
/// Runs one update tick on the currently active Scene
/// </summary>
void SceneManager::update()
{
	if (m_currentScene->getNextSceneName() == "")
	{
		m_currentScene->update();
	}
	else
	{
		loadScene(m_currentScene->getNextSceneName());
	}
	m_keyHandler->update();
}

/// <summary>
/// @brief Renders one frame from current Scene.
/// 
/// Produces one frame from the current Scene.
/// </summary>
/// <param name="deltaTime">time step since last draw call</param>
void SceneManager::draw(const float & deltaTime)
{
	m_window.clear();
	m_currentScene->draw(m_window, deltaTime);
	m_window.display();
}
