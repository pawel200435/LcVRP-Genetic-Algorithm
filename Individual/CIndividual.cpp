#include "CIndividual.h"
#include "../Alghorithms/Crossing/ICrossoverStrategyInterface.h"
#include <random>

//iSize to liczba lokacji czyli rozmiar genotypu

CIndividual::CIndividual(int iSize, int iNumGroups) {
    dFitness = -1.0; //Domyslna wartosc oznacza nieocenionego osobnika
    vGenotype.resize(iSize);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, iNumGroups - 1);

    //Wypelnienie genotypu losowymi przypisaniami ciezarowek
    for (int i = 0; i < iSize; ++i) {
        vGenotype[i] = distribution(gen);
    }
}
double CIndividual::dCalculateFitness(const CEvaluator& cEvaluator) {
    // Zabezpieczenie: jeśli dFitness jest większy lub równy 0,
    // oznacza to, że został już policzony i jest aktualny.
    if (this->dFitness >= 0.0) {
        return this->dFitness;
    }

    this->dFitness = cEvaluator.dEvaluate(this->vGenotype); //Obliczanie i zapisanie fitnessu korzystajaac z Evaluatora
    return this->dFitness;
}


void CIndividual::vMutate(IMutationStrategyInterface& cStrategy, double dProb, int iNumGroups) {
    cStrategy.vMutate(this->vGenotype, dProb, iNumGroups);
    this->dFitness = -1.0; //Po mutacji fitness jest nieaktualny
}

void CIndividual::vCrossover(ICrossoverStrategyInterface& cStrategy,
    const CIndividual& cParentA,
    const CIndividual& cParentB,
    CIndividual& cChild1,
    CIndividual& cChild2) {

    std::vector<int> vNewGenotype1;
    std::vector<int> vNewGenotype2;

    cStrategy.vCrossover(cParentA.vGetGenotype(), cParentB.vGetGenotype(), vNewGenotype1, vNewGenotype2);

    cChild1.vSetGenotype(std::move(vNewGenotype1));
    cChild2.vSetGenotype(std::move(vNewGenotype2));
}

double CIndividual::dGetFitness() const {
    return this->dFitness;
}
void CIndividual::dSetFitness(double dNewFitness) {
    this->dFitness = dNewFitness;
}

const std::vector<int>& CIndividual::vGetGenotype() const {
    return this->vGenotype;
}

void CIndividual::vSetGenotype(std::vector<int>&& vNewGenotype) {
    dFitness = -1.0;
    vGenotype = std::move(vNewGenotype);
}

SBestIndividualSnapshot CIndividual::sMakeSnapshot() const {
    return SBestIndividualSnapshot(vGenotype,dFitness);
}


