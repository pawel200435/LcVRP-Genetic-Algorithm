#ifndef PROJEKT_LCVRP_CEVALUATOR_H
#define PROJEKT_LCVRP_CEVALUATOR_H
#include "../Helpers Classes/CResult.h"
#include "../Helpers Classes/CLoadedData.h"
#include <vector>
#include <cmath>

class CEvaluator {
public:
    CEvaluator(int iNumGroups);
    CResult<bool> cLoadInstance(const std::string& sFolderName, const std::string& sFileName);
    double dEvaluate(const std::vector<int>& vGenotype) const;

    int iGetNumGroups() const;
    int iGetGenotypeSize() const;
    void vSetINumGroups(int iNewNumGroups);

private:
    static const int DEFAULT_MIN_NUMGROUPS = 2;
    CLoadedData cData;
    int iNumGroups;     //Liczba ciezarowek
    std::vector<std::vector<double>> vDistanceMatrix;   //Zapamietana macierz odleglosci

    void vBuildDistanceMatrix();
    double dCalculateDistance(const SPoint& p1, const SPoint& p2) const;
};


#endif //PROJEKT_LCVRP_CEVALUATOR_H