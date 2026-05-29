#include "CEveryGenRandomMutation.h"

CEveryGenRandomMutation::CEveryGenRandomMutation() {
    this->gen = std::mt19937(this->rd());
}

void CEveryGenRandomMutation::vMutate(std::vector<int> &vGenotype, double dMutationProb, int iNumGroups) {
    if (dMutationProb <= 0.0) return; //jesli prawdopodobienstwo wynosi 0 to znaczy ze nie mutujemy

    //Rozkład do sprawdzania prawdopodobieństwa mutacji (0.0 do 1.0)
    std::uniform_real_distribution<> probDistribuation (0.0, 1.0);

    for (size_t i = 0; i < vGenotype.size(); ++i) {
        // Jeśli wylosowana liczba jest mniejsza od dProb, zmieniamy gen
        if (probDistribuation(gen) < dMutationProb) {
            //Rozkład do losowania nowej ciężarówki (0 do iNumGroups - 1)
            std::uniform_int_distribution<> truckDistribuation(0, iNumGroups - 1);
            vGenotype[i] = truckDistribuation(gen); //Mutacja
        }
    }

}


