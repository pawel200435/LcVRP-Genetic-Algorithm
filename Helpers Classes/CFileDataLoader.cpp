#include "CFileDataLoader.h"
#include <fstream>
#include <sstream>

CFileDataLoader::CFileDataLoader(const std::string &sFolderName, const std::string &sFileName)
    : sFolderName(sFolderName), sFileName(sFileName){
    sFullFilePath = S_BASE_PATH + sFolderName + "/" + sFileName + ".lcvrp";
}

CResult<CLoadedData> CFileDataLoader::cLoadData() {
    std::ifstream cFile(sFullFilePath);
    if (!cFile.is_open()) {
        return CResult<CLoadedData>::cFail("Blad przy otwieraniu pliku "+sFullFilePath);
    }

    CLoadedData cData;
    std::string sLine;
    bool bGotDimension = false;

    while (std::getline(cFile, sLine)) {
        sLine = sTrim(sLine);

        if (sLine.empty()) {
            continue;
        }
        if (sLine == "EOF") {
            break;
        }
        //PARSOWANIE
        size_t iColonPos = sLine.find(':');
        if (iColonPos != std::string::npos) { //sprawdzamy czy znaleziono ":"
            std::string sKey = sTrim(sLine.substr(0, iColonPos)); //Wycinamy od indeksu 0 do znaku przed :
            std::string sValue = sTrim(sLine.substr(iColonPos + 1));    //Wycianmy reszte stringa bo to wartosc

            if (sKey == "NAME") {
                cData.vSetName(sValue);
            }
            else if (sKey == "DIMENSION") {
                int iDim = std::stoi(sValue);
                cData.vSetDimension(iDim);
                bGotDimension = true;
            }
            else if (sKey == "CAPACITY") {
                cData.vSetCapacity(std::stoi(sValue));
            }
            else if (sKey == "PERMUTATION") {
                std::vector<int> vPerm;
                std::stringstream ss(sValue);
                int iId;
                while (ss >> iId) {
                    vPerm.push_back(iId);
                }
                cData.vSetPermutation(std::move(vPerm));
            }
        }
        else if (sLine == "NODE_COORD_SECTION" && bGotDimension) {
            std::vector<SPoint> vCoords(cData.iGetDimension());
            for (int i = 0; i < cData.iGetDimension(); i++) {
                int iId;
                double dX, dY;
                cFile >> iId >> dX >> dY; //wczytuje, ">>" pomija biale znaki, wpisuje kolejno do zmiennych odpowiednie typy
                vCoords[iId - 1] = SPoint(dX, dY); //Zamiana ID 1..n na index 0..n-1
            }
            cData.vSetCoords(std::move(vCoords));
        }
        else if (sLine == "DEMAND_SECTION" && bGotDimension) {
            std::vector<int> vDemands(cData.iGetDimension());
            for (int i = 0; i < cData.iGetDimension(); i++) {
                int iId, iDemand;
                cFile >> iId >> iDemand;
                vDemands[iId - 1] = iDemand;
            }
            cData.vSetDemands(std::move(vDemands));
        }
        else if (sLine == "DEPOT_SECTION") {
            int iNewDepotId, iEndChar;
            cFile >> iNewDepotId;
            if (iNewDepotId != 1) {
                cData.vSetDepotId(iNewDepotId);
            }
            cFile >> iEndChar;
        }
    }
    cFile.close();
    if (!bGotDimension || cData.vGetCoords().empty()) {
        return CResult<CLoadedData>::cFail("Bład wczytywania brak wszystkich danych: "+ sFullFilePath);
    }
    return CResult<CLoadedData>::cSuccess(std::move(cData));
}

std::string CFileDataLoader::sTrim(const std::string& sString) {
    size_t iFirst = sString.find_first_not_of(" \t\r\n");
    if (iFirst == std::string::npos) return "";
    size_t iLast = sString.find_last_not_of(" \t\r\n");
    return sString.substr(iFirst, (iLast - iFirst + 1));
}
