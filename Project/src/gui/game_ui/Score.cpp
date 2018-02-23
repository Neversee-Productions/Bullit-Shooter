#include "gui\game_ui\Score.h"

int Score::s_scoreCurrent = 0;
int Score::SCORE_FOR_ASTEROID = 1000;
int Score::SCORE_FOR_BASIC = 1500;
int Score::SCORE_FOR_RANGED = 2000;


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Score::Score()
	: m_scoreStream("Score: ")
	, m_scoreDisplay()
	, m_scaling(false)
	, m_scalingUp(false)
	, m_scalingDown(false)
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
		App::getViewSizeI().x * 0.475f,
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
	if (m_scoreDisplaying < s_scoreCurrent)
	{
		m_scaling = true;
		if (s_scoreCurrent - m_scoreDisplaying > 6000)
		{
			m_scoreDisplaying += static_cast<int>((150 * 120) * App::getUpdateDeltaTime());
		}
		if (s_scoreCurrent - m_scoreDisplaying > 3000)
		{
			m_scoreDisplaying += static_cast<int>((35 * 120) * App::getUpdateDeltaTime());
		}
		else
		{
			m_scoreDisplaying += static_cast<int>((10 * 120) * App::getUpdateDeltaTime());
		}
		if (m_scoreDisplaying > s_scoreCurrent)
		{
			m_scaling = false;
			m_scoreDisplaying = s_scoreCurrent;
		}
	}
	if (m_scaling && m_scalingUp)
	{
		m_scoreDisplay.setScale(m_scoreDisplay.getScale().x + 0.01f, m_scoreDisplay.getScale().y + 0.01f);
		if (m_scoreDisplay.getScale().x > 2)
		{
			m_scalingUp = false;
			m_scalingDown = true;
			m_scoreDisplay.setScale(2.0f, 2.0f);
		}
	}
	else if (m_scalingDown)
	{
		m_scoreDisplay.setScale(m_scoreDisplay.getScale().x - 0.01f, m_scoreDisplay.getScale().y - 0.01f);
		if (m_scoreDisplay.getScale().x < 1)
		{
			m_scalingUp = false;
			m_scalingDown = true;
			m_scoreDisplay.setScale(1.0f, 1.0f);
		}
	}
	else
	{
		m_scalingUp = true;
		m_scalingDown = false;
		if (m_scoreDisplay.getScale().x > 1)
		{
			m_scoreDisplay.setScale(m_scoreDisplay.getScale().x - 0.01f, m_scoreDisplay.getScale().y - 0.01f);
			if (m_scoreDisplay.getScale().x < 1)
			{
				m_scoreDisplay.setScale(1.0f, 1.0f);
			}
		}
	}
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
	m_scoreDisplay.setString(m_scoreStream.str() + std::to_string(m_scoreDisplaying));
	window.draw(m_scoreDisplay);
}

/// <summary>
/// @brief method to reset the score.
/// 
/// 
/// </summary>
void Score::reset()
{
	m_scoreDisplay.setOutlineColor(sf::Color::Black);
	m_scoreDisplay.setOutlineThickness(2.0f);

	m_scoreDisplaying = 0;
	m_scoreTarget = 0;
	s_scoreCurrent = 0;
	m_scaling = false;
	m_scalingDown = false;
	m_scalingUp = false;
}
