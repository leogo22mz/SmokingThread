#include <QCoreApplication>
//#include <iostream>
#include <thread>
#include "Provider.h"
#include "Smoker.h"

int main() {
    Provider provider;
    Smoker smoker1(1, provider), smoker2(2, provider), smoker3(3, provider);

    std::thread providerThread(&Provider::placeIngredients, &provider);
    std::thread smoker1Thread(&Smoker::waitForIngredientsAndSmoke, &smoker1);
    std::thread smoker2Thread(&Smoker::waitForIngredientsAndSmoke, &smoker2);
    std::thread smoker3Thread(&Smoker::waitForIngredientsAndSmoke, &smoker3);

    providerThread.join();
    smoker1Thread.join();
    smoker2Thread.join();
    smoker3Thread.join();

    return 0;
}
