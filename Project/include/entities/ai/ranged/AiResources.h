#ifndef AI_RESOURCES
#define AI_RESOURCES

#include "entities\ai\AiBase.h"

namespace ai
{
	/// 
	/// @brief Defines the assets required by this ai.
	/// @author Rafael Plugge
	/// 
	/// 
	struct Resources : public ai::AiBase::Resources
	{
		ai::AiBase::Resources::Texture m_textureMove;
		ai::AiBase::Resources::Texture m_textureDeploy;
		ai::AiBase::Resources::Texture m_textureShoot;
		ai::AiBase::Resources::Texture m_textureEbola;

		ai::AiBase::Resources::Animation m_animationMove;
		ai::AiBase::Resources::Animation m_animationDeploy;
		ai::AiBase::Resources::Animation m_animationShoot;
		ai::AiBase::Resources::Animation m_animationEbola;
	};
}

#endif // !AI_RESOURCES