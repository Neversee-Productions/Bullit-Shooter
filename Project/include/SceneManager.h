#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <thread>
#include <memory>
#include <map>
#include <list>
#include <string>
#include "Scene.h"
#include "Scenes\GameScene\GameScene.h"
#include "Scenes\MainMenuScene\MainMenuScene.h"
#include "Scenes\OptionsScene\OptionsScene.h"

/// 
/// @brief Manager of Scenes.
/// @author Rafael Plugge
/// 
/// Manages the changing of scenes and
/// is our main application controller.
/// 
class SceneManager
{
public:
	SceneManager(Window & window, std::shared_ptr<KeyHandler> keyHandler);
	void update();
	void draw(const float & deltaTime);

private:
	Scene & getScene(const std::string & name);
	Scene & getActive() const;
	void addScene(std::shared_ptr<Scene> scenePt);
	void preLoadScene(const std::string & name);
	void loadScene(const std::string & name);
	void goToNextScene();

	/// <summary>
	/// @brief Reference to a created Window.
	/// 
	/// Required for all draw calls.
	/// </summary>
	Window & m_window;

	/// <summary>
	/// @brief Shared pointer to a created KeyHandler.
	/// 
	/// Required for our scenes to handle input.
	/// </summary>
	std::shared_ptr<KeyHandler> m_keyHandler;

	/// <summary>
	/// @brief Points to our current Scene.
	/// 
	/// This is contained within our list of scenes
	/// and is the target for our update/draw calls.
	/// </summary>
	std::shared_ptr<Scene> m_currentScene;

	/// <summary>
	/// @brief Alias for the value type of our map.
	/// 
	/// The first element is a pointer to a scene
	/// while the second element is a ThreadList.
	/// </summary>
	typedef std::pair<std::shared_ptr<Scene>, std::unique_ptr<std::thread>> ScenePair;

	/// <summary>
	/// @brief Alias for our map of ScenePair's.
	/// 
	/// Our map will contain a value of type ScenePair.
	/// </summary>
	typedef std::map<std::string, ScenePair> SceneMap;

	/// <summary>
	/// @brief Container of all scenes.
	/// 
	/// Scenes in this map may or may not be initialized handle with care.
	/// </summary>
	SceneMap m_sceneMap;

	/// <summary>
	/// @brief Shared pointer to a pre-created controller.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<Controller> m_controller;

};

#endif // !SCENEMANAGER_H