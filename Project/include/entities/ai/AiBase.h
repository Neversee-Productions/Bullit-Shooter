#ifndef AI_BASE_H
#define AI_BASE_H

// STL Includes
#include <list>
#include <memory>
// SFML Includes
// Thor Includes
#include "Thor\Animations\FrameAnimation.hpp"
// Project Includes
#include "App.h"
#include "Window.h"

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
		virtual void update() = 0;
		virtual void draw(Window & window, float const & deltaTime) = 0;

	protected:
		/// <summary>
		/// @brief Store read-only reference to update delta time.
		/// 
		/// 
		/// </summary>
		static float const & s_DELTA_TIME;
	};

}
#endif // !AI_BASE_H