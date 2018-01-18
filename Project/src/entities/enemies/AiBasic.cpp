#include "entities\enemies\AiBasic.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Construct our map of actions.
/// </summary>
AiBasic::AiBasic()
	: AiBase()
	, m_renderQuad({80.0f , 80.0f}) // Implicitly call sf::Vector2f() constructor
{
}

/// <summary>
/// @brief 
/// </summary>
/// <param name="deltaTime"></param>
void AiBasic::update(float const & deltaTime)
{
}

void AiBasic::draw(Window & window, float const & deltaTime)
{
}

void AiBasic::passiveSearch(AiBasic & ai)
{
}

void AiBasic::spottedPlayer(AiBasic & ai, sf::Vector2f const & playerPosition)
{
}

void AiBasic::approachPlayer(AiBasic & ai, sf::Vector2f const & playerPosition)
{
}

void AiBasic::attackPlayer(AiBasic & ai, sf::Vector2f const & playerPosition)
{
}
