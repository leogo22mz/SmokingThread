#ifndef SMOKER_H
#define SMOKER_H

#include "Provider.h"

class Smoker {
public:
    Smoker(int id, Provider& provider);
    void waitForIngredientsAndSmoke();

private:
    int smokerID;
    Provider& providerRef;
};

#endif // SMOKER_H
