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
#endif
#pragma comment(lib,"_doxygen.lib")
#pragma comment(lib,"doxycfg.lib")
#pragma comment(lib,"md5.lib")
#pragma comment(lib,"qtools.lib")
#pragma comment(lib,"vhdlparser.lib")

#include "SFML\Graphics.hpp"
#include "Thor\Graphics.hpp"
#include "json\json.hpp"
#include "tinyheaders\tinyc2.h"

/// <summary>
/// Main entry point for the application
/// </summary>
/// <param name="argc">number of arguments passed into the application</param>
/// <param name="argv">c style string of the arguments passed into the application</param>
int main(int argc, char** argv)
{
	sf::RenderWindow window;
	thor::BigSprite bigSprite;
	nlohmann::json json_ex;
	c2Circle circle;
}