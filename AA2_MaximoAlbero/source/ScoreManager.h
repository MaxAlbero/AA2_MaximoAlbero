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
    void AddToRanking(int score, const std::string& playerName) {
        if (rankingScores.size() < 10) {
            rankingScores.push_back(score);
            rankingNames.push_back(playerName);
            SortRanking();
            return;
        }

        if (score > rankingScores.back()) {
            rankingScores.pop_back();
            rankingNames.pop_back();

            rankingScores.push_back(score);
            rankingNames.push_back(playerName);
            SortRanking();
        }
    }

    void SaveScore(const std::string& playerName) {
        AddToRanking(currentScore, playerName);
        SaveRankingToFile("resources/ranking.xml");
        ResetCurrentScore();
    }

    bool IsInTopTen(int score) const {
        if (rankingScores.size() < 10) {
            return true;
        }
        return score > rankingScores.back();
    }

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

    std::vector<int> rankingScores;
    std::vector<std::string> rankingNames;

    void SortRanking() {
        std::vector<std::pair<int, std::string>> temp;
        for (size_t i = 0; i < rankingScores.size(); i++) {
            temp.push_back({ rankingScores[i], rankingNames[i] });
        }

        std::sort(temp.begin(), temp.end(),
            [](const auto& a, const auto& b) {
                return a.first > b.first;
            });

        rankingScores.clear();
        rankingNames.clear();
        for (const auto& pair : temp) {
            rankingScores.push_back(pair.first);
            rankingNames.push_back(pair.second);
        }
    }
};