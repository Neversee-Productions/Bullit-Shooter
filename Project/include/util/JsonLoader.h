#ifndef JSON_LOADER_H
#define JSON_LOADER_H

// STL Includes
#include <fstream>
// Json Includes
#include "json\json.hpp"

/// 
/// @author Rafael Plugge
/// @brief Used to store utility and helper functions.
/// 
/// 
/// 
namespace util
{
	/// <summary>
	/// @brief Loads up json from file.
	/// 
	/// Loads up the raw text file than
	/// parses it into the json object.
	/// </summary>
	/// <param name="filePath">string to the json file.</param>
	/// <returns>json object ready to be parsed.</returns>
	js::json loadJsonFromFile(std::string const & filePath);
}

#endif // !JSON_LOADER_H