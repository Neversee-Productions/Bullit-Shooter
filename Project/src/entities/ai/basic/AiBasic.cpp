#include "entities\ai\basic\AiBasicState.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Construct our map of actions.
/// </summary>
ai::AiBasic::AiBasic(Player const & player)
	: AiBase()
	, m_player(player)
	, m_renderQuad({80.0f , 80.0f}) // Implicitly call sf::Vector2f() constructor
	, m_actions()
	, m_uptrAction(nullptr)
{
	// Create Search State
	std::unique_ptr<BasicState> sptrSearchState = std::make_unique<ai::states::Search>(ai::states::Search(*this));

	// First state
	m_uptrAction.swap(sptrSearchState);


}

/// <summary>
/// 
/// </summary>
/// <param name="sptrResources"></param>
void ai::AiBasic::init(std::shared_ptr<Resources> sptrResources)
{
}

/// <summary>
/// @brief 
/// </summary>
/// <param name="deltaTime"></param>
void ai::AiBasic::update(float const & deltaTime)
{
	if (m_uptrAction)
	{
		m_uptrAction->update();
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
/// <param name="deltaTime"></param>
void ai::AiBasic::draw(Window & window, float const & deltaTime)
{
	m_uptrAction->draw(window, deltaTime);
}
