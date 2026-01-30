#pragma once
#include <string>
#include <vector>
#include <algorithm>

#define HSM ScoreManager::GetInstance()

class ScoreManager {
public:
    static ScoreManager* GetInstance() {
        static ScoreManager instance;
        return &instance;
    }

    // Getters
    int GetCurrentScore() const { return currentScore; }
    int GetHighScore() const { return highScore; }

    const std::vector<int>& GetRankingScores() const { return rankingScores; }
    const std::vector<std::string>& GetRankingNames() const { return rankingNames; }

    // Setters
    void AddPoints(int pointsAdded) {
        currentScore += pointsAdded;
        if (currentScore > highScore) {
            highScore = currentScore;
        }
    }

    void SetHighScore(int newHighScore) {
        highScore = newHighScore;
    }

    // Ranking
    void AddToRanking(int score, const std::string& playerName);
    bool IsInTopTen(int score) const;
    void LoadRankingFromFile(const std::string& filepath);
    void SaveRankingToFile(const std::string& filepath) const;
    void ResetCurrentScore() { currentScore = 0; }

private:
    ScoreManager() : highScore(0), currentScore(0) {
        rankingScores.reserve(10);
        rankingNames.reserve(10);
        LoadRankingFromFile("resources/ranking.xml");
    }

    ScoreManager(ScoreManager&) = delete;
    ScoreManager& operator=(const ScoreManager&) = delete;
    ~ScoreManager() = default;

    int highScore;
    int currentScore;

    std::vector<int> rankingScores;      // Top 10 scores ordenados de mayor a menor
    std::vector<std::string> rankingNames; // Nombres asociados a cada score

    void SortRanking();  // Ordena el ranking de mayor a menor
};