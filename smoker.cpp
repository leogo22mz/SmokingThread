#include "Smoker.h"
#include <iostream>
#include <thread>
#include <mutex>
std::mutex coutMutex;

Smoker::Smoker(int id, Provider& provider) : smokerID(id), providerRef(provider) {
}

void Smoker::waitForIngredientsAndSmoke() {
    while(true) {
        {
            std::unique_lock<std::mutex> lock(providerRef.getMtx());
            providerRef.getCv().wait(lock, [this] {
                // Reaccionar solo si este fumador tiene el ingrediente faltante
                return providerRef.getIngredientsAvailable() && providerRef.getIngredientOnTable() == smokerID;
            });

            std::lock_guard<std::mutex> guard(coutMutex);
            std::cout << "Fumador " << smokerID << " ha conseguido los ingredientes, se lo enrola y fuma." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3)); // Simular fumar

        providerRef.notifyFinishedSmoking();
    }
}
