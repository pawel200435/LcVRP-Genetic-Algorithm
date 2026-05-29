#ifndef PROJEKT_LCVRP_CONETPOINTCROSSOVER_H
#define PROJEKT_LCVRP_CONETPOINTCROSSOVER_H
#include "ICrossoverStrategyInterface.h"
#include <random>

class COnePointCrossover : public ICrossoverStrategyInterface{
public:
    COnePointCrossover();

    void vCrossover(const std::vector<int>& vParentA,
                    const std::vector<int>& vParentB,
                    std::vector<int>& vChild1,
                    std::vector<int>& vChild2) override;

private:
    std::random_device rd;
    std::mt19937 gen;
};


#endif //PROJEKT_LCVRP_CONETPOINTCROSSOVER_H