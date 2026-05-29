#ifndef PROJEKT_LCVRP_CLOADEDDATA_H
#define PROJEKT_LCVRP_CLOADEDDATA_H
#include <string>
#include <vector>

// Punkt 2D
struct SPoint {
    double dX = 0.0;
    double dY = 0.0;

    SPoint() = default;
    SPoint(double dX, double dY) : dX(dX), dY(dY) {}
};


class CLoadedData {
public:
    CLoadedData();

    const std::string& sGetName() const;
    int iGetDimension() const;
    int iGetCapacity() const;
    const std::vector<SPoint>& vGetCoords() const;
    const std::vector<int>& vGetDemands() const;
    const std::vector<int>& vGetPermutation() const;
    int iGetDepotId() const;

    void vSetName(const std::string& sNewName);
    void vSetDimension(int iNewDimension);
    void vSetCapacity(int iNewCapacity);
    void vSetDepotId(int iNewDepotId);

    //R-value pozwala uniknac kopiowania duzych wektorow.
    void vSetCoords(std::vector<SPoint>&& vNewCoords);
    void vSetDemands(std::vector<int>&& vNewDemands);
    void vSetPermutation(std::vector<int>&& vNewPermutation);

private:
    std::string sName;
    int iDimension; //Liczba wszystkich wezlow
    int iCapacity; //Maksymalna pojemnosc ciezarowki
    std::vector<SPoint> vCoords; //Punkty wspolrzednych (indeksy od 0, node 1 ma index 0)
    std::vector<int> vDemands;    //Zapotrzebowanie w lokalizacjach
    std::vector<int> vPermutation; //Permutacja lokalizacji
    int iDepotId;

};


#endif //PROJEKT_LCVRP_CLOADEDDATA_H