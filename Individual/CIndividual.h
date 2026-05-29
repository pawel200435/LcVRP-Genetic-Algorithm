#ifndef PROJEKT_LCVRP_CINDIVIDUAL_H
#define PROJEKT_LCVRP_CINDIVIDUAL_H
#include <vector>
#include "../Alghorithms/Crossing/ICrossoverStrategyInterface.h"
#include "../Alghorithms/Mutation/IMutationStrategyInterface.h"
#include "../Evaluator/CEvaluator.h"
#include "SBestIndividualSnapshot.h"

class CIndividual {
public:
    CIndividual(int iSize, int iNumGroups);
    CIndividual(const CIndividual& other) = default;
    CIndividual& operator=(const CIndividual& other) = default;
    CIndividual(CIndividual&& other) = default;
    CIndividual& operator=(CIndividual&& other) = default;

    double dCalculateFitness(const CEvaluator& cEvaluator);
    void vMutate(IMutationStrategyInterface& cStrategy,double dMutationProb, int iNumGroups);
    static void vCrossover(ICrossoverStrategyInterface& cStrategy,
        const CIndividual& cParentA, const CIndividual& cParentB,
        CIndividual& cChild1, CIndividual& cChild2);

    double dGetFitness() const;
    void dSetFitness(double dNewFitness);
    const std::vector<int>& vGetGenotype() const;
    void vSetGenotype(std::vector<int>&& vNewGenotype);
    SBestIndividualSnapshot sMakeSnapshot() const;

private:
    std::vector<int> vGenotype;
    double dFitness;
};


#endif //PROJEKT_LCVRP_CINDIVIDUAL_H