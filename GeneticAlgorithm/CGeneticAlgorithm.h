#ifndef PROJEKT_LCVRP_CGENETICALGORITHM_H
#define PROJEKT_LCVRP_CGENETICALGORITHM_H
#include <vector>
#include <random>
#include <chrono>
#include "../Individual/CIndividual.h"
#include "../Evaluator/CEvaluator.h"
#include "../Alghorithms/Crossing/ICrossoverStrategyInterface.h"
#include "../Alghorithms/Mutation/IMutationStrategyInterface.h"
#include "../Individual/SBestIndividualSnapshot.h"
#include "../Main/IAlgorithmListener.h"

class CGeneticAlgorithm {
public:
    CGeneticAlgorithm(const CEvaluator& cEval);
    //DOMYSLE WARTOSC W TYM KONSTRUKTORZE I ZABEZPIECZONE ZA POMOCA SETTEROW
    //CGeneticAlgorithm(const CEvaluator& cEvaluator, int iPopSize, double dCrossProb, double dMutProb, int iTournamentSize);

    //Głowna metoda algorytmu
    //void vRun(int iMaxIterations, ICrossoverStrategyInterface& cCrossStrategy, IMutationStrategyInterface& cMutStrategy);
    void vRun(int iMaxIterations, double dMaxSeconds, double dLogInterval, ICrossoverStrategyInterface& cCrossStrategy, IMutationStrategyInterface& cMutStrategy, IAlgorithmListener* pListener);
    const SBestIndividualSnapshot& sGetBest() const;



    int iGetPopulationSize() const;
    void vSetPopulationSize(int iPopSize);
    double iGetMutationProb() const;
    void vSetMutationProb(double iMutProb);
    double iGetCrossingProb() const;
    void vSetCrossingProb(double iCrossProb);
    int iGetTournamentSize() const;
    void vSetTournamentSize(int iTournSize);

private:
    const CEvaluator& cEvaluator;
    std::vector<CIndividual> vPopulation; //Wektor zawierajacy wszystkie osobniki w populacji
    SBestIndividualSnapshot sBestSnapshot;
    double dCurrentPopulationBest; //do wyswietlania
    int iPopulationSize;
    double dMutationProb;
    double dCrossingProb;
    int iTournamentSize;
    std::random_device rd;
    std::mt19937 gen;


    void vInitializePopulation();
    void vEvaluatePopulation();
    void vUpdateBestSnapshot();
    const CIndividual& cTournamentSelection(); //Zwraca wygranego osobnika
    bool bCheckTimeRaport(int iIteration, std::chrono::steady_clock::time_point& rLastLogTime, const std::chrono::steady_clock::time_point& rStartTime, double dMaxSeconds, double dLogInterval, IAlgorithmListener* pListener);

};


#endif //PROJEKT_LCVRP_CGENETICALGORITHM_H