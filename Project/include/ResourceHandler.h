#ifndef RESOURCEHANDLER_H
#define RESOURCEHANDLER_H

// For mutual exclusion
// We use mutex over atomic since
// unique_ptr is a non-copyable type.
#include <mutex>
// For std::pair
#include <set>
// For shared_ptr
#include <memory>
// For std::unordered_map
#include <unordered_map>
// For std::string
#include <string>
// For std::ifstream
#include <fstream>
// Resources we load
#include "SFML\Graphics\Shader.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Font.hpp"
#include "SFML\Audio\SoundBuffer.hpp"
#include "Thor\Graphics\BigTexture.hpp"
#include "Thor\Animations\FrameAnimation.hpp"
// thor resource handler
#include "Thor\Resources\ResourceHolder.hpp"
#include "Thor\Resources\ResourceLoader.hpp"
#include "Thor\Resources.hpp"
// json parser
#include "json\json.hpp"

/// 
/// @brief Will handle loading of all resources.
/// @author Rafael Plugge
/// @version 0.1
/// 
/// Only one instance of this class exist, as in it uses
/// the Single-ton pattern.
/// 
class ResourceHandler
{
public:
	static ResourceHandler & get();

	/// <summary>
	/// @brief Template loader.
	/// 
	/// Loads up our data using the appropriate resource holder based on one of the acceptable types.
	/// This function is exception safe, as in it returns a nullptr if a exception is given.
	/// 
	/// @warning The only acceptable types are: sf::Texture, sf::Font, sf::SoundBuffer, thor::BigTexture and thor::FrameAnimation.
	/// </summary>
	/// <typeparam name="data_type">Defines the type of data we will load.</typeparam>
	/// <param name="jsonParser">Defines the json parser that contains our id's file path.</param>
	/// <param name="id">Defines the key we use to identify our dat in our resource holder.</param>
	/// <returns>Returns std::shared_ptr to our loaded resource.</returns>
	template<typename data_type>
	std::shared_ptr<data_type> loadUp(json::json & jsonParser, const std::string & id);

private:
	ResourceHandler();

	/// <summary>
	/// @brief Template loader.
	/// 
	/// Loads up our data using the appropriate resource holder based on one of the acceptable types:
	/// (thor::FrameAnimation)
	/// </summary>
	/// <typeparam name="data_type">Defines the type of our data.</typeparam>
	/// <param name="jsonParser">Defines the the json parser that contains our id's information.</param>
	/// <param name="id">Defines the key we use to identify our data in our resource holder.</param>
	/// <returns>Reference to our loaded data.</returns>
	template<typename data_type>
	data_type & load(json::json & jsonParser, const std::string & id);

	/// <summary>
	/// @brief Loads a particular resource.
	/// 
	/// Defined as forward declaration of explicit template instatiation.
	/// Loads all the frames for a id's animation into ResourceHandler::m_pairAnimationHolder.
	/// @see ResourceHandler::load
	/// </summary>
	/// <param name="jsonParser">defines the json file that our resource holder uses.</param>
	/// <param name="id">defines its id in our resource holder.</param>
	/// <returns>Reference to our loaded resource.</returns>
	template<> thor::FrameAnimation & load<thor::FrameAnimation>(json::json & jsonParser, const std::string & id);

	/// <summary>
	/// @brief Loads a particular resource.
	/// 
	/// Defined as forward declaration of explicit template instatiation.
	/// Loads all the frames for a id's animation into
	/// </summary>
	/// <param name="jsonParser">defines the json file that our resource holder uses.</param>
	/// <param name="id">defines its id in our resource holder.</param>
	/// <returns>Reference to our loaded resource.</returns>
	template<> std::vector<sf::IntRect> & load<std::vector<sf::IntRect>>(json::json & jsonParser, const std::string & id);

	/// <summary>
	/// @brief Loads a particular resource.
	/// 
	/// Defined as forward declaration of explicit template instatiation.
	/// Loads both fragment and vertex shader into the a sfml shader and stores it.
	/// </summary>
	/// <param name="jsonParser">defines the json file that our resource holder uses.</param>
	/// <param name="id">defines its id in our resource holder.</param>
	/// <returns>Reference to our loaded resource.</returns>
	template<> std::shared_ptr<sf::Shader>& load<std::shared_ptr<sf::Shader>>(json::json & jsonParser, const std::string & id);

	/// <summary>
	/// @brief Template loader.
	/// 
	/// Loads up our data using the appropriate resource holder based on one of the acceptable type:
	/// (sf::Texture, sf::Font, sf::SoundBuffer and thor::BigTexture)
	/// </summary>
	/// <typeparam name="data_type">Defines the type of our data.</typeparam>
	/// <param name="id">Defines the key we use to to identify our data in our resource holder.</param>
	/// <param name="filePath">Defines the path that our resource holder uses to load the data.</param>
	/// <returns>Reference to our loaded data.</returns>
	template<typename data_type>
	data_type & load(const std::string & id, const std::string & filePath);

	/// <summary>
	/// @brief Loads a particular resource.
	/// 
	/// Defined as forward declaration of explicit template instatiation.
	/// Loads a texture into ResourceHandler::m_pairTextureHolder.
	/// @see ResourceHandler::load
	/// </summary>
	/// <param name="id">defines its id in our resource holder.</param>
	/// <param name="filePath">defines the file path our resource holder uses to load it</param>
	/// <returns>Reference to our loaded resource.</returns>
	template<> sf::Texture & load<sf::Texture>(const std::string & id, const std::string & filePath);

	/// <summary>
	/// @brief Loads a particular resource.
	/// 
	/// Defined as forward declaration of explicit template instatiation.
	/// Loads a font into ResourceHandler::m_pairFontHolder.
	/// @see ResourceHandler::load
	/// </summary>
	/// <param name="id">defines its id in our resource holder.</param>
	/// <param name="filePath">defines the file path our resource holder uses to load it</param>
	/// <returns>Reference to our loaded resource.</returns>
	template<> sf::Font & load<sf::Font>(const std::string & id, const std::string & filePath);

	/// <summary>
	/// @brief Loads a particular resource.
	/// 
	/// Defined as forward declaration of explicit template instatiation.
	/// Loads a sound buffer into ResourceHandler::m_pairSoundHolder.
	/// @see ResourceHandler::load
	/// </summary>
	/// <param name="id">defines its id in our resource holder.</param>
	/// <param name="filePath">defines the file path our resource holder uses to load it</param>
	/// <returns>Reference to our loaded resource.</returns>
	template<> sf::SoundBuffer & load<sf::SoundBuffer>(const std::string & id, const std::string & filePath);


	/// <summary>
	/// @brief Loads a particular resource.
	/// 
	/// Defined as forward declaration of explicit template instatiation.
	/// Loads a big texture into ResourceHandler::m_pairBigTextureHolder.
	/// @see ResourceHandler::load
	/// </summary>
	/// <param name="id">defines its id in our resource holder.</param>
	/// <param name="filePath">defines the file path our resource holder uses to load it</param>
	/// <returns>Reference to our loaded resource.</returns>
	template<> thor::BigTexture & load<thor::BigTexture>(const std::string & id, const std::string & filePath);

	/// <summary>
	/// @brief Defines a alias for our thor::ResourceHolder.
	/// 
	/// This resource holder manages the access of sf::texture through std::string keys and
	/// follows thor's Central Ownership model.
	/// </summary>
	typedef thor::ResourceHolder<sf::Texture, std::string, thor::Resources::CentralOwner> TextureHolder;

	/// <summary>
	/// @brief Defines a alias for our thor::ResourceHolder.
	/// 
	/// This resource holder manages the access of big textures through string keys and
	/// follows thor's Central Ownership model.
	/// </summary>
	typedef thor::ResourceHolder<thor::BigTexture, std::string, thor::Resources::CentralOwner> BigTextureHolder;

	/// <summary>
	/// @brief Defines a alias for our thor::ResourceHolder.
	/// 
	/// This resource holder manages the access of fonts through string keys and
	/// follows thor's Central Ownership model.
	/// </summary>
	typedef thor::ResourceHolder<sf::Font, std::string, thor::Resources::CentralOwner> FontHolder;

	/// <summary>
	/// @brief Defines a alias for our thor::ResourceHolder.
	/// 
	/// This resource holder manages the access of sound buffers through string keys and
	/// follows thor's Central Ownership model.
	/// </summary>
	typedef thor::ResourceHolder<sf::SoundBuffer, std::string, thor::Resources::CentralOwner> SoundHolder;

	/// <summary>
	/// @brief Defines a alias for our thor::FrameAnimation.
	/// 
	/// This resource holder contains each frame of a particular frame animation.
	/// </summary>
	typedef std::unordered_map<std::string, thor::FrameAnimation> ThorFrameHolder;

	/// <summary>
	/// @brief Defines a alias for our map of vector of rectangles.
	/// 
	/// This resource holder contains each frame of a particular animation.
	/// </summary>
	typedef std::unordered_map<std::string, std::vector<sf::IntRect>> FrameHolder;

	/// <summary>
	/// @brief Defines a alias for our map of shaders.
	/// 
	/// This resource holder contains a shared pointer to a shader followed by its id.
	/// </summary>
	typedef std::unordered_map<std::string, std::shared_ptr<sf::Shader>> ShaderHolder;

	/// 
	/// @author Rafael Plugge
	/// @brief Defines a holder with its own mutex.
	/// 
	/// Contains a unique pointer to a holder and its corresponding mutex.
	/// @tparam holder_type Defines the type of the holder.
	/// 
	template<typename holder_type>
	struct MutexHolderPair
	{
		/// <summary>
		/// @brief Defines the mutex associated to the holder.
		/// 
		/// 
		/// </summary>
		std::mutex m_mutex; 
		/// <summary>
		/// @brief Defines a unique pointer to holder.
		/// 
		/// 
		/// </summary>
		std::unique_ptr<holder_type> m_holder = std::make_unique<holder_type>();
	};

	/// <summary>
	/// @brief Our Pair with its mutex and a unique pointer to our ResourceHandler::TextureHolder.
	/// 
	/// 
	/// </summary>
	MutexHolderPair<TextureHolder> m_pairTextureHolder;

	/// <summary>
	/// @brief Our Pair with its mutex and a unique pointer to our ResourceHandler::BigTextureHolder.
	/// 
	/// 
	/// </summary>
	MutexHolderPair<BigTextureHolder> m_pairBigTextureHolder;

	/// <summary>
	/// @brief Our Pair with its mutex and a unique pointer to our ResourceHandler::FontHolder.
	/// 
	/// 
	/// </summary>
	MutexHolderPair<FontHolder> m_pairFontHolder;

	/// <summary>
	/// @brief Our Pair with its mutex and a unique pointer to our ResourceHandler::SoundHolder.
	/// 
	/// 
	/// </summary>
	MutexHolderPair<SoundHolder> m_pairSoundHolder;

	/// <summary>
	/// @brief Our Pair with its mutex and a unique pointer to our ResourceHandler::AnimationHolder.
	/// 
	/// 
	/// </summary>
	MutexHolderPair<ThorFrameHolder> m_pairAnimationHolder;

	/// <summary>
	/// @brief Our Pair with its mutex and a unique pointer to our ResourceHandler::FrameHolder.
	/// 
	/// 
	/// </summary>
	MutexHolderPair<FrameHolder> m_pairFrameHolder;

	/// <summary>
	/// @brief Our Pair with its mutex and a unique pointer to our ResourceHandler::ShaderHolder.
	/// 
	/// 
	/// </summary>
	MutexHolderPair<ShaderHolder> m_pairShaderHolder;

	/// <summary>
	/// @brief Our predefined Id Strategy.
	/// 
	/// Thor uses our Id strategy to determine how it loads our resources.
	/// </summary>
	const thor::Resources::KnownIdStrategy m_ID_STRATEGY;

	/// <summary>
	/// @brief Contains our single instance of ResourceHandler.
	/// 
	/// 
	/// </summary>
	static ResourceHandler s_instance;
};

#endif // !RESOURCEHANDLER_H