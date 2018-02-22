#ifndef SCORE_H
#define SCORE_H

// STD Includes
#include <string>
#include <sstream>
#include <memory>
// SFML Includes
#include "SFML\Graphics\Text.hpp"
// Project Includes
#include "system\Window.h"
#include "GameUiResources.h"

/// 
/// @brief 
/// @author Rafael Plugge
/// 
/// 
/// 
class Score
{
public: // Constructors/Assignment Operators/Destructor
	Score();
	Score(Score const &) = default;
	Score(Score &&) = default;

	Score & operator=(Score const &) = default;
	Score & operator=(Score &&) = default;

	~Score() = default;

public: // Public Member Functions
	void init(std::shared_ptr<gameUi::Resources> sptrResources);
	void update();
	void draw(Window & window, float const & deltaTime);
	void reset();
public: // Public Member Get's
public: // Public Member Set's
public: // Public Member Variables
public: // Public Static Variables
	/// <summary>
	/// @brief Defines the current score.
	/// 
	/// 
	/// </summary>
	static int s_scoreCurrent;
	static int SCORE_FOR_ASTEROID;
	static int SCORE_FOR_RANGED;
	static int SCORE_FOR_BASIC;
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
private: // Private Member Variables
	/// <summary>
	/// @brief Defines the string `Score: `.
	/// 
	/// 
	/// </summary>
	std::stringstream m_scoreStream;
	/// <summary>
	/// @brief Displays current score.
	/// 
	/// 
	/// </summary>
	sf::Text m_scoreDisplay;

	/// <summary>
	/// @brief current target score.
	/// 
	/// 
	/// </summary>
	int m_scoreTarget;

	/// <summary>
	/// @brief current score displayed on label.
	/// 
	/// 
	/// </summary>
	int m_scoreDisplaying;

	/// <summary>
	/// @brief is score to be scaling.
	/// 
	/// 
	/// </summary>
	bool m_scaling;

	/// <summary>
	/// @brief is score scaling up.
	/// 
	/// 
	/// </summary>
	bool m_scalingUp;

	/// <summary>
	/// @brief is score scaling down.
	/// 
	/// 
	/// </summary>
	bool m_scalingDown;
};


#endif // !SCORE_H