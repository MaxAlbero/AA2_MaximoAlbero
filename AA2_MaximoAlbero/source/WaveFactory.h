#pragma once
#include "EnemyWave.h"
#include "BubblesWave.h"
#include "KillerWhaleWave.h"
#include "HMedusaWave.h"
#include "CirclerWave.h"
#include "VMedusaWave.h"
#include "BeholderWave.h"
#include "ChomperWave.h"
#include "AmoebaWave.h"
#include "BioTitanWave.h"
#include "SpaceBossWave.h"
#include "Player.h"
#include <iostream>

class WaveFactory {
public:
    static EnemyWave* CreateWave(int enemyId, int amount, Player* playerRef = nullptr, int levelNumber = 1) {
        switch (enemyId) {
        case 0: // Bubbles
            return new BubblesWave(amount);

        case 1: // KillerWhale
            return new KillerWhaleWave(amount);

        case 2: // HMedusa
            return new HMedusaWave(amount);

        case 3: // Circler
            return new CirclerWave(); // No usa amount

        case 4: // VMedusa
            return new VMedusaWave(amount);

        case 5: // Beholder
            return new BeholderWave(amount, playerRef);

        case 6: // Chomper
            return new ChomperWave(amount);

        case 7: // Amoeba
            return new AmoebaWave(amount);

        case 99: // Boss (depende del nivel)
            if (levelNumber == 1) {
                return new BioTitanWave();
            }
            else if (levelNumber == 2) {
                return new SpaceBossWave();
            }
            else {
                std::cout << "Unknown boss for level: " << levelNumber << std::endl;
                return nullptr;
            }

        default:
            std::cout << "Unknown enemy ID: " << enemyId << std::endl;
            return nullptr;
        }
    }
};