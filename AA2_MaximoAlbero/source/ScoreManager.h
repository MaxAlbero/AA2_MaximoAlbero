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
    void SaveScore(const std::string& playerName);
    void ResetCurrentScore() { currentScore = 0; }
    int GetTopRankingScore() const {
        return rankingScores.empty() ? 0 : rankingScores[0];
    }

private:
    ScoreManager() : highScore(0), currentScore(0) {
        rankingScores.reserve(10);
        rankingNames.reserve(10);
        LoadRankingFromFile("resources/ranking.xml");
    }

    ScoreManager(const ScoreManager&) = delete;
    ScoreManager& operator=(const ScoreManager&) = delete;
    ~ScoreManager() = default;

    int highScore;
    int currentScore;

    std::vector<int> rankingScores; 
    std::vector<std::string> rankingNames;

    void SortRanking();
};