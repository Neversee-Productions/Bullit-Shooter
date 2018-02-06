#ifndef GameUI_H
#define GameUI_H

#include <memory>
#include <SFML\Graphics.hpp>
#include "Window.h"
#include "ResourceHandler.h"

///
/// @brief UI class.
/// @author Sebastian Kruzel
/// 
/// Defines the UI of the game.
/// 
class GameUI
{
public: //public member classes/structs.
	struct Resources
	{
		std::shared_ptr<sf::Texture> m_sptrHealthTemplateTexture = nullptr;
		std::shared_ptr<sf::Texture> m_sptrHealthTexture = nullptr;
	};
private: //private member classes/structs.
public: //public functions
	GameUI();
	void update();
	void draw(Window & window, const float & deltaTime);
	static void setup(std::shared_ptr<Resources> sptrResources, ResourceHandler & resourceHandler, json::json & UIParser);
	void init(std::shared_ptr<Resources> resources);
private: //private functions.
public: //public member variables.
private: //private member variables.

	/// <summary>
	/// @brief this is the template health sprite.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_healthTemplateSprite;

	/// <summary>
	/// @brief this is the health sprite.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_healthSprite;

	/// <summary>
	/// @brief position of the template health texture position.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_healthTemplatePosition;

	/// <summary>
	/// @brief position of the health bar sprite.
	/// 
	/// 
	/// </summary>
	//sf::Vector2f m_healthPosition;
};


#endif // !GameUI
