#include "ScoreManager.h"
#include "../dependencies/inc/rapidXML/rapidxml.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace rapidxml;

void ScoreManager::SortRanking() {
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

void ScoreManager::SaveRankingToFile(const std::string& filepath) const {
    try {
        std::ofstream file(filepath);
        if (!file.is_open()) {
            std::cout << "Error: Could not save ranking to " << filepath << std::endl;
            return;
        }

        // Escribir XML manualmente (más simple y sin conflictos)
        file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
        file << "<ranking>\n";

        for (size_t i = 0; i < rankingScores.size(); i++) {
            file << "  <score position=\"" << (i + 1) << "\">\n";
            file << "    <value>" << rankingScores[i] << "</value>\n";
            file << "    <playerName>" << rankingNames[i] << "</playerName>\n";
            file << "  </score>\n";
        }

        file << "</ranking>\n";
        file.close();

        std::cout << "Ranking saved to " << filepath << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error saving ranking: " << e.what() << std::endl;
    }
}

void ScoreManager::LoadRankingFromFile(const std::string& filepath) {
    try {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cout << "No ranking file found. Starting with empty ranking." << std::endl;
            return;
        }

        // Leer archivo completo
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        std::string xmlContent = buffer.str();
        std::vector<char> xml_copy(xmlContent.begin(), xmlContent.end());
        xml_copy.push_back('\0');

        // Parsear XML
        xml_document<char> doc;
        doc.parse<0>(&xml_copy[0]);

        rankingScores.clear();
        rankingNames.clear();

        // Obtener nodo raíz
        xml_node<char>* rootNode = doc.first_node("ranking");
        if (!rootNode) {
            std::cout << "Error: No ranking node found in XML" << std::endl;
            return;
        }

        // Iterar sobre los scores
        for (xml_node<char>* scoreNode = rootNode->first_node("score");
            scoreNode;
            scoreNode = scoreNode->next_sibling("score")) {

            // Leer score
            xml_node<char>* scoreValue = scoreNode->first_node("value");
            xml_node<char>* playerName = scoreNode->first_node("playerName");

            if (scoreValue && playerName && scoreValue->value() && playerName->value()) {
                try {
                    int score = std::stoi(scoreValue->value());
                    std::string name = playerName->value();

                    rankingScores.push_back(score);
                    rankingNames.push_back(name);
                }
                catch (const std::exception& e) {
                    std::cout << "Error parsing score entry: " << e.what() << std::endl;
                }
            }
        }

        std::cout << "Ranking loaded from " << filepath
            << " (" << rankingScores.size() << " entries)" << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Error loading ranking: " << e.what() << std::endl;
    }
}