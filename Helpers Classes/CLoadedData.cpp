#include "CLoadedData.h"

CLoadedData::CLoadedData()
    : iDimension(0),iCapacity(0),iDepotId(1) {}

void CLoadedData::vSetDimension(int iNewDimension) {
    if (iNewDimension > 0) {
        iDimension = iNewDimension;
        vCoords.resize(iDimension);
        vDemands.resize(iDimension);
    }
}

//Przepinamy zawartosc wektora zamiac kopiowac
void CLoadedData::vSetCoords(std::vector<SPoint>&& vNewCoords) {
    vCoords = std::move(vNewCoords);
}

void CLoadedData::vSetDemands(std::vector<int>&& vNewDemands) {
    vDemands = std::move(vNewDemands);
}

void CLoadedData::vSetPermutation(std::vector<int>&& vNewPerm) {
    vPermutation = std::move(vNewPerm);
}

const std::string& CLoadedData::sGetName() const {
    return sName;
}
int CLoadedData::iGetDimension() const {
    return iDimension;
}
int CLoadedData::iGetCapacity() const {
    return iCapacity;
}
const std::vector<SPoint>& CLoadedData::vGetCoords() const {
    return vCoords;
}
const std::vector<int>& CLoadedData::vGetDemands() const {
    return vDemands;
}
const std::vector<int>& CLoadedData::vGetPermutation() const {
    return vPermutation;
}
int CLoadedData::iGetDepotId() const {
    return iDepotId;
}
void CLoadedData::vSetName(const std::string& sNewName) {
    sName = sNewName;
}
void CLoadedData::vSetCapacity(int iNewCapacity) {
    iCapacity = iNewCapacity;
}
void CLoadedData::vSetDepotId(int iNewDepotId) {
    iDepotId = iNewDepotId;
}