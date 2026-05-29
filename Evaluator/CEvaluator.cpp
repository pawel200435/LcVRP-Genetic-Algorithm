#include "CEvaluator.h"

#include "../Helpers Classes/CFileDataLoader.h"

CEvaluator::CEvaluator(int iNumGroups){
    vSetINumGroups(iNumGroups);
}
// CEvaluator::CEvaluator(int iNumGroups): iNumGroups(iNumGroups) {
// }

double CEvaluator::dEvaluate(const std::vector<int> &vGenotype) const {
    const std::vector<int>& vPermutation = cData.vGetPermutation();
    const std::vector<int>& vDemands = cData.vGetDemands();
    int iDepotIndex = cData.iGetDepotId() -1; //Indeksowany od 0
    int iMaxCapacity = cData.iGetCapacity();
    double dTotalFitness = 0.0; //Suma dystansow przejechana przez ciezarowki

    std::vector<int> vTruckLoads(iNumGroups, 0);  // Sumy Wag zaladunkow dla ciezarowek
    std::vector<int> vTruckCurrentLocationIndex(iNumGroups, iDepotIndex);  //Ostatnia pozycja ciezarowki (Pozycja startowa to DEPOT)
    std::vector<double> vTruckDistances(iNumGroups, 0.0); //Przejechane dystanse ciezarowek
    std::vector<bool> vTruckLeftDepot(iNumGroups, false); //True jest ciezarowka wyjedzie potrzebne do zliczania pworotu do DEPOT

    for (size_t i = 0; i < vPermutation.size(); i++) {
        int iLocationId = vPermutation[i];
        int iNextLocationIndex = iLocationId-1;
        int iTruckId = vGenotype[i]; // Ciezarowki numerowane od 0 do iNumGroups-1
        int iCurrentDemand = vDemands[iNextLocationIndex]; //Obciazenie obecnego klienta
        vTruckLeftDepot[iTruckId] = true; //oznaczenie ciezarowki ze wyjechala z depotu -> bedzie wiec musiala wrocic do niego (dodamy koszt powrotu)

        //Sprawedzenie czy wystąpi nadmiaru wagi
        if (vTruckLoads[iTruckId] + iCurrentDemand > iMaxCapacity) {
            //sumaTrasyCiezarowki  += odleglosc(obecnaPozycja, DEPOT)
            vTruckDistances[iTruckId] += vDistanceMatrix[vTruckCurrentLocationIndex[iTruckId]][iDepotIndex];
            vTruckLoads[iTruckId] = 0; //Reset obiazenia (bo zostala wyladowana w depocie)
            vTruckCurrentLocationIndex[iTruckId] = iDepotIndex; //Ustawienie obecnej lokalizacji na DEPOT
        }

        vTruckLoads[iTruckId] += iCurrentDemand; //Dodanie obciązenia do obecnego ladunku ciezarowki
        vTruckDistances[iTruckId] += vDistanceMatrix[vTruckCurrentLocationIndex[iTruckId]][iNextLocationIndex]; //dystans += odelglosc(obecnaPozycja, nastepnaPozycja)
        vTruckCurrentLocationIndex[iTruckId] = iNextLocationIndex; //Aktualizacja Lokalizacji ciezarowki
    }

    //Dodanie odleglosci powrotu do DEPOT z obecnej lokalizacji
    for (size_t i=0; i < iNumGroups; i++) {
        if (vTruckLeftDepot[i] == true) {
            vTruckDistances[i] += vDistanceMatrix[vTruckCurrentLocationIndex[i]][iDepotIndex];
            vTruckCurrentLocationIndex[i] = iDepotIndex;
        }
        //Sumowanie dystansow przejechanych przez ciezarowki
        dTotalFitness += vTruckDistances[i];
    }

    return dTotalFitness;
}


CResult<bool> CEvaluator::cLoadInstance(const std::string &sFolderName, const std::string &sFileName) {
    CFileDataLoader cLoader(sFolderName, sFileName);
    CResult<CLoadedData> cResult = cLoader.cLoadData();

    if (!cResult.bIsSuccess()) {
        return CResult<bool>::cFail(cResult.sGetErrorMsg());
    }
    cData = std::move(cResult.tGetValue()); //Przeniesienie danych do klasy Evaluatora
    vBuildDistanceMatrix(); //Budowanie Macierzy

    return CResult<bool>::cSuccess(true);
}


void CEvaluator::vBuildDistanceMatrix() {
    int iDim = cData.iGetDimension();
    const std::vector<SPoint>& vCoords = cData.vGetCoords();
    vDistanceMatrix.assign(iDim, std::vector<double>(iDim, 0.0)); //Zmiana romiaru macierzy i zerowanie

    for (int i = 0; i < iDim; i++) {
        //zmniejszamy liczbe operacji bo macierz jest symetryczna
        // wiec mozemy wykonywac obliczenia tylko dla "GORNEGO TROJKATA",
        // "DOLNY TROJKAT" jest uzupelniany jednoczesnie
        for (int j = i+1; j < iDim; j++) {
            double dDistance = dCalculateDistance(vCoords[i], vCoords[j]);
            vDistanceMatrix[i][j] = dDistance;
            vDistanceMatrix[j][i] = dDistance; //uzupelnienie dolnego trojkata
        }
    }
}

double CEvaluator::dCalculateDistance(const SPoint& p1, const SPoint& p2) const {
    return std::sqrt((p1.dX - p2.dX) * (p1.dX - p2.dX) + (p1.dY - p2.dY) * (p1.dY - p2.dY)); //wzor na odleglosc
}

void CEvaluator::vSetINumGroups(int iNewNumGroups) {
    if (iNewNumGroups < DEFAULT_MIN_NUMGROUPS) {
        this->iNumGroups = DEFAULT_MIN_NUMGROUPS;
        return;
    }
    this->iNumGroups = iNewNumGroups;
}

int CEvaluator::iGetNumGroups() const {
    return this->iNumGroups;
}
int CEvaluator::iGetGenotypeSize() const {
    return (int)cData.vGetPermutation().size();
}