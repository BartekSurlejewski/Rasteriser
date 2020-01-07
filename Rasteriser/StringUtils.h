#pragma once
#include <string>
#include <vector>

class StringUtils {
public:
	static std::vector<std::string> split(const std::string &string, char delimiter, bool removeEmpty);

private:
	StringUtils() = default;
};
