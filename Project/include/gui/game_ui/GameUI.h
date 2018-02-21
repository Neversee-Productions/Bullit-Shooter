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

		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrRechargeBarTexture = nullptr;

		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrRechargeBarFrameTexture = nullptr;

		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrBorderTexture = nullptr;

		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrOverchargeFrameTexture = nullptr;
	};
private: //private member classes/structs.
public: //public functions
	GameUI(std::shared_ptr<KeyHandler> keyHandler, std::shared_ptr<Controller> controller, std::function<void()> mainMenuFunction, std::function<void()> restartGameFunction
	);
	void update();
	void draw(Window & window, const float & deltaTime);
	static void setup(std::shared_ptr<Resources> sptrResources, ResourceHandler & resourceHandler, json::json & UIParser);
	void init(std::shared_ptr<Resources> resources);
	void decrementHealth(float health);
	const tinyh::c2AABB & getHealthCollisionBox();
	void setHealthTransparency(sf::Uint8 alphaVal);
	void btnResume();
	void setPaused(bool check);
	bool getPaused();
	void setShowEnd(bool check);
	bool getShowEnd();
	void setRecharge(float val);
	void reset();
	void setFireRate(float val);
	void setTimeSinceFire(float val);
	void updateOvercharge(float overchargeValue);
	void setOverheat(bool check);
	void setPauseFlashing(bool check);
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
	/// @brief define the function that will restart the game.
	/// 
	/// 
	/// </summary>
	std::function<void()> m_restartGameFunc;

	/// <summary>
	/// @brief Define if the pause menu is to be shown and updated.
	/// 
	/// 
	/// </summary>
	bool m_showPauseScreen;

	/// <summary>
	/// @brief unique ptr to the game end ui.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<gui::GUI> m_gameEndUI;

	/// <summary>
	/// @brief this defines if we show the game end screen.
	/// 
	/// 
	/// </summary>
	bool m_showGameEnd;

	/// <summary>
	/// @brief define the border sprite.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_borderSprite;

	/// <summary>
	/// @brief define right recharge bar.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_rechargeBarRight;

	/// <summary>
	/// @brief define left recharge bar.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_rechargeBarLeft;

	/// <summary>
	/// @brief define the right recharge frame.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_rechargeFrameRight;

	/// <summary>
	/// @brief define left recharge frame.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_rechargeFrameLeft;

	/// <summary>
	/// @brief define right overcharge frame.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_overchargeFrameRight;

	/// <summary>
	/// @brief define the right overcharge bar.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_overchargeBarRight;

	/// <summary>
	/// @brief define the overcharge left bar.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_overchargeBarLeft;

	/// <summary>
	/// @brief define left overcharge frame.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_overchargeFrameLeft;

	/// <summary>
	/// @brief define target scale for the recharge bar.
	/// 
	/// 
	/// </summary>
	float m_targetRecharge;

	/// <summary>
	/// @brief how long since last fire.
	/// 
	/// 
	/// </summary>
	float m_timeSinceFire;

	/// <summary>
	/// @brief define the current fireRate.
	/// 
	/// 
	/// </summary>
	float m_fireRateVal;

	/// <summary>
	/// @brief is the players weapon overheating.
	/// 
	/// 
	/// </summary>
	bool m_overheating;

	/// <summary>
	/// @brief a timer used in the change of the overcharge bar color
	/// 
	/// 
	/// </summary>
	float m_colorFlipTimer;

	/// <summary>
	/// @brief bool that will determine if the UI should be flashing
	/// used mainly for pausing and game over.
	/// 
	/// 
	/// </summary>
	bool m_pauseFlashing;
};


#endif // !GameUI
