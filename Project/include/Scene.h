#ifndef SCENE_H
#define SCENE_H

#include <string>
#include "Window.h"

/// 
/// @brief Defines a interface for SceneManager to use.
/// @author Rafael Plugge
/// 
/// Represents what our SceneManager uses to interface between all derived scenes.
/// 
class Scene
{
public:
	Scene(const std::string & sceneName);
	const std::string & getName() const;
	virtual const std::string & getNextSceneName();
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void update() = 0;
	virtual void draw(Window & window, const float & deltaTime) = 0;

private:
	/// <summary>
	/// @brief Represents the name of the scene.
	/// 
	/// Used as a way of identifying the scene by the SceneManager.
	/// </summary>
	std::string m_name;

	/// <summary>
	/// @brief Represents the next scene that we want to move to.
	/// 
	/// Used as a way to identify the target scene by the SceneManager.
	/// </summary>
	std::string m_nextSceneName;
};

#endif // !SCENE_H