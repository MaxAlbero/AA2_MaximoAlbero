#pragma once
#include <string>
#include <map>

#define HSM ScoreManager::GetInstance()

class ScoreManager {
public:
	static ScoreManager* GetInstance() {
		static ScoreManager instance;
		return &instance;
	}

	void LoadScores(std::string path);
	void SaveScores(std::string path);
	void AddScore(int value, std::string name);
	std::map<int, std::string> GetScores();

	std::pair<int, std::string> scores[3][10];

	

	//PSEUDOCODE: EL ScoreManager acumula 1000 puntos a la puntuación actual del jugador al obtener el powerUp de 1000 puntos.
	void AddPoints(int pointsAdded) {
		currentScore += pointsAdded;

		if (currentScore > highScore) {
			highScore = currentScore;
		}
	}

	int GetCurrentScore() const { return currentScore; }
	int GetHighScore() const { return highScore; }

	void SetHighScore(int newHighScore) {
		highScore = newHighScore;
	}

private:
	ScoreManager() = default;
	ScoreManager(ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;

	int highScore; //Ahora mismo no tiene uso, pero esta variable es la que tiene que marcar la puntuación más alta obtenida, en una unica partida funciona, 
	//pero falta la logica de guardado de puntuaciones en un archivo binario
	int currentScore = 0; //TODO: VER SI HAY UNA FORMA MAS ELEGANTE DE HACER ESTO
};