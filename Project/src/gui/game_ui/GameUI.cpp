#include "gui/game_ui/GameUI.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
GameUI::GameUI(
	std::shared_ptr<KeyHandler> keyHandler
	, std::shared_ptr<Controller> controller
	, std::function<void()> mainMenuFunction
	, std::function<void()> restartGameFunction
)
	: m_healthTemplatePosition(sf::Vector2f(static_cast<sf::Vector2f>(App::getViewSize())))
	, m_targetHealth(1.0f)
	, m_gui(std::make_unique<gui::GUI>(keyHandler, controller, true))
	, m_mainMenuFunc(mainMenuFunction)
	, m_restartGameFunc(restartGameFunction)
	, m_showPauseScreen(false)
	, m_gameEndUI(std::make_unique<gui::GUI>(keyHandler, controller, true))
	, m_showGameEnd(false)
	, m_targetRecharge(0.0f)
	, m_fireRateVal(0.0f)
	, m_timeSinceFire(0.0f)
	, m_overheating(false)
	, m_colorFlipTimer(0.0f)
	, m_soundManager(SoundManager::instance())
	, m_rechargeHealth(false)
	, m_timeUntilOverheatingVoice(2.0f)
	, m_overheatingVoiceTimer(0.0f)
{
}

/// <summary>
/// @brief this is the update function it will update the ui accordingly.
/// 
/// 
/// </summary>
void GameUI::update()
{
	m_overheatingVoiceTimer += App::getUpdateDeltaTime();
	if (m_rechargeHealth)
	{
		if (m_healthSprite.getScale().x < m_targetHealth)
		{
			m_healthSprite.setScale(m_healthSprite.getScale().x + 0.5f * App::getUpdateDeltaTime(), 1.0f);
		}
		else
		{
			m_healthSprite.setScale(m_targetHealth, 1.0f);
			m_rechargeHealth = false;
		}
	}
	else
	{
		if (m_healthLostSprite.getScale().x > 0)
		{
			if (m_healthLostSprite.getScale().x > m_targetHealth)
			{
				m_healthLostSprite.setScale(sf::Vector2f(m_healthLostSprite.getScale().x - 0.25f * App::getUpdateDeltaTime(), 1.0f));
			}
		}
		else
		{
			m_healthLostSprite.setScale(sf::Vector2f(0.0f, 1.0f));
			m_healthSprite.setScale(0.0f, 1.0f);
		}
	}
	if (m_showPauseScreen)
	{
		m_gui->update(App::getUpdateDeltaTime());
	}
	if (m_showGameEnd)
	{
		m_gameEndUI->update(App::getUpdateDeltaTime());
	}
	m_rechargeBarRight.setScale(1.0f, 1 - (m_timeSinceFire / m_fireRateVal));
	m_rechargeBarLeft.setScale(1.0f, 1 - (m_timeSinceFire / m_fireRateVal));
	if (m_rechargeBarRight.getScale().y < 0)
	{
		m_rechargeBarRight.setScale(m_rechargeBarRight.getScale().x, 0.0f);
		m_rechargeBarLeft.setScale(m_rechargeBarLeft.getScale().x, 0.0f);
	}

	if (m_overheating && !m_pauseFlashing)
	{
		if (!m_playAlarm)
		{
			m_playAlarm = true;
			m_soundManager.play("overcharge_alarm");
		}
		m_colorFlipTimer += App::getUpdateDeltaTime();
		if (m_colorFlipTimer > 0.3f)
		{
			if (m_overchargeBarLeft.getColor().g > 0.0f)
			{
				m_overchargeBarLeft.setColor(sf::Color(255u,0u,0u,m_overchargeBarLeft.getColor().a));
				m_overchargeBarRight.setColor(sf::Color(255u, 0u, 0u, m_overchargeBarRight.getColor().a));
				m_borderSprite.setColor(sf::Color::Red);
			}
			else
			{
				m_overchargeBarLeft.setColor(sf::Color(0u, 255u, 0u, m_overchargeBarLeft.getColor().a));
				m_overchargeBarRight.setColor(sf::Color(0u, 255u, 0u, m_overchargeBarRight.getColor().a));
				m_borderSprite.setColor(sf::Color::White);
			}
			m_colorFlipTimer = 0.0f;
		}
	}
	else
	{
		m_playAlarm = false;
		m_soundManager.stop("overcharge_alarm");
		m_overchargeBarLeft.setColor(sf::Color(0u, 255u, 0u, m_overchargeBarLeft.getColor().a));
		m_overchargeBarRight.setColor(sf::Color(0u, 255u, 0u, m_overchargeBarRight.getColor().a));
		m_borderSprite.setColor(sf::Color::White);
	}
	m_score.update();
}


/// <summary>
/// @brief Render object.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void GameUI::draw(Window & window, const float & deltaTime)
{
	window.draw(m_healthTemplateSprite);
	window.draw(m_healthLostSprite);
	window.draw(m_healthSprite);
	window.draw(m_borderSprite);
	window.draw(m_rechargeFrameRight);
	window.draw(m_rechargeBarRight);
	window.draw(m_rechargeFrameLeft);
	window.draw(m_rechargeBarLeft);
	window.draw(m_overchargeFrameLeft);
	window.draw(m_overchargeBarLeft);
	window.draw(m_overchargeFrameRight);
	window.draw(m_overchargeBarRight);
	m_score.draw(window, deltaTime);
	if (m_showPauseScreen)
	{
		m_gui->draw(window);
	}
	if (m_showGameEnd)
	{
		m_gameEndUI->draw(window);
	}
}

/// <summary>
/// @brief Set up the UI by loading textures into resource handler.
/// 
/// 
/// </summary>
/// <param name="sptrResources">reference to the resource struct</param>
/// <param name="resourceHandler">reference to resource handler</param>
/// <param name="UIParser">the json ui parser ready to be parsed</param>
void GameUI::setup(std::shared_ptr<gameUi::Resources> sptrResources, ResourceHandler & resourceHandler, js::json & UIParser)
{
	std::string const JSON_HEALTH_TEMPLATE_TEXTURE("healthTemplate");
	std::string const JSON_HEALTH_TEXTURE("health");
	std::string const JSON_BUTTON_FONT("font");
	std::string const JSON_BUTTON_TEXTURE("buttonTexture");
	std::string const JSON_RECHARGE_BAR_TEXTURE("rechargeBar");
	std::string const JSON_RECHARGE_FRAME_TEXTURE("rechargeFrame");
	std::string const JSON_BORDER_TEXTURE("border");
	std::string const JSON_OVERCHARGE_FRAME_TEXTURE("overchargeFrame");


	sptrResources->m_sptrHealthTemplateTexture = resourceHandler.loadUp<sf::Texture>(UIParser.at(JSON_HEALTH_TEMPLATE_TEXTURE).get<std::string>(), JSON_HEALTH_TEMPLATE_TEXTURE);
	sptrResources->m_sptrHealthTexture = resourceHandler.loadUp<sf::Texture>(UIParser.at(JSON_HEALTH_TEXTURE).get<std::string>(), JSON_HEALTH_TEXTURE);

	sptrResources->m_sptrButtonFont = resourceHandler.loadUp<sf::Font>(UIParser.at(JSON_BUTTON_FONT).get<std::string>(), JSON_BUTTON_FONT);
	sptrResources->m_sptrButtonTexture = resourceHandler.loadUp<sf::Texture>(UIParser.at(JSON_BUTTON_TEXTURE).get<std::string>(), JSON_BUTTON_TEXTURE);

	sptrResources->m_sptrRechargeBarTexture = resourceHandler.loadUp<sf::Texture>(UIParser.at(JSON_RECHARGE_BAR_TEXTURE).get<std::string>(), JSON_RECHARGE_BAR_TEXTURE);
	sptrResources->m_sptrRechargeBarFrameTexture = resourceHandler.loadUp<sf::Texture>(UIParser.at(JSON_RECHARGE_FRAME_TEXTURE).get<std::string>(), JSON_RECHARGE_FRAME_TEXTURE);
	sptrResources->m_sptrOverchargeFrameTexture = resourceHandler.loadUp<sf::Texture>(UIParser.at(JSON_OVERCHARGE_FRAME_TEXTURE).get<std::string>(), JSON_OVERCHARGE_FRAME_TEXTURE);

	sptrResources->m_sptrBorderTexture = resourceHandler.loadUp<sf::Texture>(UIParser.at(JSON_BORDER_TEXTURE).get<std::string>(), JSON_BORDER_TEXTURE);

}

/// <summary>
/// @brief this function initializes the UI.
/// 
/// 
/// </summary>
/// <param name="resources">pointer to the resource struct</param>
void GameUI::init(std::shared_ptr<gameUi::Resources> resources)
{
	//initialize the health template sprite
	m_healthTemplateSprite.setTexture(*resources->m_sptrHealthTemplateTexture, false);
	m_healthTemplateSprite.setOrigin(m_healthTemplateSprite.getLocalBounds().width / 2, m_healthTemplateSprite.getLocalBounds().height / 2);
	m_healthTemplatePosition.x /= 2;
	m_healthTemplatePosition.y -= (m_healthTemplateSprite.getLocalBounds().height + 25.0f);
	m_healthTemplateSprite.setPosition(m_healthTemplatePosition);

	//initialize the health sprite
	m_healthSprite.setTexture(*resources->m_sptrHealthTexture, false);
	m_healthSprite.setOrigin(0.0f, m_healthSprite.getGlobalBounds().height / 2);
	m_healthSprite.setPosition(sf::Vector2f(m_healthTemplatePosition.x - 75.0f, m_healthTemplatePosition.y));

	//initialize the health lost sprite
	m_healthLostSprite.setTexture(*resources->m_sptrHealthTexture, false);
	m_healthLostSprite.setOrigin(0.0f, m_healthLostSprite.getGlobalBounds().height / 2);
	m_healthLostSprite.setPosition(sf::Vector2f(m_healthTemplatePosition.x - 75.0f, m_healthTemplatePosition.y));
	m_healthLostSprite.setColor(sf::Color(255u, 255u, 100u, 255u));

	//initialize the collision rectangle
	m_healthCollisionRect.min.x = m_healthTemplatePosition.x - (m_healthTemplateSprite.getLocalBounds().width / 2);
	m_healthCollisionRect.min.y = m_healthTemplatePosition.y - (m_healthTemplateSprite.getLocalBounds().height / 2);
	m_healthCollisionRect.max.x = m_healthTemplatePosition.x + (m_healthTemplateSprite.getLocalBounds().width / 2);
	m_healthCollisionRect.max.y = m_healthTemplatePosition.y + (m_healthTemplateSprite.getLocalBounds().height / 2);

	//initialize border
	m_borderSprite.setTexture(*resources->m_sptrBorderTexture, false);
	m_borderSprite.setScale(sf::Vector2f(0.724f, 0.73f));

	//initialize right recharge BAR
	m_rechargeBarRight.setTexture(*resources->m_sptrRechargeBarTexture, false);
	m_rechargeBarRight.setOrigin(m_rechargeBarRight.getLocalBounds().width / 2, m_rechargeBarRight.getLocalBounds().height);
	m_rechargeBarRight.setPosition(sf::Vector2f(App::getViewSize().x - 50.0f, (App::getViewSize().y / 2) + (m_rechargeBarRight.getLocalBounds().height / 2)));
	m_rechargeBarRight.setColor(sf::Color(73, 237, 237));


	//initialize right recharge FRAME
	m_rechargeFrameRight.setTexture(*resources->m_sptrRechargeBarFrameTexture, false);
	m_rechargeFrameRight.setOrigin(m_rechargeFrameRight.getLocalBounds().width / 2, m_rechargeFrameRight.getLocalBounds().height);
	m_rechargeFrameRight.setPosition(m_rechargeBarRight.getPosition().x - 1.6f, m_rechargeBarRight.getPosition().y + 25.0f);


	//initialize left recharge BAR
	m_rechargeBarLeft.setTexture(*resources->m_sptrRechargeBarTexture, false);
	m_rechargeBarLeft.setOrigin(m_rechargeBarLeft.getLocalBounds().width / 2, m_rechargeBarLeft.getLocalBounds().height);
	m_rechargeBarLeft.setPosition(sf::Vector2f(50.0f, (App::getViewSize().y / 2) + (m_rechargeBarLeft.getLocalBounds().height / 2)));
	m_rechargeBarLeft.setScale(1.0f, 1.0f);
	m_rechargeBarLeft.setColor(sf::Color(73, 237, 237));

	//initialize left recharge FRAME
	m_rechargeFrameLeft.setTexture(*resources->m_sptrRechargeBarFrameTexture, false);
	m_rechargeFrameLeft.setOrigin(m_rechargeFrameLeft.getLocalBounds().width / 2, m_rechargeFrameLeft.getLocalBounds().height);
	m_rechargeFrameLeft.setPosition(m_rechargeBarLeft.getPosition().x - 1.6f, m_rechargeBarLeft.getPosition().y + 25.0f);

	//initialize the left overcharge BAR
	m_overchargeBarLeft.setTexture(*resources->m_sptrRechargeBarTexture, false);
	m_overchargeBarLeft.setOrigin(m_overchargeBarLeft.getLocalBounds().width / 2, m_overchargeBarLeft.getLocalBounds().height);
	m_overchargeBarLeft.setPosition(sf::Vector2f(25.0f, (App::getViewSize().y / 2) + (m_overchargeBarLeft.getLocalBounds().height / 2)));
	m_overchargeBarLeft.setColor(sf::Color(0, 255, 0));

	//initialize left overcharge FRAME
	m_overchargeFrameLeft.setTexture(*resources->m_sptrOverchargeFrameTexture, false);
	m_overchargeFrameLeft.setOrigin(m_overchargeFrameLeft.getLocalBounds().width / 2, m_overchargeFrameLeft.getLocalBounds().height);
	m_overchargeFrameLeft.setPosition(m_overchargeBarLeft.getPosition().x - 1.6f, m_overchargeBarLeft.getPosition().y + 25.0f);

	//initialize the right overcharge BAR
	m_overchargeBarRight.setTexture(*resources->m_sptrRechargeBarTexture, false);
	m_overchargeBarRight.setOrigin(m_overchargeBarRight.getLocalBounds().width / 2, m_overchargeBarRight.getLocalBounds().height);
	m_overchargeBarRight.setPosition(sf::Vector2f(App::getViewSize().x - 25.0f, (App::getViewSize().y / 2) + (m_overchargeBarRight.getLocalBounds().height / 2)));
	m_overchargeBarRight.setColor(sf::Color(0, 255, 0));

	//initialize right overcharge FRAME
	m_overchargeFrameRight.setTexture(*resources->m_sptrOverchargeFrameTexture, false);
	m_overchargeFrameRight.setOrigin(m_overchargeFrameRight.getLocalBounds().width / 2, m_overchargeFrameRight.getLocalBounds().height);
	m_overchargeFrameRight.setPosition(m_overchargeBarRight.getPosition().x - 1.6f, m_overchargeBarRight.getPosition().y + 25.0f);


	//initialize right ui collision rect
	m_leftUICollisionRect.min.x = m_overchargeFrameLeft.getPosition().x - (m_overchargeFrameLeft.getLocalBounds().width / 2);
	m_leftUICollisionRect.min.y = m_overchargeFrameLeft.getPosition().y - (m_overchargeFrameLeft.getLocalBounds().height);
	m_leftUICollisionRect.max.x = m_rechargeFrameLeft.getPosition().x + (m_rechargeFrameLeft.getLocalBounds().width / 2);
	m_leftUICollisionRect.max.y = m_rechargeFrameLeft.getPosition().y;

	//initialize left ui collision rect
	m_rightUICollisionRect.min.x = m_overchargeFrameRight.getPosition().x - (m_overchargeFrameRight.getLocalBounds().width / 2);
	m_rightUICollisionRect.min.y = m_overchargeFrameRight.getPosition().y - (m_overchargeFrameRight.getLocalBounds().height);
	m_rightUICollisionRect.max.x = m_rechargeFrameRight.getPosition().x + (m_rechargeFrameRight.getLocalBounds().width / 2);
	m_rightUICollisionRect.max.y = m_rechargeFrameRight.getPosition().y;


	//initiailze the pause screen
	const sf::Vector2f & zero = sf::Vector2f(0.0f, 0.0f);
	auto sptrButtonFont = resources->m_sptrButtonFont;
	auto sptrButtonTexture = resources->m_sptrButtonTexture;

	m_gui->addButton(
		std::bind(&GameUI::btnResume, this),
		"Resume",
		zero,
		sptrButtonFont,
		24,
		sptrButtonTexture,
		gui::Button::s_TEXT_RECT_LEFT,
		gui::Button::s_TEXT_RECT_MID,
		gui::Button::s_TEXT_RECT_RIGHT
	);
	m_gui->addButton(
		m_mainMenuFunc,
		"Exit",
		zero,
		sptrButtonFont,
		24,
		sptrButtonTexture,
		gui::Button::s_TEXT_RECT_LEFT,
		gui::Button::s_TEXT_RECT_MID,
		gui::Button::s_TEXT_RECT_RIGHT
	);
	m_gameEndUI->addButton(
		m_restartGameFunc,
		"Restart",
		zero,
		sptrButtonFont,
		24,
		sptrButtonTexture,
		gui::Button::s_TEXT_RECT_LEFT,
		gui::Button::s_TEXT_RECT_MID,
		gui::Button::s_TEXT_RECT_RIGHT
	);
	m_gameEndUI->addButton(
		m_mainMenuFunc,
		"Exit",
		zero,
		sptrButtonFont,
		24,
		sptrButtonTexture,
		gui::Button::s_TEXT_RECT_LEFT,
		gui::Button::s_TEXT_RECT_MID,
		gui::Button::s_TEXT_RECT_RIGHT
	);
	m_gui->addLabel("Pause", 50u, sf::Vector2f(App::getViewSize().x / 2.0f, App::getViewSize().y * 0.1f), sptrButtonFont, sf::Color::White);
	const auto& windowSize = App::getViewSize();
	m_gui->configure(gui::GUI::Layouts::StackVertically, windowSize);
	m_gameEndUI->configure(gui::GUI::Layouts::StackVertically, windowSize);
	m_score.init(resources);
}

/// <summary>
/// @brief this function will turn the health to be taken away into a percentage 
/// and scale down the scale sprite accordingly.
/// 
/// 
/// </summary>
/// <param name="health">float value for health to be taken away</param>
void GameUI::decrementHealth(const float & health)
{
	float healthLost = health / 100.0f;
	m_targetHealth = m_healthSprite.getScale().x - healthLost;
	if (m_healthSprite.getScale().x > 0)
	{
		m_healthSprite.setScale(sf::Vector2f(m_healthSprite.getScale().x - healthLost, 1.0f));
	}
	else
	{
		m_healthSprite.setScale(sf::Vector2f(0.0f,1.0f));
	}
}

/// <summary>
/// @brief this function returns a constant reference to the health collision box.
/// 
/// 
/// </summary>
/// <returns>constant reference to a c2AABB rectangle which represents the collision box.</returns>
const tinyh::c2AABB & GameUI::getHealthCollisionBox()
{
	return m_healthCollisionRect;
}

/// <summary>
/// @brief getter for right ui collision box.
/// 
/// 
/// </summary>
/// <returns>constant reference to collision box</returns>
const tinyh::c2AABB & GameUI::getRightUICollisionBox()
{
	return m_rightUICollisionRect;
}

/// <summary>
/// @brief getter for left ui collision box.
/// 
/// 
/// </summary>
/// <returns>constant reference to collision box</returns>
const tinyh::c2AABB & GameUI::getLeftUICollisionBox()
{
	return m_leftUICollisionRect;
}

/// <summary>
/// @brief This function sets the alpha of health components to passed in value.
/// 
/// 
/// </summary>
/// <param name="alphaVal">the new value of alpha</param>
void GameUI::setHealthTransparency(sf::Uint8 alphaVal)
{
	m_healthSprite.setColor(sf::Color(m_healthSprite.getColor().r, m_healthSprite.getColor().g, m_healthSprite.getColor().b, alphaVal));
	m_healthTemplateSprite.setColor(sf::Color(m_healthTemplateSprite.getColor().r, m_healthTemplateSprite.getColor().g, m_healthTemplateSprite.getColor().b, alphaVal));
	m_healthLostSprite.setColor(sf::Color(m_healthLostSprite.getColor().r, m_healthLostSprite.getColor().g, m_healthLostSprite.getColor().b, alphaVal));
}

/// <summary>
/// @brief set transparency of right UI elements.
/// 
/// 
/// </summary>
/// <param name="alphaVal">new UI value of right UI elements</param>
void GameUI::setRightBarsTransparency(sf::Uint8 alphaVal)
{
	m_overchargeBarRight.setColor(sf::Color(m_overchargeBarRight.getColor().r, m_overchargeBarRight.getColor().g, m_overchargeBarRight.getColor().b, alphaVal));
	m_rechargeBarRight.setColor(sf::Color(m_rechargeBarRight.getColor().r, m_rechargeBarRight.getColor().g, m_rechargeBarRight.getColor().b, alphaVal));
	m_overchargeFrameRight.setColor(sf::Color(m_overchargeFrameRight.getColor().r, m_overchargeFrameRight.getColor().g, m_overchargeFrameRight.getColor().b, alphaVal));
	m_rechargeFrameRight.setColor(sf::Color(m_rechargeFrameRight.getColor().r, m_rechargeFrameRight.getColor().g, m_rechargeFrameRight.getColor().b, alphaVal));
}

/// <summary>
/// @brief set transparency of Left UI elements.
/// 
/// 
/// </summary>
/// <param name="alphaVal">new UI value of Left UI elements</param>
void GameUI::setLeftBarsTransparency(sf::Uint8 alphaVal)
{
	m_overchargeBarLeft.setColor(sf::Color(m_overchargeBarLeft.getColor().r, m_overchargeBarLeft.getColor().g, m_overchargeBarLeft.getColor().b, alphaVal));
	m_rechargeBarLeft.setColor(sf::Color(m_rechargeBarLeft.getColor().r, m_rechargeBarLeft.getColor().g, m_rechargeBarLeft.getColor().b, alphaVal));
	m_overchargeFrameLeft.setColor(sf::Color(m_overchargeFrameLeft.getColor().r, m_overchargeFrameLeft.getColor().g, m_overchargeFrameLeft.getColor().b, alphaVal));
	m_rechargeFrameLeft.setColor(sf::Color(m_rechargeFrameLeft.getColor().r, m_rechargeFrameLeft.getColor().g, m_rechargeFrameLeft.getColor().b, alphaVal));
}

/// <summary>
/// @brief this disables the pause screen.
/// 
/// 
/// </summary>
void GameUI::btnResume()
{
	m_showPauseScreen = false;
}

/// <summary>
/// @brief setter of the m_showPauseScreen boolean.
/// 
/// 
/// </summary>
/// <param name="check">boolean that represents the new value of show pause screen</param>
void GameUI::setPaused(bool check)
{
	if (check)
	{
		m_gui->resetSelectedWidget();
	}
	m_showPauseScreen = check;
}

/// <summary>
/// @brief getter for the show pause screen bool.
/// 
/// 
/// </summary>
/// <returns>the m_showPauseScreen state</returns>
bool GameUI::getPaused()
{
	return m_showPauseScreen;
}

/// <summary>
/// @brief method that will determine if we show game end screen.
/// 
/// 
/// </summary>
/// <param name="check">new value of the show game end bool</param>
void GameUI::setShowEnd(bool check)
{
	if (check)
	{
		m_gameEndUI->resetSelectedWidget();
	}
	m_showGameEnd = check;
}

/// <summary>
/// @brief a getter for the show end game bool.
/// 
///
/// </summary>
/// <returns>returns m_showGameEnd bool</returns>
bool GameUI::getShowEnd()
{
	return m_showGameEnd;
}

/// <summary>
/// @brief set the target of the recharge value.
/// 
/// 
/// </summary>
/// <param name="val">new target for recharge</param>
void GameUI::setRecharge(float val)
{
	m_targetRecharge = val;
}

/// <summary>
/// @brief this method resets the game ui.
/// 
/// 
/// </summary>
void GameUI::reset()
{
	m_score.reset();
	m_healthSprite.setScale(1.0f, 1.0f);
	m_healthLostSprite.setScale(1.0f, 1.0f);
	m_targetHealth = 1.0f;
	m_showPauseScreen = false;
	m_showGameEnd = false;
	m_pauseFlashing = false;
	m_rechargeHealth = false;
	m_timeUntilOverheatingVoice = 10.0f;
	m_overheatingVoiceTimer = 0.0f;
}

/// <summary>
/// @brief setter for the fire rate.
/// 
/// 
/// </summary>
/// <param name="val">new value of fire rate</param>
void GameUI::setFireRate(float val)
{
	m_fireRateVal = val;
}

/// <summary>
/// @brief setter for the time since fire.
/// 
/// 
/// </summary>
/// <param name="val">new value of time since fire</param>
void GameUI::setTimeSinceFire(float val)
{
	m_timeSinceFire = val;
}

/// <summary>
/// @brief update the overcharge value to represent actual overcharge.
/// 
/// 
/// </summary>
/// <param name="overchargeValue">the actual overcharge value</param>
void GameUI::updateOvercharge(float overchargeValue)
{
	m_overchargeBarLeft.setScale(m_overchargeBarLeft.getScale().x, overchargeValue);
	m_overchargeBarRight.setScale(m_overchargeBarRight.getScale().x, overchargeValue);
	if (m_overheatingVoiceTimer > m_timeUntilOverheatingVoice)
	{
		if (overchargeValue > 0.6 && !m_overheating)
		{
			m_overheatingVoiceTimer = 0.0f;
			auto random = (rand() % 2 + 1); //generate number between 1 and 2
			if (random == 1)
			{
				m_soundManager.play("overheat1", false);
			}
			else if (random == 2)
			{
				m_soundManager.play("overheat2", false);
			}
		}
	}

}

/// <summary>
/// @brief setter for the overheat bool
/// 
/// 
/// </summary>
/// <param name="check">new overheat value</param>
void GameUI::setOverheat(bool check)
{
	m_overheating = check;
}

/// <summary>
/// @brief setter that will make the ui start or stop flashing.
/// 
/// 
/// </summary>
/// <param name="check">new value of the flashing bool</param>
void GameUI::setPauseFlashing(bool check)
{
	m_pauseFlashing = check;
}

/// <summary>
/// 
/// </summary>
/// <param name="newHealth"></param>
void GameUI::rechargeHealth(float const & newHealth)
{
	m_rechargeHealth = true;
	m_targetHealth = newHealth / 100.0f;
	m_healthLostSprite.setScale(m_targetHealth, 1.0f);
}
/// @brief set target health value.
/// 
/// 
/// </summary>
/// <param name="playerHealth"></param>
void GameUI::setTargetHealth(const float & playerHealth)
{
	m_targetHealth = playerHealth / 100.0f;

	//float healthLost = health / 100.0f;
	//m_targetHealth = m_healthSprite.getScale().x - healthLost;
	auto healthScale = playerHealth * (1.0f / 100.0f);
	if (m_healthSprite.getScale().x > 0)
	{
		m_healthSprite.setScale(sf::Vector2f(healthScale , 1.0f));
	}
	else
	{
		m_healthSprite.setScale(sf::Vector2f(0.0f, 1.0f));
	}
}
