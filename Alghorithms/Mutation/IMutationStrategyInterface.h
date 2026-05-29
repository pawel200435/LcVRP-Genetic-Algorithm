#ifndef PROJEKT_LCVRP_IMUTATIONSTRATEGYINTERFACE_H
#define PROJEKT_LCVRP_IMUTATIONSTRATEGYINTERFACE_H
#include <vector>

class IMutationStrategyInterface {
public:
    virtual ~IMutationStrategyInterface() = default;
    virtual void vMutate(std::vector<int>& vGenotype, double dMutationProb, int iNumGroups) = 0;
};


#endif //PROJEKT_LCVRP_IMUTATIONSTRATEGYINTERFACE_H