#include "util\JsonLoader.h"

js::json util::loadJsonFromFile(std::string const & filePath)
{
	std::ifstream rawFile(filePath);
	js::json jsonFile;
	rawFile >> jsonFile;
	return jsonFile;
}
