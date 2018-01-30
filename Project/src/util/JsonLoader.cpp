#include "util\JsonLoader.h"

json::json util::loadJsonFromFile(std::string const & filePath)
{
	std::ifstream rawFile(filePath);
	json::json jsonFile;
	rawFile >> jsonFile;
	return jsonFile;
}
