#ifndef AI_BASE_H
#define AI_BASE_H

// STL Includes
#include <list>
#include <memory>
// SFML Includes
// Thor Includes
#include "Thor\Animations\FrameAnimation.hpp"
// Project Includes
#include "system\App.h"
#include "system\Window.h"
#include "system\ResourceHandler.h"

/// 
/// @author Rafael Plugge
/// @brief Scope for all Ai classes.
/// 
/// 
/// 
namespace ai
{

	/// 
	/// @author Rafael Plugge
	/// @brief Base class for all AI.
	/// 
	/// Describes AI interface.
	/// 
	class AiBase
	{
	public:
		
		/// 
		/// @author Rafael Plugge
		/// @brief Define the necessary resources.
		/// 
		/// Used by game scene to pass the required,
		/// resources that Ai needs
		/// 
		/// @note Classes derived from this on will have
		///		to create their own Resources struct.
		/// 
		struct Resources
		{
			/// 
			/// @author Rafael Plugge
			/// @brief Define the necessary resources for loading a texture.
			/// 
			/// Used by game scene to pass the required resources that Ai needs.
			/// Derived structs will use this struct to define what textures they want.
			/// 
			struct Texture
			{
				/// <summary>
				/// @brief Store the texture's ID.
				/// 
				/// 
				/// </summary>
				std::string m_id = "";
				/// <summary>
				/// @brief Store the origin of the texture.
				/// 
				/// 
				/// </summary>
				sf::Vector2f m_origin;
				/// <summary>
				/// @brief Store the scale of the texture.
				/// 
				/// 
				/// </summary>
				sf::Vector2f m_scale;
				/// <summary>
				/// @brief Store the texture rectangle.
				/// 
				/// Source rectangle 
				/// </summary>
				sf::IntRect m_textureRect;
				/// <summary>
				/// @brief Store shared pointer to texture.
				/// 
				/// uninitialized so that the resource handler can initialize it.
				/// </summary>
				std::shared_ptr<sf::Texture> m_sptrTexture = nullptr;
			};
			/// 
			/// @author Rafael Plugge
			/// @brief Define the necessary resources for loading a animation.
			/// 
			/// Used by game scene to pass the required resources that Ai needs.
			/// Derived structs will use this struct to define what animations they want.
			/// 
			struct Animation
			{
				/// <summary>
				/// @brief Defines the ID of the animation.
				/// 
				/// 
				/// </summary>
				std::string m_id = "";
				/// <summary>
				/// @brief Defines the duration of the animation.
				/// 
				/// 
				/// </summary>
				sf::Time m_duration;
				/// <summary>
				/// @brief Defines the origin of the animation frames.
				/// 
				/// 
				/// </summary>
				sf::Vector2f m_origin;
				/// <summary>
				/// @brief Defines shared pointer to our animation's frames.
				/// 
				/// 
				/// </summary>
				thor::FrameAnimation m_frames;
				/// <summary>
				/// @brief Defines shared pointer to our animation's texture.
				/// 
				/// 
				/// </summary>
				std::shared_ptr<sf::Texture> m_sptrTexture = nullptr;
			};
		};

	public:
		AiBase() = default;
		~AiBase() = default;
		virtual void update() abstract;
		virtual void draw(Window & window, float const & deltaTime) abstract;
		virtual bool decrementHealth(float const & damage);
	public:
		inline bool const & getActive() const { return m_active; }
		virtual bool checkCollision(tinyh::c2Circle const & collision) const abstract;
		virtual bool checkCollision(tinyh::c2AABB const & collision) const abstract;
		virtual bool checkCollision(tinyh::c2Capsule const & collision) const abstract;
	public:
		inline virtual void setActive(bool const & newActive) { m_active = newActive; }

	protected:
		static void setup(AiBase::Resources::Texture & textureResources, ResourceHandler & resourceHandler, js::json & textureParser, std::string const & id);
		static void setup(AiBase::Resources::Animation & animResources, ResourceHandler & resourceHandler, js::json & animationParser, std::string const & id);
	protected:
		/// <summary>
		/// @brief Store read-only reference to update delta time.
		/// 
		/// 
		/// </summary>
		static float const & s_DELTA_TIME;
		/// <summary>
		/// @brief Determines if enemy is active.
		/// 
		/// 
		/// </summary>
		bool m_active;
		/// <summary>
		/// @brief Pertains the ai's current health.
		/// 
		/// 
		/// </summary>
		float m_health;
	};

}
#endif // !AI_BASE_H