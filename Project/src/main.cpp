#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#pragma comment(lib,"thor-d.lib")
#else 
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#pragma comment(lib,"thor.lib")
#define NDEBUG
#include <Windows.h>
#endif

#include <time.h>
#include "Application.h"

/// <summary>
/// @mainpage 3rd year Project
/// 
/// ## 2D Side Scroll Space shoot'em up
///
/// ## Meet the team
/// 
/// * [Rafael Plugge](https://www.linkedin.com/in/rafael-plugge-512164106/)
/// * [Sebastian Kruzel](https://www.linkedin.com/in/sebastiankruzel/)
/// 
/// ## Required software
/// 
/// * [Visual C++ Redistributable 2017](https ://go.microsoft.com/fwlink/?LinkId=746571)
/// 
///		*All external dependencies included in the project*
/// 
/// ## 3rd Party Libraries
/// 
/// * [SFML 2.4](https://github.com/SFML/SFML)
/// * [Thor](https://github.com/Bromeon/Thor)
/// * [JSON](https://github.com/nlohmann/json)
/// * [tinyheaders](https://github.com/RandyGaul/tinyheaders)
/// 
/// ## Supervisor
/// 
/// * Philip Bourke
/// 
/// </summary>

/// <summary>
/// @brief Entry point.
/// 
/// The Main Entry point for the application.
/// @file
/// </summary>
/// <param name="argc">number of arguments passed into the application.</param>
/// <param name="argv">c style string of the arguments passed into the application.</param>
int main(int argc, char** argv)
{
	std::srand(static_cast<unsigned int>(time(nullptr))); // generate seed using time since epoch.
#ifdef NDEBUG
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // !NDEBUG
	Application& app = Application();
	app.run();
}