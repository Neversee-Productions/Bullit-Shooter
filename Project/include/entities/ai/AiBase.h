#ifndef AI_BASE_H
#define AI_BASE_H

// STL Includes
#include <list>
// SFML Includes
// Thor Includes
#include "Thor\Input.hpp" // For thor::ActionMap<>
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
			// Empty for now.
		};


	public:
		AiBase() = default;
		~AiBase() = default;
		virtual void init(std::shared_ptr<Resources> sptrResources) = 0;
		virtual void update(float const & deltaTime) = 0;
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