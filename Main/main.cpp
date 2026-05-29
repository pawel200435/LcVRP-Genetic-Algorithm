#include <iostream>

#include "CConsoleLogger.h"
#include "../Alghorithms/Crossing/COnePointCrossover.h"
#include "../Alghorithms/Mutation/CEveryGenRandomMutation.h"
#include "../Alghorithms/Mutation/CReversedGenMutation.h"
#include "../Helpers Classes/CResult.h"
#include "../Helpers Classes/CFileDataLoader.h"
#include "../Evaluator/CEvaluator.h"
#include "../GeneticAlgorithm/CGeneticAlgorithm.h"


int main() {
    const std::string sFolder = "Vrp-Set-P";
    const std::string sFile = "P-n16-k8";
    int iNumGroups = 2;
    int iPopSize = 100;
    double dCrossProb = 0.7;
    double dMutProb = 0.1;
    int iTournamentSize = 2;
    int iIterations = 100000;
    double dMaxSeconds = 60;
    double dLogInterval = 5;
    COnePointCrossover cCrossStrategy;
    // CEveryGenRandomMutation cMutStrategy;
    CReversedGenMutation cMutStrategy;

    std::vector<int> wektor = {2,6,1,4,3,5,5,1};
    cMutStrategy.vMutate(wektor, 1, iNumGroups);
    for (int iGen : wektor) {
        std::cout << iGen << " ";
    }


    CEvaluator cEval(iNumGroups);
    CResult<bool> result = cEval.cLoadInstance(sFolder, sFile);
    if (!result.bIsSuccess()) {
        std::cerr << "CRESULT: "+ result.sGetErrorMsg() << std::endl;
        return 1;
    }

    CGeneticAlgorithm cAG(cEval);
    cAG.vSetPopulationSize(iPopSize);
    cAG.vSetCrossingProb(dCrossProb);
    cAG.vSetMutationProb(dMutProb);
    cAG.vSetTournamentSize(iTournamentSize);

    //CGeneticAlgorithm cGenAlg(cEval, iPopSize, dCrossProb, dMutProb, iTournamentSize);
    std::cout << "Start ewolucji..." << std::endl;
    CConsoleLogger cLogger; //Obiekt wyswietlajacy
    cAG.vRun(iIterations, dMaxSeconds, dLogInterval, cCrossStrategy, cMutStrategy, &cLogger);
    std::cout << "Ewolucja zakonczona." << std::endl;


    const SBestIndividualSnapshot& sBest = cAG.sGetBest();
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "NAJLEPSZY ZNALEZIONY DYSTANS: " << sBest.dFitness << std::endl;
    std::cout << "Genotyp: ";
    for (int iTruckNumber : sBest.vGenotype) {
        std::cout << iTruckNumber << " ";
    }
    std::cout << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    return 0;






    //
    //
    //
    // // 1. Przygotowanie danych testowych
    // // Twój genotyp (15 elementów, najwyższy indeks ciężarówki to 7)
    // std::vector<int> vTestGenotype = { 0, 7, 1, 2, 7, 0, 0, 5, 2, 3, 4, 4, 1, 4, 4 };
    //
    // // 2. Inicjalizacja Ewaluatora (musi być wczytany plik!)
    // // Upewnij się, że iNumTrucks >= 8, bo w genotypie masz ID "7"
    // int iNumTrucks = 8;
    // CEvaluator cEval(iNumTrucks);
    // cEval.cLoadInstance("Vrp-Set-P", "P-n16-k8");
    //
    // // 3. Stworzenie osobnika testowego
    // // Rozmiar genotypu (15) i liczba grup (8)
    // CIndividual cTestIndividual(15, iNumTrucks);
    //
    // // 4. Ręczne wstrzyknięcie genotypu
    // // Używamy std::move, bo vSetGenotype przyjmuje r-wartość (&&)
    // cTestIndividual.vSetGenotype(std::move(vTestGenotype));
    //
    // // 5. Obliczenie dystansu
    // double dFitness = cTestIndividual.dCalculateFitness(cEval);
    //
    // // 6. Wyświetlenie wyniku
    // std::cout << "--- TEST RĘCZNEGO GENOTYPU ---" << std::endl;
    // std::cout << "Obliczony dystans: " << dFitness << std::endl;
    // if (dFitness < 0) {
    //     std::cout << "BŁĄD: Wynik ujemny może oznaczać błąd w CEvaluator!" << std::endl;
    // }
    //
    //





    //          TESTY WCZYTYWANIA
    // CFileDataLoader cLoader("Vrp-Set-P", "P-n16-k8");
    // CResult<CLoadedData> cResult = cLoader.cLoadData();
    //
    // if (!cResult.bIsSuccess()) {
    //     std::cout << "BLAD WCZYTYWANIA: " << cResult.sGetErrorMsg() << std::endl;
    //     return 1;
    // }
    // CLoadedData& cData = cResult.tGetValue();
    // std::cout << "--- TEST ODCZYTU DANYCH LcVRP ---" << std::endl;
    // std::cout << "Nazwa instancji: " << cData.sGetName() << std::endl;
    // std::cout << "Wymiar (Dimension): " << cData.iGetDimension() << std::endl;
    // std::cout << "Pojemnosc (Capacity): " << cData.iGetCapacity() << std::endl;
    // std::cout << "ID Depotu: " << cData.iGetDepotId() << std::endl;
    //
    // const auto& vCoords = cData.vGetCoords();
    // const auto& vDemands = cData.vGetDemands();
    //
    // if (!vCoords.empty()) {
    //     std::cout << "\n--- Weryfikacja punktow (pierwszy i ostatni) ---" << std::endl;
    //
    //     // Punkt 1 (zazwyczaj Depot, indeks 0)
    //     std::cout << "Punkt [1]: X=" << vCoords[0].dX << ", Y=" << vCoords[0].dY
    //               << ", Demand=" << vDemands[0] << std::endl;
    //
    //     // Ostatni punkt (indeks dimension - 1)
    //     int iLast = cData.iGetDimension() - 1;
    //     std::cout << "Punkt [" << iLast + 1 << "]: X=" << vCoords[iLast].dX
    //               << ", Y=" << vCoords[iLast].dY
    //               << ", Demand=" << vDemands[iLast] << std::endl;
    // }
    // const auto& vPerm = cData.vGetPermutation();
    // std::cout << "\nLiczba klientow w permutacji: " << vPerm.size() << std::endl;
    // if (!vPerm.empty()) {
    //     std::cout << "Pierwszy klient do odwiedzenia: " << vPerm[0] << std::endl;
    // }
    // std::cout << "\n--- TEST ZAKONCZONY POMYSLNIE ---" << std::endl;


}
