#include "entities\ai\AiBaseState.h"

/// <summary>
/// @brief Base State default constructor.
/// 
/// 
/// </summary>
ai::states::AiBaseState::AiBaseState()
	: m_DELTA_TIME(App::getUpdateDeltaTime())
{
}
