#include "entities\ai\ranged\AiRangedState.h"

ai::states::AiRangedState::AiRangedState(AiRanged * aiUnit)
	: ai::states::AiBaseState()
	, m_ai(aiUnit)
{
}
