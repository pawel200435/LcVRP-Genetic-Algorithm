#ifndef PROJEKT_LCVRP_CEVERYGENRANDOMMUTATION_H
#define PROJEKT_LCVRP_CEVERYGENRANDOMMUTATION_H
#include "IMutationStrategyInterface.h"
#include <random>

class CEveryGenRandomMutation : public IMutationStrategyInterface {
public:
    CEveryGenRandomMutation();
    void vMutate(std::vector<int>& vGenotype, double dMutationProb, int iNumGroups) override;

private:
    std::random_device rd;
    std::mt19937 gen;
};


#endif //PROJEKT_LCVRP_CEVERYGENRANDOMMUTATION_H