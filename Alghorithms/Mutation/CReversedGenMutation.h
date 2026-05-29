#ifndef PROJEKT_LCVRP_CREVERSEDGENMUTATION_H
#define PROJEKT_LCVRP_CREVERSEDGENMUTATION_H
#include "IMutationStrategyInterface.h"
#include <random>


class CReversedGenMutation : public IMutationStrategyInterface {
public:
    CReversedGenMutation();
    void vMutate(std::vector<int>& vGenotype, double dMutationProb, int iNumGroups) override;

private:
    std::random_device rd;
    std::mt19937 gen;
};


#endif //PROJEKT_LCVRP_CREVERSEDGENMUTATION_H