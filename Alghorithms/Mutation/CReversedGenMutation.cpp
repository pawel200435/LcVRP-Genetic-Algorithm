#include "CReversedGenMutation.h"

CReversedGenMutation::CReversedGenMutation() {
    this->gen = std::mt19937(this->rd());
}

void CReversedGenMutation::vMutate(std::vector<int> &vGenotype, double dMutationProb, int iNumGroups) {
    if (dMutationProb <= 0) return;

    std::uniform_real_distribution<> probDistribuation (0.0, 1.0);
    if (probDistribuation(gen) > dMutationProb) return;

    int iGenotypeSize = vGenotype.size();
    std::uniform_int_distribution<> distribution(0, iGenotypeSize - 1);
    int firstPivot = distribution(this->gen);
    int lastPivot = distribution(this->gen);

    if (firstPivot == lastPivot) {
        return;
    }
    if (firstPivot > lastPivot) {
        std::swap(firstPivot, lastPivot);
    }

    while (firstPivot < lastPivot) {
        std::swap(vGenotype[firstPivot], vGenotype[lastPivot]);
        firstPivot++;
        lastPivot--;
    }
}

