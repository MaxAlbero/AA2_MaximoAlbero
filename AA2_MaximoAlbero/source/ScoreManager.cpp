#include "ScoreManager.h"
#include "../dependencies/inc/rapidXML/rapidxml.hpp"
#include "../dependencies/inc/rapidXML/rapidxml_iterators.hpp"
#include "../dependencies/inc/rapidXML/rapidxml_utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

void ScoreManager::AddToRanking(int score, const std::string& playerName) {
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

bool ScoreManager::IsInTopTen(int score) const {
    if (rankingScores.size() < 10) {
        return true;
    }
    return score > rankingScores.back();
}

void ScoreManager::SaveScore(const std::string& playerName) {
    AddToRanking(currentScore, playerName);
    SaveRankingToFile("resources/ranking.xml");
    ResetCurrentScore();
}

void ScoreManager::SortRanking() {
    // Crear vector temporal con pares (score, nombre)
    std::vector<std::pair<int, std::string>> temp;
    for (size_t i = 0; i < rankingScores.size(); i++) {
        temp.push_back({ rankingScores[i], rankingNames[i] });
    }

    // Ordenar de mayor a menor
    std::sort(temp.begin(), temp.end(),
        [](const auto& a, const auto& b) {
            return a.first > b.first;
        });

    // Limpiar y repoblar los vectores originales
    rankingScores.clear();
    rankingNames.clear();
    for (const auto& pair : temp) {
        rankingScores.push_back(pair.first);
        rankingNames.push_back(pair.second);
    }
}

void ScoreManager::LoadRankingFromFile(const std::string& filepath) {
    try {
        rapidxml::file<> xmlFile(filepath.c_str());
        rapidxml::xml_document<> doc;
        doc.parse<0>(xmlFile.data());

        rapidxml::xml_node<>* rankingNode = doc.first_node("ranking");
        if (!rankingNode) {
            std::cout << "No ranking node found in XML file" << std::endl;
            return;
        }

        rankingScores.clear();
        rankingNames.clear();

        for (rapidxml::xml_node<>* scoreNode = rankingNode->first_node("score");
            scoreNode != nullptr;
            scoreNode = scoreNode->next_sibling("score")) {

            rapidxml::xml_node<>* pointsNode = scoreNode->first_node("points");
            rapidxml::xml_node<>* nameNode = scoreNode->first_node("name");

            if (pointsNode && pointsNode->value() && nameNode && nameNode->value()) {
                int points = std::stoi(pointsNode->value());
                std::string name = nameNode->value();

                rankingScores.push_back(points);
                rankingNames.push_back(name);
            }
        }

        std::cout << "Ranking loaded from file: " << rankingScores.size() << " entries" << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Error loading ranking from file: " << e.what() << std::endl;
    }
}

void ScoreManager::SaveRankingToFile(const std::string& filepath) const {
    try {
        std::ofstream file(filepath);

        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file << "<ranking>\n";

        // Escribir cada puntuación
        for (size_t i = 0; i < rankingScores.size(); i++) {
            file << "\t<score>\n";
            file << "\t\t<points>" << rankingScores[i] << "</points>\n";
            file << "\t\t<name>" << rankingNames[i] << "</name>\n";
            file << "\t</score>\n";
        }

        file << "</ranking>\n";
        file.close();

        std::cout << "Ranking saved to file: " << filepath << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Error saving ranking to file: " << e.what() << std::endl;
    }
}