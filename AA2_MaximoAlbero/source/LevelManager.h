#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct Level {
    std::string id;
    std::string name;
    std::string xmlPath;
    int levelNumber;
};

class LevelManager {
private:
    static LevelManager* _instance;
    std::vector<Level> _levels;
    int _currentLevelIndex = 0;

    LevelManager();

public:
    static LevelManager* GetInstance();

    void InitializeLevels();
    const std::vector<Level>& GetLevels() const { return _levels; }
    const Level& GetLevel(int index) const { return _levels[index]; }
    int GetLevelCount() const { return _levels.size(); }
    int GetCurrentLevelIndex() const { return _currentLevelIndex; }
    void SetCurrentLevel(int index) { _currentLevelIndex = index; }
};

#define LM LevelManager::GetInstance()