#ifndef PICKUP_H
#define PICKUP_H

#include <string>
#include <memory>
#include "SFML\Graphics.hpp"

class Pickup
{

public:
	/// <summary>
	/// @author Sebastian Kruzel
	/// @brief Define resources for the pickup
	/// 
	/// 
	/// </summary>
	struct Resources
	{
		struct IndividualPickup
		{
			std::string m_id = "";
			std::shared_ptr<sf::Texture> m_texture;
			sf::Vector2f m_size;
		};

		std::vector<IndividualPickup> m_pickups;
	};

private:
	std::shared_ptr<sf::Texture> m_texture;

};

#endif // !PICKUP_H