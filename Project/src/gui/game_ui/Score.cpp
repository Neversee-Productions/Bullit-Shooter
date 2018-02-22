#include "gui\game_ui\Score.h"

int Score::s_scoreCurrent = 0;

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Score::Score()
	: m_scoreStream("Score: ")
	, m_scoreDisplay()
{
	m_scoreStream << "Score: ";
}

/// <summary>
/// @brief Initialize resources.
/// 
/// 
/// </summary>
/// <param name="sptrResources">shared pointer to initialized resources.</param>
void Score::init(std::shared_ptr<gameUi::Resources> sptrResources)
{
	m_scoreDisplay.setFont(*sptrResources->m_sptrButtonFont);
	m_scoreDisplay.setFillColor(sf::Color::White);
	m_scoreDisplay.setOutlineColor(sf::Color::Black);
	m_scoreDisplay.setString(m_scoreStream.str() + std::to_string(s_scoreCurrent));
	m_scoreDisplay.setOrigin(
		m_scoreDisplay.getGlobalBounds().width * 0.5f,
		m_scoreDisplay.getGlobalBounds().height * 0.5f
	);
	m_scoreDisplay.setPosition(
		App::getViewSizeI().x * 0.5f,
		App::getViewSizeI().y * 0.1f
	);
}

/// <summary>
/// @brief Update score.
/// 
/// 
/// </summary>
void Score::update()
{
}

/// <summary>
/// @brief Render score to target.
/// 
/// 
/// </summary>
/// <param name="window">reference to the target window.</param>
/// <param name="deltaTime">read-only reference to the delta time.</param>
void Score::draw(Window & window, float const & deltaTime)
{
	m_scoreDisplay.setString(m_scoreStream.str() + std::to_string(s_scoreCurrent));
	m_scoreDisplay.setOrigin(
		m_scoreDisplay.getGlobalBounds().width * 0.5f,
		m_scoreDisplay.getGlobalBounds().height * 0.5f
	);
	window.draw(m_scoreDisplay);
}
