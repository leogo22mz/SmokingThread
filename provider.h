#ifndef PROVIDER_H
#define PROVIDER_H

#include <mutex>
#include <condition_variable>

class Provider {
public:
    Provider();
    void placeIngredients();
    void notifyFinishedSmoking();

    // Métodos para acceder a las variables de condición y estado
    std::mutex& getMtx();
    std::condition_variable& getCv();
    bool getIngredientsAvailable() const;
    int getIngredientOnTable() const;

private:
    std::mutex mtx;
    std::condition_variable cv;
    bool ingredientsAvailable;
    int ingredientOnTable;
};

#endif // PROVIDER_H
