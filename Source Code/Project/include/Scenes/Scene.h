#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <assert.h>
#include <fstream>
#include "Thor\Graphics.hpp"
#include "json\json.hpp"
#include "system\ResourceHandler.h"
#include "system\Window.h"
#include "input\Controller.h"

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
	void setNextSceneName(const std::string & nextSceneName);
	virtual void preStart(const std::string & resourceFilePath);
	virtual void start(const std::string & resourceFilePath) abstract;
	virtual void stop() abstract;
	virtual void update() abstract;
	virtual void draw(Window & window, const float & deltaTime) abstract;

protected:
	virtual void goToNextScene() abstract;

	/// <summary>
	/// @brief Reference to update time step.
	/// 
	/// 
	/// </summary>
	const float m_UPDATE_DT;

private:
	/// <summary>
	/// @brief Represents the next scene that we want to move to.
	/// 
	/// Used as a way to identify the target scene by the SceneManager.
	/// </summary>
	std::string m_nextSceneName;

	/// <summary>
	/// @brief Represents the name of the scene.
	/// 
	/// Used as a way of identifying the scene by the SceneManager.
	/// </summary>
	std::string m_name;

};

#endif // !SCENE_H