#include "entities\ai\basic\ABSearchState.h"

/// <summary>
/// 
/// </summary>
/// <param name="aiUnit"></param>
ai::states::AiBasicSearchState::AiBasicSearchState(AiBasic & aiUnit)
	: ai::states::AiBasicState(aiUnit)
{
}

/// <summary>
/// 
/// </summary>
void ai::states::AiBasicSearchState::update()
{
	// If player found
	// change state
}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
/// <param name="deltaTime"></param>
void ai::states::AiBasicSearchState::draw(Window & window, float const & deltaTime)
{
}
