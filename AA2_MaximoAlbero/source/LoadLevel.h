#pragma once
#include <string>
#include <vector>

class LoadLevel {
public:
	bool LoadFile(std::string& path, std::vector<int>& wave, std::vector<int>& amount);
};