#include "Scene.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Initializes members to their default state.
/// </summary>
/// <param name="sceneName">Defines the scene's name.</param>
Scene::Scene(const std::string & sceneName)
	: m_name(sceneName)
	, m_nextSceneName("")
	, m_UPDATE_DT(App::getUpdateDeltaTime())
{
}

/// <summary>
/// @brief Retrieves Scene name.
/// 
/// 
/// </summary>
/// <returns>The name of the scene.</returns>
const std::string & Scene::getName() const
{
	return m_name;
}

/// <summary>
/// @brief Retrieves Scene::m_nextSceneName string.
/// 
/// Can be overriden to allow for changing of next scene
/// based on a custom condition.
/// </summary>
/// <returns>The name of the next scene.</returns>
const std::string & Scene::getNextSceneName()
{
	return m_nextSceneName;
}

/// <summary>
/// @brief Tells SceneManager to change current scene.
/// 
/// Note this will cause a instant scene change.
/// </summary>
/// <param name="nextSceneName">Defines the name of the next scene.</param>
void Scene::setNextSceneName(const std::string & nextSceneName)
{
	m_nextSceneName = std::move(nextSceneName);
}

/// <summary>
/// @brief Will pre load all resources.
/// 
/// 
/// </summary>
void Scene::preStart(const std::string & resourceFilePath)
{
}
