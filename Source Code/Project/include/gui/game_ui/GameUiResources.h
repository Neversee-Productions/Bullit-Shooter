#ifndef GAME_UI_RESOURCES_H
#define GAME_UI_RESOURCES_H

// STD Includes
#include <memory>
// SFML Includes
#include "SFML\Graphics.hpp"
// Project Includes

/// 
/// @brief Defines the namespace for GameUI's resources.
/// @author Rafael Plugge
/// 
namespace gameUi
{

	/// 
	/// @brief Defines the game ui resources.
	/// @author Sebastian Kruzel
	/// 
	/// 
	/// 
	struct Resources
	{
		std::shared_ptr<sf::Texture> m_sptrHealthTemplateTexture = nullptr;
		std::shared_ptr<sf::Texture> m_sptrHealthTexture = nullptr;
		/// <summary>
		/// @brief shared pointer to font.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Font> m_sptrButtonFont = nullptr;
		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrButtonTexture = nullptr;
		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrRechargeBarTexture = nullptr;
		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrRechargeBarFrameTexture = nullptr;
		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrBorderTexture = nullptr;
		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrOverchargeFrameTexture = nullptr;
	};
}

#endif // !GAME_UI_RESOURCES_H