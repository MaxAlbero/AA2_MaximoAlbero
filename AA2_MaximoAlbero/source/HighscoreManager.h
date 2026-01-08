#pragma once
#include <string>
#include <map>

#define HSM HighscoreManager::GetInstance()

class HighscoreManager {
public:
	static HighscoreManager* GetInstance() {
		static HighscoreManager instance;
		return &instance;
	}

	void LoadScores(std::string path);
	void SaveScores(std::string path);
	void AddScore(int value, std::string name);
	std::map<int, std::string> GetScores();

	std::pair<int, std::string> scores[3][10];

private:
	HighscoreManager() = default;
	HighscoreManager(HighscoreManager&) = delete;
	HighscoreManager& operator=(const HighscoreManager&) = delete;
	~HighscoreManager();
};