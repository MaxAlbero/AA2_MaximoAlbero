#pragma once
#include "EnemyWave.h"
#include "BubblesWave.h"
#include "KillerWhaleWave.h"
#include "HMedusaWave.h"
#include "CirclerWave.h"
#include "VMedusaWave.h"
#include "BeholderWave.h"
#include "ChomperWave.h"
#include "BossWave.h"
#include "Player.h"

class WaveFactory {
public:
    static EnemyWave* CreateWave(int enemyId, int amount, Player* playerRef = nullptr) {
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

        case 99: // Boss (puedes usar un ID especial)
            return new BossWave();

        default:
            std::cout << "Unknown enemy ID: " << enemyId << std::endl;
            return nullptr;
        }
    }
};