#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include <map>
#include <string>
#include "Scene.h"
#include "Scenes\GameScene.h"
#include "Scenes\MainMenuScene\MainMenuScene.h"

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
	SceneManager(Window & window, KeyHandler & keyHandler);
	void update();
	void draw(const float & deltaTime);

private:
	Scene & getScene(const std::string & name);
	Scene & getActive() const;
	void addScene(std::shared_ptr<Scene> scenePt);
	void loadScene(const std::string & name);
	void goToNextScene();

	/// <summary>
	/// @brief Reference to a created Window.
	/// 
	/// Required for all draw calls.
	/// </summary>
	Window & m_window;

	/// <summary>
	/// @brief Reference to a created KeyHandler.
	/// 
	/// Required for our scenes to handle input.
	/// </summary>
	KeyHandler & m_keyHandler;

	/// <summary>
	/// @brief Points to our current Scene.
	/// 
	/// This is contained within our list of scenes
	/// and is the target for our update/draw calls.
	/// </summary>
	std::shared_ptr<Scene> m_currentScene;
	
	/// <summary>
	/// @brief Alias for our map of Scene's.
	/// 
	/// 
	/// </summary>
	typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

	/// <summary>
	/// @brief Container of all scenes.
	/// 
	/// Scenes in this map may or may not be initialized handle with care.
	/// </summary>
	SceneMap m_sceneMap;

	/// <summary>
	/// 
	/// </summary>
	std::shared_ptr<Controller> m_controller;

};

#endif // !SCENEMANAGER_H