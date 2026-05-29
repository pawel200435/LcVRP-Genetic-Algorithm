#ifndef PROJEKT_LCVRP_CFILEDATALOADER_H
#define PROJEKT_LCVRP_CFILEDATALOADER_H
#include "CLoadedData.h"
#include "CResult.h"


class CFileDataLoader {
public:
    CFileDataLoader(const std::string& sFolderName, const std::string& sFileName);
    CResult<CLoadedData> cLoadData();

private:
    static constexpr const char* S_BASE_PATH = "../data/lcvrp/";

    std::string sFolderName;
    std::string sFileName;
    std::string sFullFilePath;

    std::string sTrim(const std::string& sString);
};


#endif //PROJEKT_LCVRP_CFILEDATALOADER_H