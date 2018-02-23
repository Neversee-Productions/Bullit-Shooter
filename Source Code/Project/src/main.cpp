#include "main.hpp"

/// <summary>
/// @mainpage Bullit " " Shooter
/// 
/// ## Space shoot'em up
/// 
/// ### 2018 Games Fleadh
/// 
/// ## Meet the team
/// 
/// * [Rafael Plugge](https://www.linkedin.com/in/rafael-plugge-512164106/)
/// * [Sebastian Kruzel](https://www.linkedin.com/in/sebastiankruzel/)
/// 
/// ## Required software
/// 
/// * [Visual C++ Redistributable 2017](https://go.microsoft.com/fwlink/?LinkId=746571)
/// 
/// *All external dependencies included in the project, under 'redist' folder*
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
	// generate seed using time since epoch.
	std::srand(static_cast<unsigned int>(time(nullptr)));
	
	Application& app = Application();
	app.run();
}