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
#include "AngrygonsWave.h"
#include "AnnoyerWave.h"
#include "MissileWave.h"
#include "NukeWave.h"
#include "DanielsWave.h"
#include "TorpedoWave.h"
#include "TurboChainsawWave.h"
#include "UfoWave.h"
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

        case 10:
            return new BioTitanWave();

        case 11: // Angrygons
            return new AngrygonsWave(amount);

        case 12: // Annoyer
            return new AnnoyerWave(amount, playerRef);

        case 13: // Missile
            return new MissileWave(amount);

        case 14: // Nuke
            return new NukeWave(amount);

        case 15: // Torpedo
            return new TorpedoWave(amount);

        case 16: // TurboChainsaw
            return new TurboChainsawWave();

        case 17: // Ufo
            return new UfoWave(amount);

        case 18:
            return new DanielsWave(amount);

        case 20:
            return new SpaceBossWave();
        default:
            std::cout << "Unknown enemy ID: " << enemyId << std::endl;
            return nullptr;
        }
    }
};