#include "Provider.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>

Provider::Provider() : ingredientsAvailable(false), ingredientOnTable(-1) {
}

void Provider::placeIngredients() {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(1, 3);

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int chosenIngredient = distr(eng);

        {
            std::lock_guard<std::mutex> lock(mtx);
            ingredientOnTable = chosenIngredient;
            ingredientsAvailable = true;
            std::cout << "Proveedor coloca dos ingredientes en la mesa, falta el ingrediente: " << chosenIngredient << std::endl;
        }

        cv.notify_all();

        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !ingredientsAvailable; });
        }
    }
}

void Provider::notifyFinishedSmoking() {
    std::lock_guard<std::mutex> lock(mtx);
    ingredientsAvailable = false;
    ingredientOnTable = -1;
    cv.notify_all();
}

std::mutex& Provider::getMtx() {
    return mtx;
}

std::condition_variable& Provider::getCv() {
    return cv;
}

bool Provider::getIngredientsAvailable() const {
    return ingredientsAvailable;
}

int Provider::getIngredientOnTable() const {
    return ingredientOnTable;
}
