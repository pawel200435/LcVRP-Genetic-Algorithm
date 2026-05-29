#ifndef PROJEKT_LCVRP_CRESULT_H
#define PROJEKT_LCVRP_CRESULT_H
#include <string>

template <typename T>
class CResult {
    public:
    static CResult<T> cSuccess(T resultValue);
    static CResult<T> cFail(std::string sErrorMsg);

    bool bIsSuccess() const;
    const std::string& sGetErrorMsg() const;
    T& tGetValue();

    private:
    CResult(bool bIsSuccess, T tValue, std::string sErrorMsg);

    bool bSuccess;
    T tValue;
    std::string sErrorMsg;
};


template<typename T>
CResult<T> CResult<T>::cSuccess(T resultValue) {
    return CResult(true, std::move(resultValue), ""); //zeby nie wykonywac kopii obiektu np duzego cData z pliku CFileDataLoader.cpp
}

template<typename T>
CResult<T> CResult<T>::cFail(std::string sErrorMsg) {
    return CResult(false, T(), sErrorMsg); // T() wywola konstruktor domyslny danego typu
}

template<typename T>
bool CResult<T>::bIsSuccess() const {
    return bSuccess;
}

template<typename T>
const std::string& CResult<T>::sGetErrorMsg() const {
    return sErrorMsg;
}

template<typename T>
T & CResult<T>::tGetValue() {
    return tValue;
}

template<typename T>
CResult<T>::CResult(bool bIsSuccess, T tValue, std::string sErrorMsg)
    : bSuccess(bIsSuccess), tValue(std::move(tValue)), sErrorMsg(std::move(sErrorMsg)) {}


#endif //PROJEKT_LCVRP_CRESULT_H
