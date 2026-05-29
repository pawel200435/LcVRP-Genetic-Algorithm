#include "CGeneticAlgorithm.h"
#include "ConstantsGeneticAlgorithm.h"
#include <iostream>

// CGeneticAlgorithm::CGeneticAlgorithm(const CEvaluator& cEval, int iPopSize, double dCrossProb, double dMutProb, int iTournamentSize)
//     : cEvaluator(cEval), iPopulationSize(iPopSize), dCrossingProb(dCrossProb),
//     dMutationProb(dMutProb), iTournamentSize(iTournamentSize), gen(rd()) {
// }

CGeneticAlgorithm::CGeneticAlgorithm(const CEvaluator& cEval) : cEvaluator(cEval), gen(rd()) {
    vSetPopulationSize(DEFAULT_MIN_TOURNAMENT_SIZE);
    vSetCrossingProb(DEFAULT_CROSSING_PROB);
    vSetMutationProb(DEFAULT_MUTATION_PROB);
    vSetTournamentSize(DEFAULT_MIN_TOURNAMENT_SIZE);
}

const SBestIndividualSnapshot &CGeneticAlgorithm::sGetBest() const {
    return sBestSnapshot;
}

int CGeneticAlgorithm::iGetPopulationSize() const {return iPopulationSize;}
void CGeneticAlgorithm::vSetPopulationSize(int iPopSize) {
    if (iPopulationSize < DEFAULT_MIN_POPULATION_SIZE) {
        iPopulationSize = DEFAULT_MIN_POPULATION_SIZE;
        return;
    }
    this->iPopulationSize = iPopSize;
}

double CGeneticAlgorithm::iGetMutationProb() const {return dMutationProb;}
void CGeneticAlgorithm::vSetMutationProb(double dMutProb) {
    if (dMutProb < 0.0 || dMutProb > 1.0) {
        this->dMutationProb = DEFAULT_MUTATION_PROB;
        return;
    }
    this->dMutationProb = dMutProb;
}

double CGeneticAlgorithm::iGetCrossingProb() const {return dCrossingProb;}
void CGeneticAlgorithm::vSetCrossingProb(double iCrossProb) {
    if (iCrossProb < 0.0 || iCrossProb > 1.0) {
        this->dCrossingProb = DEFAULT_CROSSING_PROB;
        return;
    }
    this->dCrossingProb = iCrossProb;
}

int CGeneticAlgorithm::iGetTournamentSize() const {return iTournamentSize;}
void CGeneticAlgorithm::vSetTournamentSize(int iTournSize) {
    if (iTournSize < DEFAULT_MIN_TOURNAMENT_SIZE || iTournSize > iPopulationSize) {
        iTournamentSize = DEFAULT_MIN_TOURNAMENT_SIZE;
        return;
    }
    this->iTournamentSize = iTournSize;
}


void CGeneticAlgorithm::vRun(int iMaxIterations, double dMaxSeconds, double dLogInterval, ICrossoverStrategyInterface &cCrossStrategy, IMutationStrategyInterface &cMutStrategy, IAlgorithmListener *pListener) {
    vInitializePopulation(); //Stworzenie populacji
    vEvaluatePopulation();  //Obliczenie fitensow
    vUpdateBestSnapshot();  //Zaktualizowanie najlepszego osobnika dotychczas

    auto startTime = std::chrono::steady_clock::now();  //Potrzebne do raportowania i kontroli czasu dzialania programu
    auto lastLogTime = startTime;

    std::uniform_real_distribution<> random(0.0,1.0);

    for (int i = 0; i < iMaxIterations; i++) {
        if (!bCheckTimeRaport(i, lastLogTime, startTime, dMaxSeconds, dLogInterval, pListener)) break; //Metoda sprawdzajaca czas i raportujaca postepy do Listenera

        std::vector<CIndividual> vNextPopulation; //wektor zawierajacy miejsce na nasteona populacje
        vNextPopulation.reserve(iPopulationSize);

        while (vNextPopulation.size() < iPopulationSize) {  // Musimy stworzyc nowa populacje o takiej samej wielkosci co poprzednia
            //Selekcja turniejowa
            const CIndividual& cParentA = cTournamentSelection();
            const CIndividual& cParentB = cTournamentSelection();

            //Krzyzowanie
            CIndividual cChildA = cParentA;
            CIndividual cChildB = cParentB;
            if (random(gen) < dCrossingProb) {
                CIndividual::vCrossover(cCrossStrategy, cParentA, cParentB, cChildA, cChildB);
            }

            //Mutacja
            cChildA.vMutate(cMutStrategy, dMutationProb, cEvaluator.iGetNumGroups());
            cChildB.vMutate(cMutStrategy, dMutationProb, cEvaluator.iGetNumGroups());

            //Ocena i dodanie do nowej generacji
            cChildA.dCalculateFitness(cEvaluator);
            cChildB.dCalculateFitness(cEvaluator);
            vNextPopulation.push_back(std::move(cChildA));
            if (vNextPopulation.size() < iPopulationSize) {     //ZABEZPIECZENIE JESLI BYLOBY NIEPARZYSTA LICZBA POPULACJI
                vNextPopulation.push_back(std::move(cChildB));
            }
        }

        vPopulation = std::move(vNextPopulation); //STARA populacja jest zastapiona NOWĄ
        vUpdateBestSnapshot();
    }
}


void CGeneticAlgorithm::vInitializePopulation() {
    vPopulation.clear(); //Czyszczenie wektora
    int iGenotypeSize = cEvaluator.iGetGenotypeSize();
    int iNumTrucks = cEvaluator.iGetNumGroups();

    vPopulation.reserve(iPopulationSize); //Rezerwuje pamiec potrzebna na ten obiekt
    for (int i = 0; i < iPopulationSize; i++) {
        CIndividual cNewIndividual(iGenotypeSize, iNumTrucks);  //Tworzymy nowego losowego osobnika (musimy tworzyc nowego caly czas bo losuje on w srodku geny)
        vPopulation.push_back(std::move(cNewIndividual));  //Dodajemy go do populacji przepinajac go
    }
}

void CGeneticAlgorithm::vEvaluatePopulation() {
    for (CIndividual& cIndividual : vPopulation) {
        cIndividual.dCalculateFitness(cEvaluator);
    }
}

/// NOWA METODA
void CGeneticAlgorithm::vUpdateBestSnapshot() {
    //Szukamy najlepszego w obecnej populacji
    double dPopulationBest = vPopulation[0].dGetFitness();
    const CIndividual* pGenBestIndividual = &vPopulation[0];

    for (const auto& cIndividual : vPopulation) {
        if (cIndividual.dGetFitness() < dPopulationBest) { // Minimalizacja
            dPopulationBest = cIndividual.dGetFitness();
            pGenBestIndividual = &cIndividual;
        }
    }
    // Zapamiętujemy wynik tej konkretnej generacji
    this->dCurrentPopulationBest = dPopulationBest;
    // Sprawdzamy, czy to rekord globalny (Global Best), <0 jesli jest swieży
    if (sBestSnapshot.dFitness < 0 || dPopulationBest < sBestSnapshot.dFitness) {
        sBestSnapshot = pGenBestIndividual->sMakeSnapshot();
    }
}

const CIndividual& CGeneticAlgorithm::cTournamentSelection() { //Dzialajac na wskaznikach unikamu kopiowan
    std::uniform_int_distribution<> iIndex(0, iPopulationSize - 1);
    const CIndividual* pBest = &vPopulation[iIndex(gen)];   //Losujemy pierwszego kandydata (z racji ze jest 1 to bedzie najlepszy)

    //Losujemy nastepnych kandydatow w zaleznosci od wielkosci Turnieju
    for (int i=1; i<iTournamentSize; i++) {
        const CIndividual* pCandidate = &vPopulation[iIndex(gen)];
        if (pCandidate->dGetFitness() < pBest->dGetFitness()) {
            pBest = pCandidate;
        }
    }
    return *pBest;
}


bool CGeneticAlgorithm::bCheckTimeRaport(int iIteration, std::chrono::steady_clock::time_point& rLastLogTime, const std::chrono::steady_clock::time_point& rStartTime, double dMaxSeconds, double dLogInterval, IAlgorithmListener* pListener) {
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTotalTime = currentTime - rStartTime;
    if (elapsedTotalTime.count() >= dMaxSeconds) return false; //Sprawdzenie limitu czasu

    std::chrono::duration<double> elapsedSinceLog = currentTime - rLastLogTime; //Czas od ostatniego raportu
    if (pListener && elapsedSinceLog.count() >= dLogInterval) {
        pListener->vListenProgress(iIteration, elapsedTotalTime.count(), sBestSnapshot.dFitness, dCurrentPopulationBest);//Powiadomienie Listenera
        rLastLogTime = currentTime; // Aktualizacja czasu ostatniego logu
    }
    return true;
}

