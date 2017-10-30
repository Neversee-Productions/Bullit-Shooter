#ifndef APPLICATION_H
#define APPLICATION_H

#include "SFML\System\Clock.hpp"
#include "SFML\System\Time.hpp"

/// 
/// @brief Main application starter.
/// @author Rafael Plugge
/// 
/// Boots up application, setups main controller and window.
/// 
class Application
{
public:
	Application();
	~Application();
	void run();

private:

};


#endif // !APPLICATION_H