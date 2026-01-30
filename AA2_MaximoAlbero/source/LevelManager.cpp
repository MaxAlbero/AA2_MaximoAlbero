#include "LevelManager.h"

LevelManager* LevelManager::_instance = nullptr;

LevelManager::LevelManager() {
    InitializeLevels();
}

LevelManager* LevelManager::GetInstance() {
    if (_instance == nullptr) {
        _instance = new LevelManager();
    }
    return _instance;
}

void LevelManager::InitializeLevels() {
    _levels.clear();

    // Nivel 1
    _levels.push_back({
        "level_1",
        "SEA OF KARNAUGH",
        "resources/level_1.xml",
        1
        });

    // Nivel 2
    _levels.push_back({
        "level_2",
        "CIRCUITS OF BOOLE",
        "resources/level_2.xml",
        2
        });

}