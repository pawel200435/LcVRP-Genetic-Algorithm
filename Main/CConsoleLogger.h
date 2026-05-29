#ifndef PROJEKT_LCVRP_CCONSOLELOGGER_H
#define PROJEKT_LCVRP_CCONSOLELOGGER_H
#include "IAlgorithmListener.h"


class CConsoleLogger : public IAlgorithmListener {
public:
    void vListenProgress(int iIteration, double dElapsedSeconds, double dBestFitness, double dCurrentBest) override;
};


#endif //PROJEKT_LCVRP_CCONSOLELOGGER_H