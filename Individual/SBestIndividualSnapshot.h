#ifndef PROJEKT_LCVRP_SBESTINDIVIDUALSNAPSHOT_H
#define PROJEKT_LCVRP_SBESTINDIVIDUALSNAPSHOT_H
#include <vector>

struct SBestIndividualSnapshot {
    std::vector<int> vGenotype;
    double dFitness;

    SBestIndividualSnapshot()
        : dFitness(std::numeric_limits<double>::max()){}

    //Kopiujemy genotyp i wartosc Fitness
    SBestIndividualSnapshot(const std::vector<int> vGenotype, const double dFitness)
        : vGenotype(vGenotype) ,dFitness(dFitness){}

};


#endif //PROJEKT_LCVRP_SBESTINDIVIDUALSNAPSHOT_H