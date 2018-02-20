#ifndef GameUI_H
#define GameUI_H

#include <memory>
#include <SFML\Graphics.hpp>
#include "system\Window.h"
#include "system\ResourceHandler.h"
#include "tinyheaders\tinyc2.h"
#include "gui\GUI.h"
#include "Scenes\Scene.h"


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

		/// <summary>
		/// @brief shared pointer to font.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Font> m_sptrButtonFont = nullptr;

		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrButtonTexture = nullptr;
	};
private: //private member classes/structs.
public: //public functions
	GameUI(std::shared_ptr<KeyHandler> keyHandler, std::shared_ptr<Controller> controller, std::function<void()> mainMenuFunction);
	void update();
	void draw(Window & window, const float & deltaTime);
	static void setup(std::shared_ptr<Resources> sptrResources, ResourceHandler & resourceHandler, js::json & UIParser);
	void init(std::shared_ptr<Resources> resources);
	void decrementHealth(float health);
	const tinyh::c2AABB & getHealthCollisionBox();
	void setHealthTransparency(sf::Uint8 alphaVal);
	void btnResume();
	void setPaused(bool check);
	bool getPaused();
	void reset();
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
	/// @brief this represents the amount of health that player has lost.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_healthLostSprite;

	/// <summary>
	/// @brief position of the template health texture position.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_healthTemplatePosition;


	/// <summary>
	/// @brief this is the variable that will specify
	/// how low the health bar is to go.
	/// 
	/// 
	/// </summary>
	float m_targetHealth;

	/// <summary>
	/// @brief this is a tiny headers rectangle object to deal with collisions.
	/// 
	/// 
	/// </summary>
	tinyh::c2AABB m_healthCollisionRect;

	/// <summary>
	/// @brief Unique pointer to our GUI (pause screen).
	/// 
	/// 
	/// </summary>
	std::unique_ptr<gui::GUI> m_gui;

	/// <summary>
	/// @brief define the function that is executed when the main menu button is pressed.
	/// 
	/// 
	/// </summary>
	std::function<void()> m_mainMenuFunc;

	/// <summary>
	/// @brief Define if the pause menu is to be shown and updated.
	/// 
	/// 
	/// </summary>
	bool m_showPauseScreen;

};


#endif // !GameUI
