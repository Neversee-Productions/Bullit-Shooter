#ifndef AI_BASE_H
#define AI_BASE_H

// STL Includes
#include <unordered_map>
// SFML Includes
// Thor Includes
#include "Thor\Input.hpp" // For thor::ActionMap<>
// Project Includes
#include "App.h"
#include "Window.h"

/// 
/// @author Rafael Plugge
/// @brief Base class for all AI.
/// 
/// Describes AI interface.
/// 
/// @tparam ActionTypes Use to define what type of actions the Ai will perform
/// 
template<typename ActionTypes>
class AiBase
{
public:
	AiBase();
	~AiBase() = default;
	virtual void update(float const & deltaTime) = 0;
	virtual void draw(Window & window, float const & deltaTime) = 0;

protected:
	float const & m_DELTA_TIME;
	typedef std::unordered_map<ActionTypes, std::string> ActionMap;
	ActionMap m_actions;
};

template<typename ActionTypes>
AiBase<ActionTypes>::AiBase()
	: m_actions()
	, m_DELTA_TIME(App::getUpdateDeltaTime())
{
}

#endif // !AI_BASE_H