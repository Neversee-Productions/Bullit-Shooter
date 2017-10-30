#ifndef APPLICATION_H
#define APPLICATION_H

#include "SFML\System\Clock.hpp"
#include "SFML\System\Time.hpp"

/// <summary>
/// @brief Main Application Starter.
/// @author Rafael Plugge
/// 
/// Boots up application, setups main controller and window.
/// </summary>
class Application
{
public:
	Application();
	~Application();
	void run();

};


#endif // !APPLICATION_H