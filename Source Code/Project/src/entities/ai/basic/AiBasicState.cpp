#include "entities\ai\basic\AiBasicState.h"


/// <summary>
/// @brief Construct our Basic State.
/// 
/// 
/// </summary>
ai::states::AiBasicState::AiBasicState(AiBasic & aiUnit)
	: ai::states::AiBaseState()
	, m_ai(aiUnit)
{
}

/// <summary>
/// Checks if there is a collision between this state's hitboxes and the collision primitive.
/// </summary>
/// <param name="collision">read-only reference to a 2d collision AABB rectangle.</param>
/// <returns>True if collisions has occured.</returns>
bool ai::states::AiBasicState::checkCollision(tinyh::c2AABB const & collision)
{
	return tinyh::c2AABBtoAABB(m_ai.m_collisionRect, collision);
}

/// <summary>
/// Checks if there is a collision between this state's hitboxes and the collision primitive.
/// </summary>
/// <param name="collision">read-only reference to a 2d collision circle.</param>
/// <returns>True if collisions has occured.</returns>
bool ai::states::AiBasicState::checkCollision(tinyh::c2Circle const & collision)
{
	return tinyh::c2CircletoAABB(collision, m_ai.m_collisionRect);
}

/// <summary>
/// Checks if there is a collision between this state's hitboxes and the collision primitive.
/// </summary>
/// <param name="collision">read-only reference to a 2d collision capsule.</param>
/// <returns>True if collisions has occured.</returns>
bool ai::states::AiBasicState::checkCollision(tinyh::c2Capsule const & collision)
{
	return tinyh::c2AABBtoCapsule(m_ai.m_collisionRect, collision);
}