#include "entities\Progression.h"

int Progression::s_spawnBasicEnemies = 1;

/// <summary>
/// @brief Default Constructor.
/// 
/// 
/// </summary>
/// <param name="asteroidManager">reference to asteroid manager.</param>
/// <param name="basicEnemyManager">reference to basic enemy manager.</param>
/// <param name="rangedEnemyManager">reference ranged enemy manager.</param>
Progression::Progression(
	Player & player
	, AsteroidManager & asteroidManager
	, BasicEnemyManager & basicEnemyManager
	, RangedEnemyManager & rangedEnemyManager
)
	: m_player(player)
	, m_asteroidManager(asteroidManager)
	, m_basicEnemyManager(basicEnemyManager)
	, m_rangedEnemyManager(rangedEnemyManager)
	, m_SCORE(Score::s_scoreCurrent)
	, m_timer()
	, m_UPDATE_DT_TIME(sf::seconds(App::getUpdateDeltaTime()))
	, m_DIF_INC(10.0f)
	, m_difficultyLevel(0u)
	, m_difficultyWentUp(false)
	, m_RANGED_ENEMY_SPAWN_CAP(20)
	, m_BASIC_ENEMY_SPAWN_CAP(5)
	, m_ASTEROID_SPAWN_CAP(40)
	, m_rangedEnemySpawnAmount(0)
{
	this->reset();
}

/// <summary>
/// @brief 
/// </summary>
/// <param name="sptrResources"></param>
void Progression::init(std::shared_ptr<gameUi::Resources> sptrResources)
{
	m_timerDisplay.setFont(*sptrResources->m_sptrButtonFont);
}

/// <summary>
/// @brief Resets level progression.
/// 
/// 
/// </summary>
void Progression::reset()
{
	m_timer = sf::Time::Zero;
	m_difficultyWentUp = false;
	m_difficultyLevel = 0u;
	m_rangedEnemySpawnAmount = 0;
	s_spawnBasicEnemies = 1;
	m_timerDisplay.setPosition(100.0f, 200.0f);
	m_timerDisplay.setFillColor(sf::Color::White);
	m_timerDisplay.setOutlineColor(sf::Color::Black);
	m_timerDisplay.setOutlineThickness(2.0f);
}

/// <summary>
/// @brief Updates the timer of progression.
/// 
/// 
/// </summary>
void Progression::update()
{
	m_timer += m_UPDATE_DT_TIME;
	if (m_timer > sf::seconds(m_DIF_INC * static_cast<float>(m_difficultyLevel + 1)))
	{
		m_difficultyWentUp = true;
		if (m_difficultyLevel < 255u)
		{
			++m_difficultyLevel;
		}
		if (m_asteroidManager.s_spawnAmount < m_ASTEROID_SPAWN_CAP)
		{
			m_asteroidManager.s_spawnAmount += 1;
		}
		this->spawnRangedEnemies();
		if (s_spawnBasicEnemies < m_RANGED_ENEMY_SPAWN_CAP)
		{
			++s_spawnBasicEnemies;
		}
	}
}

/// <summary>
/// @brief Draws any progression indicators.
/// 
/// 
/// </summary>
/// <param name="window">reference to the window.</param>
/// <param name="deltaTime">read-only reference to the draw delta time.</param>
void Progression::draw(Window & window, float const & deltaTime)
{
	if (m_difficultyWentUp)
	{
		m_difficultyWentUp = false;
		// Difficulty went up draw something.
	}
#ifdef _DEBUG
	std::string displayStr = "Time: " + std::to_string(m_timer.asSeconds());
	displayStr.append("\n");
	displayStr.append("Level: " + std::to_string(m_difficultyLevel + 1));
	m_timerDisplay.setString(displayStr);
	window.draw(m_timerDisplay);
#endif // _DEBUG
}

/// <summary>
/// @brief Spawns ranged enemies.
/// 
/// 
/// </summary>
void Progression::spawnRangedEnemies()
{
	if (m_rangedEnemySpawnAmount < m_RANGED_ENEMY_SPAWN_CAP)
	{
		++m_rangedEnemySpawnAmount;
	}
	for (int i = 0; i < m_rangedEnemySpawnAmount; ++i)
	{
		m_rangedEnemyManager.spawn(this->randRangedEnemySpawn());
	}
}

/// <summary>
/// @brief random ranged enemy spawn.
/// 
/// Ranged enemies need to spawn off screen.
/// </summary>
/// <returns></returns>
sf::Vector2f Progression::randRangedEnemySpawn()
{
	bool spawnRight = static_cast<bool>(rand() % 2); // random 1 or 0
	float offsetX = static_cast<float>(rand() % 100 + 1); // random 1 to 100
	offsetX += static_cast<float>(rand() % 100 + 1) / 100.0f; // random 0.001 to 0.100
	float offsetY = static_cast<float>(rand() % 200 + 1); // random 1 to 200
	offsetY += static_cast<float>(rand() % 200 + 1) / 100.0f; // random 0.1 to 0.200
	if (spawnRight)
	{
		return { offsetX + App::getViewSizeF().x, -offsetY - 100.0f };
	}
	else
	{
		return { -offsetX - 100.0f, -offsetY - 100.0f };
	}
}
